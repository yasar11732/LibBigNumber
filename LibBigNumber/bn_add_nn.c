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

bn_digit_t bn_add_nn(bn_digit_t *result, const bn_digit_t *op1, bn_size_t n1, const bn_digit_t *op2, bn_size_t n2)
{
	bn_digit_t carry = bn_add_n(result, op1, op2, n2);
	if (n1 > n2)
		carry = bn_add_n1(result + n2, op1 + n2, n1 - n2, carry);

	return carry;
}