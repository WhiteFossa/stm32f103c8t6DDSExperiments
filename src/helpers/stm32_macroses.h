/**
 *  Various macroses for Fossa's STM32 library.
 */

/**
 * Returns 2^B, i.e. 1 at Bth position starting from zero.
 */
#define BV(B) (1U << B)

/**
 * Masks-out higher word.
 */
#define MASKH(V) (0x0000FFFFU & V)

/**
 * Masks-out lower word.
 */
#define MASKL(V) (0xFFFF0000U & V)
