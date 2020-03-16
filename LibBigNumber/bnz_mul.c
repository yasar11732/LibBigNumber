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

void
bnz_mul(bnz_t *result, bnz_constptr op1, bnz_constptr op2)
{
	if (op1->length == 0 || op2->length == 0)
	{
		result->length = 0;
		return;
	}

	bn_size_t op1_len = BN_ABS(op1->length);
	bn_size_t op2_len = BN_ABS(op2->length);
	
	bn_size_t len = op1_len + op2_len;
	bn_digit_t *rp;
	if (result->digits == op1->digits || result->digits == op2->digits)
	{
		rp = bn_xmalloc(len);
	}
	else
	{
		rp = BN_GROW(result, len);
	}


	if (op1_len >= op2_len)
		bn_mul_n(rp, op1->digits, op1_len, op2->digits, op2_len);
	else
		bn_mul_n(rp, op2->digits, op2_len, op1->digits, op1_len);

	if (rp != result->digits)
	{
		free(result->digits);
		result->digits = rp;
		result->alloc = len;
	}

	len = bn_trim(rp, len);

	result->length = (op1->length ^ op2->length) < 0 ? -len : len;
}