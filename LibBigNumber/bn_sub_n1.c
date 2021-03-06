/*

	Copyright (C) 2020  Ya�ar Arabac�

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

bn_digit_t bn_sub_n1(bn_digit_t *result, const bn_digit_t *op1, bn_digit_t op2, bn_size_t n)
{
	bn_size_t i;
	bn_digit_t carry = op1[0] < op2;
	result[0] = op1[0] - op2;

	for (i = 1; i < n; i++)
	{
		bn_digit_t a = op1[i];
		bn_digit_t b = carry;
		carry = a < b;
		result[i] = a - b;
	}

	return carry;
}