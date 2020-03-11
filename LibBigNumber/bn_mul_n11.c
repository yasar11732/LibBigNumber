#include "bn.h"

void bn_mul_n11(bn_digit_t *rl, bn_digit_t op1, bn_digit_t op2)
{
	*((bn_long_digit_t *)rl) = ((bn_long_digit_t)op1) * ((bn_long_digit_t)op2);
}