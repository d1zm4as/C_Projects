/* dnscli.c */

#include <dnscli.h>

#include <time.h>

enum {
    DNS_PORT = 53,
    DNS_CLASS_IN = 1,
    DNS_TYPE_A = 1,
    DNS_TYPE_AAAA = 28,
    DNS_TYPE_CNAME = 5,
    DNS_MAX_PACKET = 512
};

static uint16_t read_u16(const unsigned char *p) {
    return (uint16_t)((p[0] << 8) | p[1]);
}

static void write_u16(unsigned char *p, uint16_t value) {
    p[0] = (unsigned char)((value >> 8) & 0xff);
    p[1] = (unsigned char)(value & 0xff);
}

void zero(int8 *dst, int16 size) {
    memset(dst, 0, size);
}

packet *mrpacket(void) {
    packet *p = malloc(sizeof(*p));

    assert(p);
    zero($1 p, (int16)sizeof(*p));
    p->e.type = TypeIPv4;
    return p;
}

static int parse_qtype(const char *value) {
    if (value == NULL || *value == '\0' || strcmp(value, "A") == 0) {
        return DNS_TYPE_A;
    }
    if (strcmp(value, "AAAA") == 0) {
        return DNS_TYPE_AAAA;
    }
    if (strcmp(value, "CNAME") == 0) {
        return DNS_TYPE_CNAME;
    }
    return -1;
}

static size_t encode_qname(unsigned char *dst, size_t dstlen, const char *name) {
    size_t written = 0;
    const char *label = name;

    while (*label != '\0') {
        const char *dot = strchr(label, '.');
        size_t len = dot ? (size_t)(dot - label) : strlen(label);

        if (len == 0 || len > 63 || written + len + 2 > dstlen) {
            return 0;
        }

        dst[written++] = (unsigned char)len;
        memcpy(dst + written, label, len);
        written += len;

        if (!dot) {
            break;
        }

        label = dot + 1;
    }

    if (written + 1 > dstlen) {
        return 0;
    }

    dst[written++] = 0;
    return written;
}

static ssize_t skip_name(const unsigned char *msg, size_t msglen, size_t offset) {
    size_t pos = offset;
    size_t jumps = 0;

    while (pos < msglen) {
        unsigned char len = msg[pos];

        if ((len & 0xc0) == 0xc0) {
            if (pos + 1 >= msglen || jumps++ > msglen) {
                return -1;
            }
            return (ssize_t)(pos + 2 - offset);
        }

        if (len == 0) {
            return (ssize_t)(pos + 1 - offset);
        }

        pos += (size_t)len + 1;
    }

    return -1;
}

static int decode_name(const unsigned char *msg, size_t msglen, size_t offset, char *out, size_t outlen, size_t *consumed) {
    size_t pos = offset;
    size_t outpos = 0;
    size_t used = 0;
    int jumped = 0;
    size_t safety = 0;

    if (outlen == 0) {
        return -1;
    }

    out[0] = '\0';

    while (pos < msglen && safety++ < msglen) {
        unsigned char len = msg[pos];

        if ((len & 0xc0) == 0xc0) {
            if (pos + 1 >= msglen) {
                return -1;
            }
            uint16_t ptr = (uint16_t)(((len & 0x3f) << 8) | msg[pos + 1]);
            if (!jumped) {
                used = pos + 2 - offset;
                jumped = 1;
            }
            pos = ptr;
            continue;
        }

        if (len == 0) {
            if (!jumped) {
                used = pos + 1 - offset;
            }
            if (outpos == 0) {
                if (outlen < 2) {
                    return -1;
                }
                out[outpos++] = '.';
            }
            out[outpos] = '\0';
            if (consumed != NULL) {
                *consumed = used;
            }
            return 0;
        }

        pos++;
        if (pos + len > msglen || outpos + len + 2 > outlen) {
            return -1;
        }

        if (outpos != 0) {
            out[outpos++] = '.';
        }

        memcpy(out + outpos, msg + pos, len);
        outpos += len;
        pos += len;

        if (!jumped) {
            used = pos - offset;
        }
    }

    return -1;
}

