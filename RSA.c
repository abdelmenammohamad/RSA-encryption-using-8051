// RSA.c
#include "RSA.h"
#include "config.h" 
#include "math.h" 

/* ---------------- RSA Functions ---------------- */

// Generate RSA key from p, q, e (Now calculates 16-bit n, phi, d)
#include <reg51.h> // Required for P1 access
#include "RSA.h"
#include "config.h" 
#include "math.h" 

/**
 * Generate RSA key using e from Port 1
 * Returns TRUE (1) if successful, FALSE (0) if GCD(e, phi) != 1
 */
uint8_t rsa_generate_key(uint8_t p, uint8_t q, RSA_Key *key) {
    uint16_t n, phi, d, e_val;

    // Calculate modulus and totient
    n = (uint16_t)p * (uint16_t)q;
    phi = (uint16_t)(p - 1) * (uint16_t)(q - 1);

    // Read the 8-bit value from Port 1 and treat it as the public exponent
    e_val = (uint16_t)P1;

    // RSA requirement: e must be coprime to phi, and usually e > 1
    if (e_val <= 1 || gcd(e_val, phi) != 1) {
        return FALSE; // Validation failed
    }

    // Calculate private exponent
    d = mod_inverse(e_val, phi);

    // Store in structure
    key->n = n;
    key->e = e_val;
    key->d = d;

    return TRUE; // Success
}

// Encrypt 16-bit plaintext
void rsa_encrypt(uint16_t plaintext, uint16_t *ciphertext, RSA_Key *key) {
    *ciphertext = mod_exp(plaintext, key->e, key->n);
}

// Decrypt 16-bit ciphertext
void rsa_decrypt(uint16_t ciphertext, uint16_t *plaintext, RSA_Key *key) {
    *plaintext = mod_exp(ciphertext, key->d, key->n);
}