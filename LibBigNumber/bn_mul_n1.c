#include "bn.h"

bn_digit_t bn_mul_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n)
{
	bn_digit_t temp[2];
	bn_digit_t carry;
	bn_size_t i;

	for (i = 0, carry = 0; i < n; i++)
	{
		bn_mul_n11(temp, op1[i], op2);
		bn_add_n1(temp, temp, carry, 2); // bu carry döndüremez, döndürmemeli
		carry = temp[1];
		result[i] = temp[0];
	}

	return carry;
}