#include "bn.h"

bn_digit_t bn_sub_n(bn_digit_t *r, bn_digit_t *op1, bn_digit_t *op2, bn_size_t size)
{
	bn_digit_t carry;
	bn_size_t i;
	for (i = 0, carry = 0; i < size; i++)
	{
		bn_digit_t a = op1[i];
		bn_digit_t b = op2[i];
		b += carry;
		carry = (b < carry);
		carry += (a < b);
		r[i] = a - b;
	}

	return carry;
}