#include "bigint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void bi_reserve(BigInt *a, size_t cap) {
    if (cap <= a->cap) return;
    size_t new_cap = a->cap ? a->cap : 4;
    while (new_cap < cap) new_cap *= 2;
    uint32_t *nd = (uint32_t *)realloc(a->d, new_cap * sizeof(uint32_t));
    if (!nd) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    a->d = nd;
    a->cap = new_cap;
}

static void bi_normalize(BigInt *a) {
    while (a->len > 0 && a->d[a->len - 1] == 0) a->len--;
}

void bi_init(BigInt *a) {
    a->d = NULL;
    a->len = 0;
    a->cap = 0;
}

void bi_free(BigInt *a) {
    free(a->d);
    a->d = NULL;
    a->len = 0;
    a->cap = 0;
}

void bi_from_u64(BigInt *a, uint64_t v) {
    bi_reserve(a, 3);
    a->len = 0;
    if (v == 0) return;
    while (v) {
        a->d[a->len++] = (uint32_t)(v % BI_BASE);
        v /= BI_BASE;
    }
}

void bi_copy(BigInt *dst, const BigInt *src) {
    bi_reserve(dst, src->len);
    memcpy(dst->d, src->d, src->len * sizeof(uint32_t));
    dst->len = src->len;
}

void bi_move(BigInt *dst, BigInt *src) {
    bi_free(dst);
    *dst = *src;
    bi_init(src);
}

void bi_add(BigInt *out, const BigInt *a, const BigInt *b) {
    size_t max = a->len > b->len ? a->len : b->len;
    bi_reserve(out, max + 1);
    uint64_t carry = 0;
    for (size_t i = 0; i < max; i++) {
        uint64_t av = i < a->len ? a->d[i] : 0;
        uint64_t bv = i < b->len ? b->d[i] : 0;
        uint64_t sum = av + bv + carry;
        out->d[i] = (uint32_t)(sum % BI_BASE);
        carry = sum / BI_BASE;
    }
    out->len = max;
    if (carry) out->d[out->len++] = (uint32_t)carry;
}

void bi_sub(BigInt *out, const BigInt *a, const BigInt *b) {
    bi_reserve(out, a->len);
    int64_t carry = 0;
    for (size_t i = 0; i < a->len; i++) {
        int64_t av = a->d[i];
        int64_t bv = i < b->len ? b->d[i] : 0;
        int64_t val = av - bv + carry;
        if (val < 0) {
            val += BI_BASE;
            carry = -1;
        } else {
            carry = 0;
        }
        out->d[i] = (uint32_t)val;
    }
    out->len = a->len;
    bi_normalize(out);
}

void bi_mul_small(BigInt *out, const BigInt *a, uint32_t m) {
    if (a->len == 0 || m == 0) {
        out->len = 0;
        return;
    }
    bi_reserve(out, a->len + 1);
    uint64_t carry = 0;
    for (size_t i = 0; i < a->len; i++) {
        uint64_t prod = (uint64_t)a->d[i] * m + carry;
        out->d[i] = (uint32_t)(prod % BI_BASE);
        carry = prod / BI_BASE;
    }
    out->len = a->len;
    if (carry) out->d[out->len++] = (uint32_t)carry;
}

void bi_mul(BigInt *out, const BigInt *a, const BigInt *b) {
    if (a->len == 0 || b->len == 0) {
        out->len = 0;
        return;
    }
    bi_reserve(out, a->len + b->len);
    memset(out->d, 0, (a->len + b->len) * sizeof(uint32_t));
    for (size_t i = 0; i < a->len; i++) {
        uint64_t carry = 0;
        for (size_t j = 0; j < b->len; j++) {
            uint64_t cur = out->d[i + j] + (uint64_t)a->d[i] * b->d[j] + carry;
            out->d[i + j] = (uint32_t)(cur % BI_BASE);
            carry = cur / BI_BASE;
        }
        size_t pos = i + b->len;
        while (carry) {
            uint64_t cur = out->d[pos] + carry;
            out->d[pos] = (uint32_t)(cur % BI_BASE);
            carry = cur / BI_BASE;
            pos++;
        }
    }
    out->len = a->len + b->len;
    bi_normalize(out);
}

int bi_cmp(const BigInt *a, const BigInt *b) {
    if (a->len != b->len) return a->len < b->len ? -1 : 1;
    for (size_t i = a->len; i > 0; i--) {
        uint32_t av = a->d[i - 1];
        uint32_t bv = b->d[i - 1];
        if (av != bv) return av < bv ? -1 : 1;
    }
    return 0;
}

size_t bi_decimal_len(const BigInt *a) {
    if (a->len == 0) return 1;
    uint32_t top = a->d[a->len - 1];
    size_t digits = 0;
    while (top) {
        top /= 10;
        digits++;
    }
    return (a->len - 1) * BI_BASE_DIGITS + digits;
}

char *bi_to_str(const BigInt *a) {
    if (a->len == 0) {
        char *z = (char *)malloc(2);
        if (!z) return NULL;
        z[0] = '0';
        z[1] = '\0';
        return z;
    }
    size_t len = bi_decimal_len(a);
    char *s = (char *)malloc(len + 1);
    if (!s) return NULL;
    char *p = s;
    size_t i = a->len - 1;
    int n = snprintf(p, len + 1, "%u", a->d[i]);
    p += n;
    while (i-- > 0) {
        snprintf(p, len + 1 - (size_t)(p - s), "%09u", a->d[i]);
        p += BI_BASE_DIGITS;
    }
    return s;
}
