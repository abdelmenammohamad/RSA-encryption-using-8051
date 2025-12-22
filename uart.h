#ifndef UART_H
#define UART_H

#include <reg51.h>     // 8051 special function registers
#include "config.h"   // Global configuration (F_CPU, BAUDRATE, types)

/* Function Declarations */
void uart_init(void);           // Initialize UART
void uart_send_byte(char c);    // Send single character
char uart_receive_byte(void);   // Receive single character

/* Word (2-byte) UART Functions */
void uart_send_word(uint16_t word);   // Send 2-byte word
uint16_t uart_receive_word(void);     // Receive 2-byte word

uint8_t uart_receive_decimal(void);

#endif /* UART_H */
