#include <reg51.h>
#include "uart.h"
#include "RSA.h"
#include "math.h"
#include "config.h"

/* Hardware Definitions */
sbit MODE_PIN = P3^3;         // 0 = Setup, 1 = Operation
sbit OP_PIN   = P3^4;         // 0 = Encrypt, 1 = Decrypt
sbit ERROR_LED = P2^0;        // Primality Error
sbit E_ERROR_LED = P2^1;      // GCD Error

RSA_Key key;
uint8_t setup_done = FALSE;   // Global flag to track initialization

void handle_setup(void) {
    uint8_t p_val, q_val;
    uint16_t e_val;
    
    // Prevent re-running if already configured
    if (setup_done == TRUE) return;

    // 1. Loop for P: continues until valid prime is received
    while (1) {
        p_val = uart_receive_decimal(); 
        if (fermat_test(p_val) == TRUE) {
            ERROR_LED = 0;
						uart_send_byte('S'); //clear the buffer, due to a problem with the first send_byte
            uart_send_byte('P'); 
            break; 
        } else {
            ERROR_LED = 1;
            uart_send_byte('R'); 
        }
    }

    // 2. Loop for Q: continues until valid prime is received
    while (1) {
        q_val = uart_receive_decimal(); 
        if (fermat_test(q_val) == TRUE) {
            ERROR_LED = 0;
            uart_send_byte('Q'); 
            break; 
        } else {
            ERROR_LED = 1;
            uart_send_byte('R'); 
        }
    }

    // 3. Loop for E and Final Key Gen
    while (1) {
        e_val = (uint16_t)uart_receive_decimal(); 
        if (rsa_generate_key(p_val, q_val, e_val, &key) == TRUE) {
            E_ERROR_LED = 0;
						uart_send_byte('E'); 
            uart_send_byte('O'); 
            uart_send_byte('K');
            setup_done = TRUE; // Mark setup as complete permanently
            break; 
        } else {
            E_ERROR_LED = 1; 
						uart_send_byte('R'); 
        }
    }
}

void main(void) {
    uint16_t data_in, data_out;

    uart_init();
    ERROR_LED = 0;
    E_ERROR_LED = 0;

    while (1) {
        if (MODE_PIN == 0) {
            // Setup Mode: Only runs if setup_done is FALSE
            if (setup_done == FALSE) {
                handle_setup();
            }
        } else {
            // Operation Mode: Only active if setup has been completed once
            if (setup_done == TRUE) {
                if (OP_PIN == 0) {
                    /* Encrypt Mode */
                    // Receive 1 byte (0-255) to encrypt
                    data_in = (uint16_t)uart_receive_byte();
                    rsa_encrypt(data_in, &data_out, &key);  
                    // Send 2-byte ciphertext (MSB first)
                    uart_send_word(data_out);               
                } 
                else {
                    /* Decrypt Mode */
                    // Receive 2-byte ciphertext to decrypt
                    data_in = (uint16_t)uart_receive_byte();
										P0=(uint8_t)data_in;
                    rsa_decrypt(data_in, &data_out, &key);  
                    // Send decrypted 2-byte word (since result can be up to 16-bit n)
                    uart_send_word(data_out);               
                }
            }
        }
    }
}