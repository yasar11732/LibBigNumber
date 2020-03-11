#include "bn.h"

bn_digit_t bn_add_n(bn_digit_t *result, const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t n)
{
	bn_size_t i;
	bn_digit_t carry;
	for (i = 0, carry = 0; i < n; i++)
	{
		bn_digit_t a, b, r;

		a = op1[i];
		b = op2[i];
		r = a + carry;
		carry = (r < a);
		r += b;
		carry += (r < b);
		result[i] = r;
	}
	return carry;
}