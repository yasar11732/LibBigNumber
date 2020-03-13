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

bn_size_t bnz_sub_abs(bnz_ptr result, bnz_constptr op1, bnz_constptr op2)
{
	int s1 = BN_ABS(op1->length);
	int s2 = BN_ABS(op2->length);
	bn_digit_t *rp;

	int cmp = bn_cmp_nn(op1->digits, s1, op2->digits, s2);

	if (cmp > 0)
	{
		rp = BN_GROW(result, s1);
		bn_sub_nn(rp, op1->digits, s1, op2->digits, s2);
		return bn_trim(rp, s1);
	}
	else if (cmp < 0)
	{
		rp = BN_GROW(result, s2);
		bn_sub_nn(rp, op2->digits, s2, op1->digits, s1);
		return -bn_trim(rp, s2);
	}
	else
	{
		return 0;
	}
}