static int resolve_server(const char *server, struct sockaddr_storage *addr, socklen_t *addrlen, int *family_out) {
    struct in_addr v4;
    struct in6_addr v6;

    memset(addr, 0, sizeof(*addr));

    if (inet_pton(AF_INET, server, &v4) == 1) {
        struct sockaddr_in *sin = (struct sockaddr_in *)addr;
        sin->sin_family = AF_INET;
        sin->sin_port = htons(DNS_PORT);
        sin->sin_addr = v4;
        *addrlen = sizeof(*sin);
        *family_out = AF_INET;
        return 0;
    }

    if (inet_pton(AF_INET6, server, &v6) == 1) {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)addr;
        sin6->sin6_family = AF_INET6;
        sin6->sin6_port = htons(DNS_PORT);
        sin6->sin6_addr = v6;
        *addrlen = sizeof(*sin6);
        *family_out = AF_INET6;
        return 0;
    }

    struct addrinfo hints;
    struct addrinfo *res = NULL;
    int rc;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_UNSPEC;

    rc = getaddrinfo(server, "53", &hints, &res);
    if (rc != 0 || res == NULL) {
        return -1;
    }

    if (res->ai_family == AF_INET) {
        memcpy(addr, res->ai_addr, sizeof(struct sockaddr_in));
        *addrlen = (socklen_t)sizeof(struct sockaddr_in);
        *family_out = AF_INET;
    } else if (res->ai_family == AF_INET6) {
        memcpy(addr, res->ai_addr, sizeof(struct sockaddr_in6));
        *addrlen = (socklen_t)sizeof(struct sockaddr_in6);
        *family_out = AF_INET6;
    } else {
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);
    return 0;
}

static int build_query(unsigned char *buf, size_t buflen, uint16_t id, const char *name, int qtype) {
    size_t qname_len;
    size_t offset = 0;

    if (buflen < 12) {
        return -1;
    }

    memset(buf, 0, buflen);
    write_u16(buf + 0, id);
    write_u16(buf + 2, 0x0100);
    write_u16(buf + 4, 1);
    write_u16(buf + 6, 0);
    write_u16(buf + 8, 0);
    write_u16(buf + 10, 0);
    offset = 12;

    qname_len = encode_qname(buf + offset, buflen - offset, name);
    if (qname_len == 0) {
        return -1;
    }
    offset += qname_len;

    if (offset + 4 > buflen) {
        return -1;
    }

    write_u16(buf + offset, (uint16_t)qtype);
    write_u16(buf + offset + 2, DNS_CLASS_IN);
    offset += 4;
    return (int)offset;
}

