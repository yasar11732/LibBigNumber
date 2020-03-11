#include "bn.h"

bn_digit_t bn_add_nn(bn_digit_t *result, const bn_digit_t *op1, bn_size_t n1, const bn_digit_t *op2, bn_size_t n2)
{
	bn_digit_t carry = bn_add_n(result, op1, op2, n2);
	if (n1 > n2)
		carry = bn_add_n1(result + n2, op1 + n2, n1 - n2, carry);

	return carry;
}