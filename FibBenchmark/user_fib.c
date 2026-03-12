#include "user_fib.h"
#include "bigint.h"
#include <limits.h>

void fib_user(int64_t n, BigInt *out, int *sign) {
    BigInt a, b, p, q;
    bi_init(&a);
    bi_init(&b);
    bi_init(&p);
    bi_init(&q);

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

    /* SICP-style fast doubling with (a,b,p,q) invariants. */
    bi_from_u64(&a, 1);
    bi_from_u64(&b, 0);
    bi_from_u64(&p, 0);
    bi_from_u64(&q, 1);

    while (1) {
        if (un == 0) {
            bi_move(out, &b);
            break;
        } else if ((un & 1u) == 0) {
            /* p, q = p^2 + q^2, q^2 + 2*p*q */
            BigInt p2, q2, pq, two_pq, new_p, new_q;
            bi_init(&p2);
            bi_init(&q2);
            bi_init(&pq);
            bi_init(&two_pq);
            bi_init(&new_p);
            bi_init(&new_q);

            bi_mul(&p2, &p, &p);
            bi_mul(&q2, &q, &q);
            bi_add(&new_p, &p2, &q2);

            bi_mul(&pq, &p, &q);
            bi_mul_small(&two_pq, &pq, 2);
            bi_add(&new_q, &q2, &two_pq);

            bi_move(&p, &new_p);
            bi_move(&q, &new_q);

            bi_free(&p2);
            bi_free(&q2);
            bi_free(&pq);
            bi_free(&two_pq);
            un >>= 1;
        } else {
            /* a, b = b*q + a*q + a*p, b*p + a*q */
            BigInt bq, aq, ap, bp, new_a, new_b, tmp;
            bi_init(&bq);
            bi_init(&aq);
            bi_init(&ap);
            bi_init(&bp);
            bi_init(&new_a);
            bi_init(&new_b);
            bi_init(&tmp);

            bi_mul(&bq, &b, &q);
            bi_mul(&aq, &a, &q);
            bi_mul(&ap, &a, &p);
            bi_add(&tmp, &bq, &aq);
            bi_add(&new_a, &tmp, &ap);

            bi_mul(&bp, &b, &p);
            bi_add(&new_b, &bp, &aq);

            bi_move(&a, &new_a);
            bi_move(&b, &new_b);

            bi_free(&bq);
            bi_free(&aq);
            bi_free(&ap);
            bi_free(&bp);
            bi_free(&tmp);
            un -= 1;
        }
    }

    bi_free(&a);
    bi_free(&b);
    bi_free(&p);
    bi_free(&q);
}
