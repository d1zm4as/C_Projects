/* dnscli.h */
#pragma once

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;
typedef uint64_t int64;

#define packed __attribute__((packed))
#define $v (void *)
#define $c (char *)
#define $i (int)
#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define TypeIPv4 0x0800

struct s_packet {
    struct {
        int8 dst[6];
        int8 src[6];
        int16 type;
    } e packed;

    struct {
        int8 ihl : 4;
        int8 ver : 4;
        int8 ecn : 2;
        int8 dscp : 6;
        int16 length;
        int16 id;
        int16 offset : 13;
        int8 flags : 3;
        int8 ttl;
        int8 protocol;
        int16 checksum;
        int32 src;
        int32 dst;
    } i packed;

    struct {
        int16 src;
        int16 dst;
        int16 length;
        int16 checksum;
    } u packed;

    struct {
        int16 id;
        unsigned int rd : 1;
        unsigned int tc : 1;
        unsigned int aa : 1;
        unsigned int opcode : 4;
        unsigned int qr : 1;
        unsigned int rcode : 4;
        unsigned int cd : 1;
        unsigned int ad : 1;
        unsigned int z : 1;
        unsigned int ra : 1;
        struct {
            int16 questions;
            int16 answers;
            int16 authrrs;
            int16 additionalrrs;
        } num packed;
    } d packed;
} packed;

typedef struct s_packet packet;

void zero(int8 *dst, int16 size);
packet *mrpacket(void);

int dnscli_main(int argc, char **argv);
