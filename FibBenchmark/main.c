#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>
#include "bigint.h"
#include "user_fib.h"

static uint64_t now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static void fib_ref_fd(uint64_t n, BigInt *f, BigInt *g) {
    if (n == 0) {
        bi_from_u64(f, 0);
        bi_from_u64(g, 1);
        return;
    }

    BigInt a, b;
    bi_init(&a);
    bi_init(&b);
    fib_ref_fd(n >> 1, &a, &b);

    BigInt two_b, two_b_minus_a, c, a2, b2, d;
    bi_init(&two_b);
    bi_init(&two_b_minus_a);
    bi_init(&c);
    bi_init(&a2);
    bi_init(&b2);
    bi_init(&d);

    bi_mul_small(&two_b, &b, 2);
    bi_sub(&two_b_minus_a, &two_b, &a);
    bi_mul(&c, &a, &two_b_minus_a);

    bi_mul(&a2, &a, &a);
    bi_mul(&b2, &b, &b);
    bi_add(&d, &a2, &b2);

    if ((n & 1u) == 0) {
        bi_move(f, &c);
        bi_move(g, &d);
    } else {
        BigInt c_plus_d;
        bi_init(&c_plus_d);
        bi_add(&c_plus_d, &c, &d);
        bi_move(f, &d);
        bi_move(g, &c_plus_d);
    }

    bi_free(&a);
    bi_free(&b);
    bi_free(&two_b);
    bi_free(&two_b_minus_a);
    bi_free(&a2);
    bi_free(&b2);
    bi_free(&c);
    bi_free(&d);
}

static void fib_ref(int64_t n, BigInt *out, int *sign) {
    uint64_t un;
    if (n < 0) {
        if (n == INT64_MIN) {
            un = (uint64_t)INT64_MAX + 1u;
        } else {
            un = (uint64_t)(-n);
        }
        *sign = (un % 2u == 0) ? -1 : 1;
    } else {
        un = (uint64_t)n;
        *sign = 1;
    }

    BigInt f, g;
    bi_init(&f);
    bi_init(&g);
    fib_ref_fd(un, &f, &g);
    bi_move(out, &f);
    bi_free(&g);
}

static void bench_one(const char *label, void (*fn)(int64_t, BigInt *, int *), int64_t n,
                      int runs, int warmup, int print_len, int print_num,
                      int verify) {
    BigInt out;
    bi_init(&out);
    int sign = 1;

    for (int i = 0; i < warmup; i++) {
        fn(n, &out, &sign);
        bi_free(&out);
        bi_init(&out);
    }

    uint64_t min = UINT64_MAX, max = 0, sum = 0;
    for (int i = 0; i < runs; i++) {
        uint64_t t0 = now_ns();
        fn(n, &out, &sign);
        uint64_t t1 = now_ns();
        uint64_t dt = t1 - t0;
        if (dt < min) min = dt;
        if (dt > max) max = dt;
        sum += dt;

        if (verify) {
            BigInt ref;
            bi_init(&ref);
            int ref_sign = 1;
            fib_ref(n, &ref, &ref_sign);
            if (sign != ref_sign || bi_cmp(&out, &ref) != 0) {
                fprintf(stderr, "Verification failed for %s at n=%lld\n", label,
                        (long long)n);
                bi_free(&ref);
                bi_free(&out);
                exit(2);
            }
            bi_free(&ref);
        }

        if (i + 1 < runs) {
            bi_free(&out);
            bi_init(&out);
        }
    }

    double avg_ms = (double)sum / (double)runs / 1e6;
    printf("%s: n=%lld runs=%d warmup=%d\n", label, (long long)n, runs, warmup);
    printf("  min=%.3f ms  avg=%.3f ms  max=%.3f ms\n",
           (double)min / 1e6, avg_ms, (double)max / 1e6);

    if (print_len) {
        printf("  digits=%zu\n", bi_decimal_len(&out));
    }
    if (print_num) {
        char *s = bi_to_str(&out);
        if (!s) {
            fprintf(stderr, "Out of memory while printing\n");
            bi_free(&out);
            exit(1);
        }
        if (sign < 0 && out.len != 0) {
            printf("  value=-%s\n", s);
        } else {
            printf("  value=%s\n", s);
        }
        free(s);
    }

    bi_free(&out);
}

static void usage(const char *prog) {
    printf("Usage: %s [options]\n", prog);
    printf("Options:\n");
    printf("  --n N            Fibonacci index (can be negative; default 100000)\n");
    printf("  --runs N         Number of timed runs (default 3)\n");
    printf("  --warmup N       Warmup runs (default 1)\n");
    printf("  --mode M         user | ref | both (default user)\n");
    printf("  --verify         Verify user result against ref\n");
    printf("  --print-len      Print decimal digit count\n");
    printf("  --print          Print the full number (slow)\n");
    printf("  --help           Show this help\n");
}

int main(int argc, char **argv) {
    int64_t n = 100000;
    int runs = 3;
    int warmup = 1;
    int verify = 0;
    int print_len = 0;
    int print_num = 0;
    const char *mode = "user";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--n") == 0 && i + 1 < argc) {
            n = (int64_t)strtoll(argv[++i], NULL, 10);
        } else if (strcmp(argv[i], "--runs") == 0 && i + 1 < argc) {
            runs = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
            warmup = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
            mode = argv[++i];
        } else if (strcmp(argv[i], "--verify") == 0) {
            verify = 1;
        } else if (strcmp(argv[i], "--print-len") == 0) {
            print_len = 1;
        } else if (strcmp(argv[i], "--print") == 0) {
            print_num = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            usage(argv[0]);
            return 1;
        }
    }

    if (runs <= 0) runs = 1;
    if (warmup < 0) warmup = 0;

    if (strcmp(mode, "user") == 0) {
        bench_one("user", fib_user, n, runs, warmup, print_len, print_num, verify);
    } else if (strcmp(mode, "ref") == 0) {
        bench_one("ref", fib_ref, n, runs, warmup, print_len, print_num, 0);
    } else if (strcmp(mode, "both") == 0) {
        bench_one("user", fib_user, n, runs, warmup, print_len, print_num, verify);
        bench_one("ref", fib_ref, n, runs, warmup, print_len, print_num, 0);
    } else {
        fprintf(stderr, "Invalid mode: %s\n", mode);
        return 1;
    }

    return 0;
}
