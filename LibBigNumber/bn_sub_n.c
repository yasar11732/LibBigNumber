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

bn_digit_t bn_sub_n(bn_digit_t *r, const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t size)
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