#include "bn.h"

bn_digit_t bn_add_n1(bn_digit_t *result, const bn_digit_t *op1, bn_digit_t op2, bn_size_t n)
{
	bn_size_t i;
	result[0] = op1[0] + op2;
	bn_digit_t carry = result[0] < op2;

	for (i = 1; i < n; i++)
	{
		result[i] = op1[i] + carry;
		carry = (result[i] < carry);
	}

	return carry;
}