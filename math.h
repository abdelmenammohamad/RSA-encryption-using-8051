#ifndef MATH_H
#define MATH_H

#include "config.h"

/* ================= Primality Test ================= */
/* Fermat primality test (returns TRUE or FALSE) */
uint8_t fermat_test(uint8_t x);

/* ================= Number Theory ================= */
/* Greatest Common Divisor */
uint16_t gcd(uint16_t a, uint16_t b);

/* Modular multiplicative inverse using Extended Euclidean Algorithm */
uint16_t mod_inverse(uint16_t e, uint16_t phi);

/* ================= Modular Arithmetic ================= */
/* Modular exponentiation: (base^exp) mod mod */
uint16_t mod_exp(uint16_t base, uint16_t exp, uint16_t mod);

/* ================= Primality Test ================= */
/* Fermat primality test (returns TRUE or FALSE) */
/* For 8-bit numbers, we use base 2 for the test */
uint8_t fermat_test(uint8_t x);

#endif /* MATH_H */
