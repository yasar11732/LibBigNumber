#ifndef __BN_H_
#define __BN_H_
#include <limits.h> // CHAR_BIT
#include <stdint.h>

typedef int32_t bn_size_t;
typedef uint32_t bn_digit_t;
typedef uint64_t bn_long_digit_t;

#define BN_DIGIT_BITS ((sizeof(bn_digit_t)) * CHAR_BIT)
#define BN_DIGIT_MAX ((bn_digit_t) ~ (bn_digit_t)0)
#define BN_DIGIT_HI ((bn_digit_t) (1 << (BN_DIGIT_BITS / 2)))
#define BN_DIGIT_LOWMASK (BN_DIGIT_HI - 1)

#define BN_MAX(a,b) ((a) > (b) ? (a) : (b))
#define BN_MIN(a,b) ((a) < (b) ? (a) : (b))
#define BN_ABS(a) ((a) >= 0 ? (a) : -(a))
#define BN_CMP(a,b) (((a) > (b)) - ((b) > (a)))

#if defined(__GNUC__)
#define nlz(x) __builtin_clz(x)
#elif defined(_MSC_VER)
#define nlz(x) __lzcnt(x)
#else
int nlz(unsigned int value)
{
	int i;
	for (i = 0; value; i++)
		value >>= 1;
	return 32 - i;
}
#endif

// Initialize random number generation engine with zero terminated string. strlen(key) > 4.
void init_rng(char *key);

// returns a random char
uint8_t randomc();

// fill array of digits with random numbers
void fill_random(bn_digit_t *arr, bn_size_t len);

// result = op1 + op2, where both op1 and op2 is n digits long
bn_digit_t bn_add_n(bn_digit_t *result, const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t n);

// result = op1 + op2, where op1 is n digits long, op2 is single digit
bn_digit_t bn_add_n1(bn_digit_t *result, const bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// result = op1 + op2, where op1 is n1 digits long, op2 is n2 digits long
bn_digit_t bn_add_nn(bn_digit_t *result, const bn_digit_t *op1, bn_size_t n1, const bn_digit_t *op2, bn_size_t n2);

// result = op1 * op2, where op1 is m digits long, op2 is n digits long
void bn_mul_n(bn_digit_t *result, bn_digit_t *op1, bn_size_t m, bn_digit_t *op2, bn_size_t n);

// result = op1 * op2, where op1 is n digits long, op2 is single digit
bn_digit_t bn_mul_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// rl = op1 * op2 where op1 and op2 are single digit
void bn_mul_n11(bn_digit_t *rl, bn_digit_t op1, bn_digit_t op2);

// result += op1 * op2, where op1 is n digits long, op2 is single digit
bn_digit_t bn_muladd_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// result = op1 - op2, where op1 and op2 is "size" digits long
bn_digit_t bn_sub_n(bn_digit_t *r, bn_digit_t *op1, bn_digit_t *op2, bn_size_t size);

#endif