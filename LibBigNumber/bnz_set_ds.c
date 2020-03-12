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

int bnz_set_ds(bnz_ptr bnz, const char *str)
{
	int sign = 0;
	if (*str == '-')
	{
		str++;
		sign = 1;
	}

	while (*str == '0')
	{
		str++;
	}

	if (!*str)
	{
		bnz->length = 0;
		return 0;
	}

	bn_size_t length = 0;

	const char *tmp = str;

	while (*tmp++)
		length++;

	bn_digit_t *mem = BN_GROW(bnz, (bn_size_t)(length * 4 / BN_DIGIT_BITS + 1));

	bn_size_t rdigits = length % 9;
	bn_digit_t tmp_val;
	bn_size_t k;

	tmp_val = 0;
	for (k = 0; k < rdigits; k++)
	{
		tmp_val = tmp_val * 10 + (*str++ - '0');
	}

	mem[0] = tmp_val;
	length = 1;

	while (*str)
	{
		tmp_val = *str++ - '0';
		for (k = 1; k < 9; k++)
		{
			tmp_val = tmp_val * 10 + (*str++ - '0');
		}

		bn_digit_t carry = bn_mul_n1(mem, mem, 1000000000, length);
		carry += bn_add_n1(mem, mem, tmp_val, length);
		if (carry)
			mem[length++] = carry;
	}

	if (sign)
	{
		bnz->length = -length;
	}
	else
	{
		bnz->length = length;
	}

	return 0;
}