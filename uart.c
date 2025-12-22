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




/* ================= recive 1byte decimal number ================= */

// Receive a 1-byte decimal number (0-255) via 3 ASCII digits or Enter
uint8_t uart_receive_decimal(void) {
    uint8_t count = 0;
    uint8_t digits[3] = {0, 0, 0};
    char received;
    uint16_t result = 0;

    for (count = 0; count < 3; count++) {
        received = uart_receive_byte();

        // Check if user pressed "Enter" (ASCII 13)
        if (received == '\r' || received == '\n') {
            if (count == 0) return 0; // "Enter" on first digit = 0
            break; // Stop receiving and calculate what we have
        }

        // Convert ASCII to actual number (e.g., '1' becomes 1)
        // Standard ASCII offset is 48. 
        digits[count] = received - 48; 
    }

    // Logic for shifting digits based on how many were entered
    if (count == 1) {
        // Only one digit was entered before Enter or filling up
        result = digits[0];
    } 
    else if (count == 2) {
        // Two digits: [0] is tens, [1] is units
        result = (digits[0] * 10) + digits[1];
    } 
    else if (count == 3) {
        // Three digits: [0] is hundreds, [1] is tens, [2] is units
        result = (digits[0] * 100) + (digits[1] * 10) + digits[2];
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    // Ensure it fits in 8-bit (max 255)
    return (uint8_t)(result > 255 ? 255 : result);
}
