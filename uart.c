#include "uart.h"

#define TH1_VALUE (256 - (F_CPU / 12 / 32 / BAUD_RATE))  // Timer 1 reload value

// Initialize UART
void uart_init(void) {
    SCON = 0x50;  // UART mode 1, 8-bit data, REN enabled
    TMOD |= 0x20; // Timer 1, mode 2 (8-bit auto-reload)
    TH1 = TH1_VALUE;
    TL1 = TH1_VALUE;
    TR1 = 1;      // Start Timer 1
    TI = 1;       // Set TI to indicate ready to send
}

// Send a single byte
void uart_send_byte(char c) {
    SBUF = c;
    while (TI == 0);  // Wait until transmission complete
    TI = 0;           // Clear TI flag
}

// Receive a single byte
char uart_receive_byte(void) {
    while (RI == 0);  // Wait until a byte is received
    RI = 0;           // Clear RI flag
    return SBUF;      // Return received byte
}

/* ================= Added Functions Only ================= */

// Send a 2-byte word (MSB first)
void uart_send_word(uint16_t word) {
    uart_send_byte((word >> 8) & 0xFF);  // High byte
    uart_send_byte(word & 0xFF);         // Low byte
}

// Receive a 2-byte word (MSB first)
uint16_t uart_receive_word(void) {
    uint16_t word;
    word  = ((uint16_t)uart_receive_byte()) << 8; // High byte
    word |= (uint16_t)uart_receive_byte();        // Low byte
    return word;
}
