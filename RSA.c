// RSA.c
#include "RSA.h"
#include "math.h" 

/**
 * Generate RSA key using provided e_val
 * Returns TRUE if successful, FALSE if GCD(e, phi) != 1
 */
uint8_t rsa_generate_key(uint8_t p, uint8_t q, uint16_t e_val, RSA_Key *key) {
    uint16_t n, phi, d;

    n = (uint16_t)p * (uint16_t)q;
    phi = (uint16_t)(p - 1) * (uint16_t)(q - 1);

    // Validation: e must be coprime to phi and e > 1
    if (e_val <= 1 || gcd(e_val, phi) != 1) {
        return FALSE; 
    }

    // Calculate private exponent
    d = mod_inverse(e_val, phi);

    key->n = n;
    key->e = e_val;
    key->d = d;

    return TRUE; 
}

void rsa_encrypt(uint16_t plaintext, uint16_t *ciphertext, RSA_Key *key) {
    *ciphertext = mod_exp(plaintext, key->e, key->n);
}

void rsa_decrypt(uint16_t ciphertext, uint16_t *plaintext, RSA_Key *key) {
    *plaintext = mod_exp(ciphertext, key->d, key->n);
}