#ifndef BIGINT_H
#define BIGINT_H

#include <stdint.h>
#include <stddef.h>

#define BI_BASE 1000000000u
#define BI_BASE_DIGITS 9

typedef struct {
    uint32_t *d;
    size_t len;
    size_t cap;
} BigInt;

void bi_init(BigInt *a);
void bi_free(BigInt *a);
void bi_from_u64(BigInt *a, uint64_t v);
void bi_copy(BigInt *dst, const BigInt *src);
void bi_move(BigInt *dst, BigInt *src);
void bi_add(BigInt *out, const BigInt *a, const BigInt *b);
void bi_sub(BigInt *out, const BigInt *a, const BigInt *b); /* assumes a >= b */
void bi_mul(BigInt *out, const BigInt *a, const BigInt *b);
void bi_mul_small(BigInt *out, const BigInt *a, uint32_t m);
int  bi_cmp(const BigInt *a, const BigInt *b);
size_t bi_decimal_len(const BigInt *a);
char *bi_to_str(const BigInt *a); /* malloc'd string */

#endif
