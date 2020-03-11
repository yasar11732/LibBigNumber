#include "bn.h"

void _bn_mul_n11(bn_digit_t *rl, bn_digit_t op1, bn_digit_t op2)
{
	bn_digit_t op1_h = (op1 >> (BN_DIGIT_BITS / 2));
	bn_digit_t op1_l = (op1 & BN_DIGIT_LOWMASK);
	bn_digit_t op2_h = (op2 >> (BN_DIGIT_BITS / 2));
	bn_digit_t op2_l = (op2 & BN_DIGIT_LOWMASK);

	bn_digit_t p1 = op1_l * op2_l;
	bn_digit_t p2 = op1_l * op2_h;
	bn_digit_t p3 = op1_h * op2_l;
	bn_digit_t p4 = op1_h * op2_h;

	p2 += (p1 >> (BN_DIGIT_BITS / 2));
	p2 += p3;
	if (p2 < p3) // carry
	{
		p4 += BN_DIGIT_HI;
	}

	rl[0] = (p2 << (BN_DIGIT_BITS / 2)) + (p1 & BN_DIGIT_LOWMASK);
	rl[1] = p4 + (p2 >> (BN_DIGIT_BITS / 2));
}