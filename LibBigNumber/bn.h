/*

	Copyright (C) 2020  Yaþar Arabacý

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef __BN_H_
#define __BN_H_
#include <limits.h> // CHAR_BIT
#include <stdint.h>
#include <stdlib.h> // malloc/realloc

// alloca
#if defined(_MSC_VER)
#include <malloc.h>
#define alloca _alloca
#else
#include <alloc.h>
#endif

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

#define BN_GROW(bn, n) ((n) > (bn)->alloc ? \
    bnz_resize((bn), (n)) \
    : (bn)->digits)

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

typedef struct {
	bn_size_t alloc;
	bn_size_t length;
	bn_digit_t *digits;
} bnz_t;

typedef bnz_t *bnz_ptr;
typedef const bnz_t *bnz_constptr;

// initialize bnz_ptr before first use
void bnz_init(bnz_ptr bnz);

// reallocate p_old to size*sizeof(bn_digit_t). Call exit() if realloc fails.
bn_digit_t *bn_xrealloc(bn_digit_t *p_old, bn_size_t size);

// allocate and return pointer to size*sizeof(bn_digit_t) byte of memory. Call exit() if malloc fails.
bn_digit_t *bn_xmalloc(bn_size_t size);

// allocate space for `size` digits.
bn_digit_t *bnz_resize(bnz_ptr bn, bn_size_t size);

// Calculate length of digits, after leading zeros
bn_size_t bn_trim(bn_digit_t *digits, bn_size_t current_size);

// bn = i
void bnz_set_int(bnz_ptr bn, int i);

// return `(op1 > op2) - (op1 < op2)` where length of both arrays are `opsize`
int bn_cmp_n(const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t opsize);

// return `(op1 > op2) - (op1 < op2)` where length of arrays might differ
int bn_cmp_nn(const bn_digit_t *op1, bn_size_t op1size, const bn_digit_t *op2, bn_size_t op2size);


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

// result = abs(op1) + abs(o2)
bn_size_t bnz_add_abs(bnz_ptr result, bnz_constptr op1, bnz_constptr op2);

// result = op1 + op2
void bnz_add(bnz_ptr result, bnz_constptr op1, bnz_constptr op2);

// result = op1 * op2, where op1 is m digits long, op2 is n digits long
void bn_mul_n(bn_digit_t *result, bn_digit_t *op1, bn_size_t m, bn_digit_t *op2, bn_size_t n);

// result = op1 * op2, where op1 is n digits long, op2 is single digit
bn_digit_t bn_mul_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// rl = op1 * op2 where op1 and op2 are single digit
void bn_mul_n11(bn_digit_t *rl, bn_digit_t op1, bn_digit_t op2);

// result += op1 * op2, where op1 is n digits long, op2 is single digit
bn_digit_t bn_muladd_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// result = op1 - op2, where op1 and op2 is "size" digits long
bn_digit_t bn_sub_n(bn_digit_t *r, const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t size);

// result = op1 - op2, where op1 is n1 digits long, op2 is n2 digits long
bn_digit_t bn_sub_nn(bn_digit_t *result, const bn_digit_t *op1, bn_size_t n1, const bn_digit_t *op2, bn_size_t n2);

// result = op1 - op2 where op1 is n digits long, op2 is single digit
bn_digit_t bn_sub_n1(bn_digit_t *result, const bn_digit_t *op1, bn_digit_t op2, bn_size_t n);

// result = abs(op1) - abs(op2)
bn_size_t bnz_sub_abs(bnz_ptr result, bnz_constptr op1, bnz_constptr op2);

// q = n / d, r = n % d, where n is nlen digits long, d is dlen digits long, d[dlen-1] /= 0
// r can be null
void bn_div_n(bn_digit_t *q, bn_digit_t *r, bn_digit_t *n, bn_size_t nlen, bn_digit_t *d, bn_size_t dlen);

// q = op1 / op2, returns op1 % op2. op1 is n digits long, op2 is single digit
bn_digit_t bn_div_n1(bn_digit_t *q, bn_digit_t *op1, bn_size_t len, bn_digit_t op2);

// Convert a bnz to decimal string
char *bnz_tods(bnz_constptr bnz, char *ds);

// bnz = int(str)
int bnz_set_ds(bnz_ptr bnz, const char *str);

#endif