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