

# RSA on 8051 Microcontroller

This repository presents a **lightweight educational implementation of the RSA public-key cryptosystem** on the **8051 microcontroller**, using UART for data input/output. The project is intended for learning purposes and demonstrates how asymmetric cryptography can be adapted to resource-constrained embedded systems.

---

## RSA Algorithm (Brief Overview)

RSA operates on three main steps:

1. **Key Generation**
   - Choose two prime numbers `p` and `q`
   - Compute `n = p × q`
   - Compute Euler’s totient: `φ(n) = (p−1)(q−1)`
   - Choose public exponent `e` such that `gcd(e, φ(n)) = 1`
   - Compute private exponent `d` where `e × d ≡ 1 (mod φ(n))`

2. **Encryption**
   - Ciphertext:  
     ```
     C = M^e mod n
     ```

3. **Decryption**
   - Plaintext recovery:  
     ```
     M = C^d mod n
     ```

---

## 8051 Size and Resource Constraints

Due to the limited memory and lack of hardware multiplication/division on the 8051:

- All RSA values (`n`, `e`, `d`, plaintext, ciphertext) use **32-bit unsigned integers**
- No dynamic memory allocation is used
- Modular exponentiation is implemented using **iterative multiplication**
- Key sizes are intentionally **small and insecure by modern standards**
- This implementation is **for educational and demonstration purposes only**


---

## Hardware Setup

- 8051 Microcontroller
- UART interface (TTL level)
- Virtual Terminal (Proteus) or USB-to-TTL module

---

## Project Structure


## Project Files and Their Purpose

- **`main.c`**  
  The main program entry point. Initializes UART, sets up RSA keys, reads input from the port or UART, performs encryption/decryption, and sends results back via UART.

- **`rsa.c`**  
  Contains the implementation of the RSA algorithm functions, including modular exponentiation, encryption, and decryption routines.

- **`rsa.h`**  
  Header file declaring the RSA structures and function prototypes for use in `main.c` or other modules.

- **`uart.c`**  
  Implements UART communication functions, including initialization, sending, and receiving bytes for data exchange with a PC or virtual terminal.

- **`uart.h`**  
  Header file declaring UART function prototypes and configuration constants for baud rate and hardware settings.

- **`config.h`**  
  Central configuration file containing microcontroller-specific settings (e.g., oscillator frequency), data types, and any project-wide constants.





<img width="1561" height="697" alt="image" src="https://github.com/user-attachments/assets/d3d96125-5b32-49b8-9b08-b59f3c6cbf3e" />



