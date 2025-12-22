// math.c 
#include "math.h"
#include "config.h" // Includes uint32_t

/* ================= Modular Exponentiation ================= */
//Computes (base^exp) % mod using square-and-multiply
uint16_t mod_exp(uint16_t base, uint16_t exp, uint16_t mod) // Changed return type to uint16_t
{
    char exp_size = 16;
    uint32_t result;
		base = base % mod;
    if (exp == 0) return (uint16_t)1;

    //move the MSB of exp till it react max index
    while (!(exp & 0x8000)) {
        exp = exp << 1;
        exp_size = exp_size - 1;
    }

    //for MSB in exp
    result = base;
    exp = exp << 1;
    //for the rest of the bits
    while ((exp != 0) || (exp_size > 1)) {
        result = (result * result) % mod;
        if ((exp & 0x8000)) result = (result * base) % mod;
        exp = exp << 1;
        exp_size = exp_size - 1;
    }

    return result;
}
/* ================= Modular Exponentiation(another method with less one varibale) ================= */
/* Computes (base^exp) % mod using square-and-multiply */
/*uint16_t mod_exp(uint16_t base, uint16_t exp, uint16_t mod)
{
    uint32_t result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }

    return (uint16_t)result;
}
*/


/* ================= GCD ================= */
/* Euclidean Algorithm */
uint16_t gcd(uint16_t a, uint16_t b) // Changed return type to uint16_t for consistency
{
    uint16_t temp;
// ... (rest of the function is correct) ...
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* ================= Modular Inverse ================= */
/* Extended Euclidean Algorithm (iterative) */
/* ================= Modular Inverse ================= */
/* Extended Euclidean Algorithm (iterative) */
uint16_t mod_inverse(uint16_t e, uint16_t phi) 
{
    long t = 0;
    long newt = 1;
    long r = phi;     // Initial remainder 0 is phi
    long newr = e;    // Initial remainder 1 is e
    long q, tmp;

    // The loop continues until the remainder becomes 0
    while (newr != 0) {
        q = r / newr; // Calculate quotient

        // Update t and newt (coefficients)
        tmp = newt;
        newt = t - (q * newt);
        t = tmp;

        // Update r and newr (remainders)
        tmp = newr;
        newr = r - (q * newr);
        r = tmp;
    }

    // After the loop, r should be the GCD. If GCD > 1, no inverse exists.
    if (r > 1) return 0; 

    // Ensure the result is positive
    if (t < 0) {
        t = t + phi;
    }

    return (uint16_t)t; // Cast back to 16-bit for RSA key structure
}

/* ================= fermat_test ================= */

uint8_t fermat_test(uint8_t x) {
    // 1. Basic cases: 0, 1 are not prime; 2, 3 are prime
    if (x <= 1) return FALSE;
    if (x == 2 || x == 3) return TRUE;
    
    // 2. Even numbers greater than 2 are not prime
    if (x % 2 == 0) return FALSE;

    // 3. Fermat's Little Theorem: a^(n-1) = 1 (mod n)
    // We use base 2 for the calculation
    if (mod_exp(2, x - 1, x) == 1) {
        return TRUE;
    }

    return FALSE;
}