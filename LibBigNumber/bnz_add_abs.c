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

// result = abs(op1) + abs(op2)
bn_size_t bnz_add_abs(bnz_ptr result, bnz_constptr op1, bnz_constptr op2)
{
	bn_size_t s1 = BN_ABS(op1->length);
	bn_size_t s2 = BN_ABS(op2->length);
	bn_digit_t carry;
	bn_digit_t *rp;

	// switch operands so s1 is bigger or equal in size
	if (s1 < s2)
	{
		bnz_constptr tmp = op1;
		op1 = op2;
		op2 = tmp;

		bn_size_t tmps = s1;
		s1 = s2;
		s2 = tmps;
	}

	rp = BN_GROW(result, s1 + 1);
	carry = bn_add_nn(rp, op1->digits, s1, op2->digits, s2);

	rp[s1] = carry;
	return s1 + carry;
}