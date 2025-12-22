// RSA.h
#ifndef RSA_H
#define RSA_H

#include "config.h"

typedef struct {
    uint16_t n;   
    uint16_t e;   
    uint16_t d;   
} RSA_Key; 

/* Updated to accept e_val as a parameter instead of reading a Port */
uint8_t rsa_generate_key(uint8_t p, uint8_t q, uint16_t e_val, RSA_Key *key);

void rsa_encrypt(uint16_t plaintext, uint16_t *ciphertext, RSA_Key *key); 
void rsa_decrypt(uint16_t ciphertext, uint16_t *plaintext, RSA_Key *key); 

#endif