// RSA.h
#ifndef RSA_H
#define RSA_H

#include "config.h"
#include "math.h" // Needed for key generation functions

// RSA Key Structure must be 16-bit
typedef struct {
    uint16_t n;   // modulus
    uint16_t e;   // public exponent
    uint16_t d;   // private exponent
} RSA_Key; 

// Generate RSA key from small primes p, q
uint8_t rsa_generate_key(uint8_t p, uint8_t q, RSA_Key *key);

// Encrypt 16-bit plaintext
void rsa_encrypt(uint16_t plaintext, uint16_t *ciphertext, RSA_Key *key); 

// Decrypt 16-bit ciphertext
void rsa_decrypt(uint16_t ciphertext, uint16_t *plaintext, RSA_Key *key); 

#endif /* RSA_H */