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

bn_digit_t bn_muladd_n1(bn_digit_t *result, bn_digit_t *op1, bn_digit_t op2, bn_size_t n)
{
	bn_digit_t temp[2];
	bn_digit_t carry;
	bn_size_t i;
	for (i = 0, carry = 0; i < n; i++)
	{
		bn_mul_n11(temp, op1[i], op2);
		bn_add_n1(temp, temp, carry, 2);
		carry = temp[1];
		result[i] += temp[0];
		carry += (result[i] < temp[0]);
	}
	return carry;
}