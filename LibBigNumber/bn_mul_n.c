#include "bn.h"

void bn_mul_n(bn_digit_t *result, bn_digit_t *op1, bn_size_t m, bn_digit_t *op2, bn_size_t n)
{
	bn_size_t i;
	result[m] = bn_mul_n1(result, op1, op2[0], m);

	for (i = 1; i < n; i++)
	{
		result++;
		op2++;

		result[m] = bn_muladd_n1(result, op1, op2[0], m);
	}
}