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


#endif