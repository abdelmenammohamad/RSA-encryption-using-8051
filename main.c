#include <reg51.h>
#include "uart.h"
#include "RSA.h"
#include "math.h"
#include "config.h"

/* ================= Hardware Definitions ================= */
sbit S0 = P3^3;              // Mode bit 0
sbit S1 = P3^4;              // Mode bit 1

sbit ERROR_LED = P2^0;       // LED turns ON if primality (p, q) fails
sbit E_ERROR_LED = P2^1;     // NEW: LED turns ON if public exponent (e) fails

/* ================= Global Variables ================= */
RSA_Key key;
uint8_t setup_done = FALSE;   
uint8_t e_sent = FALSE;       

/* Function to handle Mode 00: Setup */
/* Function to handle Mode 00: Setup */
void handle_setup(void) {
    uint8_t p_val, q_val;
    
    if (setup_done == TRUE) {
        e_sent = FALSE; 
        return;
    }

    // 1. Loop for P
    while (1) {
        p_val = (uint8_t)uart_receive_byte();
				P0=p_val;
        if (fermat_test(p_val) == TRUE) {
            ERROR_LED = 0;      // P is valid
            uart_send_byte('P'); // Acknowledge P is OK
            uart_send_byte('\n');
            break; 
        } else {
            ERROR_LED = 1;      // P failed
            uart_send_byte('R'); // Request retry for P
        }
    }

    // 2. Loop for Q
    while (1) {
        q_val = (uint8_t)uart_receive_byte(); 
        if (fermat_test(q_val) == TRUE) {
            ERROR_LED = 0;      // Q is valid
            uart_send_byte('Q'); // Acknowledge Q is OK
            uart_send_byte('\n');
            break; 
        } else {
            ERROR_LED = 1;      // Q failed
            uart_send_byte('R'); // Request retry for Q
        }
    }

    // 3. Loop for E and Key Generation
    while (1) {
        // Try to generate key using e from Port 1
        if (rsa_generate_key(p_val, q_val, &key) == TRUE) {
            E_ERROR_LED = 0;      
            uart_send_byte('O'); 
            uart_send_byte('K');
            uart_send_byte('\n'); 
            setup_done = TRUE;
            e_sent = FALSE;
            break; 
        } else {
            E_ERROR_LED = 1;      
            uart_send_byte('E');  // Notify UART that Port P1 value is invalid
            // In this version, we wait for the user to change P1 
            // and perhaps send a dummy byte to trigger a re-check
            uart_receive_byte(); 
        }
    }
}

void main(void) {
    uint16_t ciphertext, plaintext;
    uint8_t mode;

    uart_init();
    ERROR_LED = 0;
    E_ERROR_LED = 0; // Initialize second LED to OFF

    while (1) {
        mode = ((uint8_t)S1 << 1) | (uint8_t)S0;

        switch (mode) {
            case 0: /* Mode 00: Setup */
                handle_setup();
                break;
						
            case 1: /* Mode 01: Send public exponent e */
                if (setup_done && !e_sent) {
                    uart_send_word(key.e);
                    uart_send_byte('\n');
                    e_sent = TRUE; 
                }
                break;

            case 2: /* Mode 10: Receive byte, decrypt, and send */
                if (setup_done) {
                    ciphertext = (uint16_t)uart_receive_byte();
                    rsa_decrypt(ciphertext, &plaintext, &key);
                    uart_send_byte((uint8_t)plaintext);
                }
                break;

            case 3: /* Mode 11: Receive 16-bit ciphertext, decrypt */
                if (setup_done) {
                    ciphertext = uart_receive_word();
                    rsa_decrypt(ciphertext, &plaintext, &key);
                    uart_send_word(plaintext);
                }
                break;
        }
    }
}