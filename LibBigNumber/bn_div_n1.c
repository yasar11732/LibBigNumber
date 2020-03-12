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

#include "bn.h"

bn_digit_t bn_div_n1(bn_digit_t *q, bn_digit_t *op1, bn_size_t len, bn_digit_t op2)
{
	bn_digit_t carry = 0;
	bn_size_t i;

	for (i = len - 1; i >= 0; i--)
	{
		bn_long_digit_t u = ((bn_long_digit_t)carry << BN_DIGIT_BITS) + (op1[i]);
		q[i] = (bn_digit_t)(u / op2);
		carry = u % op2;
	}

	return carry;
}