#ifndef CONFIG_H
#define CONFIG_H

/* ================= Clock Configuration ================= */
#define F_CPU       11059200UL     /* 11.0592 MHz crystal */

/* ================= UART Configuration ================= */
#define BAUD_RATE    9600

/* ================= RSA Constraints ================= */
/* p and q are restricted to 1 byte as per project rules */
#define RSA_KEY_SIZE_BYTES   1

/* Fermat primality test security level */
#define FERMAT_ROUNDS        5

/* ================= Data Types ================= */

typedef unsigned char  uint8_t;
typedef signed	char    int8;
typedef unsigned int  uint16_t;
typedef unsigned long  uint32_t;


/* ================= Boolean ================= */
#define TRUE    1
#define FALSE   0

#endif /* CONFIG_H */