static int print_answers(const unsigned char *buf, size_t len, uint16_t id) {
    if (len < 12) {
        fprintf(stderr, "short DNS response\n");
        return -1;
    }

    uint16_t resp_id = read_u16(buf + 0);
    uint16_t flags = read_u16(buf + 2);
    uint16_t qdcount = read_u16(buf + 4);
    uint16_t ancount = read_u16(buf + 6);

    if (resp_id != id) {
        fprintf(stderr, "mismatched DNS transaction id\n");
        return -1;
    }

    if ((flags & 0x8000) == 0) {
        fprintf(stderr, "not a DNS response\n");
        return -1;
    }

    if ((flags & 0x000f) != 0) {
        fprintf(stderr, "DNS error rcode=%u\n", flags & 0x000f);
        return -1;
    }

    size_t offset = 12;
    for (uint16_t i = 0; i < qdcount; i++) {
        ssize_t skip = skip_name(buf, len, offset);
        if (skip < 0 || offset + (size_t)skip + 4 > len) {
            fprintf(stderr, "truncated DNS question\n");
            return -1;
        }
        offset += (size_t)skip + 4;
    }

    int printed = 0;

    for (uint16_t i = 0; i < ancount && offset < len; i++) {
        char name[256];
        size_t consumed = 0;
        ssize_t skip = decode_name(buf, len, offset, name, sizeof(name), &consumed);
        if (skip < 0 || offset + consumed + 10 > len) {
            fprintf(stderr, "truncated DNS answer\n");
            return -1;
        }
        offset += consumed;

        uint16_t type = read_u16(buf + offset);
        uint16_t class = read_u16(buf + offset + 2);
        uint16_t rdlen = read_u16(buf + offset + 8);
        offset += 10;

        if (offset + rdlen > len) {
            fprintf(stderr, "truncated DNS rdata\n");
            return -1;
        }

        if (class == DNS_CLASS_IN && type == DNS_TYPE_A && rdlen == 4) {
            char ip[INET_ADDRSTRLEN];
            if (inet_ntop(AF_INET, buf + offset, ip, sizeof(ip)) != NULL) {
                printf("%s\n", ip);
                printed = 1;
            }
        } else if (class == DNS_CLASS_IN && type == DNS_TYPE_AAAA && rdlen == 16) {
            char ip[INET6_ADDRSTRLEN];
            if (inet_ntop(AF_INET6, buf + offset, ip, sizeof(ip)) != NULL) {
                printf("%s\n", ip);
                printed = 1;
            }
        } else if (class == DNS_CLASS_IN && type == DNS_TYPE_CNAME) {
            char cname[256];
            size_t cname_consumed = 0;
            if (decode_name(buf, len, offset, cname, sizeof(cname), &cname_consumed) == 0) {
                printf("%s CNAME %s\n", name, cname);
                printed = 1;
            }
        }

        offset += rdlen;
    }

    if (!printed) {
        fprintf(stderr, "no address records found\n");
        return -1;
    }

    return 0;
}

static int perform_query(const char *server, const char *name, int qtype) {
    unsigned char query[DNS_MAX_PACKET];
    unsigned char response[DNS_MAX_PACKET];
    struct sockaddr_storage dest;
    socklen_t destlen = 0;
    int family = AF_INET;
    int sockfd;
    int query_len;
    uint16_t id;

    if (resolve_server(server, &dest, &destlen, &family) != 0) {
        fprintf(stderr, "unable to resolve nameserver: %s\n", server);
        return -1;
    }

    sockfd = socket(family, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    struct timeval tv = {
        .tv_sec = 3,
        .tv_usec = 0
    };
    (void)setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    id = (uint16_t)(((unsigned)time(NULL) ^ (unsigned)getpid()) & 0xffff);
    query_len = build_query(query, sizeof(query), id, name, qtype);
    if (query_len < 0) {
        fprintf(stderr, "failed to build DNS query\n");
        close(sockfd);
        return -1;
    }

    if (sendto(sockfd, query, (size_t)query_len, 0, (struct sockaddr *)&dest, destlen) < 0) {
        perror("sendto");
        close(sockfd);
        return -1;
    }

    ssize_t received = recvfrom(sockfd, response, sizeof(response), 0, NULL, NULL);
    close(sockfd);

    if (received < 0) {
        perror("recvfrom");
        return -1;
    }

    return print_answers(response, (size_t)received, id);
}

int dnscli_main(int argc, char **argv) {
    const char *name;
    const char *server = "8.8.8.8";
    int qtype = DNS_TYPE_A;

    if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "usage: %s <name> [nameserver] [A|AAAA|CNAME]\n", argv[0]);
        return 1;
    }

    name = argv[1];
    if (argc >= 3) {
        server = argv[2];
    }
    if (argc >= 4) {
        qtype = parse_qtype(argv[3]);
        if (qtype < 0) {
            fprintf(stderr, "unknown query type: %s\n", argv[3]);
            return 1;
        }
    }

    return perform_query(server, name, qtype) == 0 ? 0 : 1;
}

int main(int argc, char **argv) {
    return dnscli_main(argc, argv);
}
