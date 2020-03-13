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

void bnz_add(bnz_ptr result, bnz_constptr op1, bnz_constptr op2)
{
	bn_size_t result_size;

	if ((op1->length ^ op2->length) >= 0)
	{
		result_size = bnz_add_abs(result, op1, op2);
	}
	else
	{
		result_size = bnz_sub_abs(result, op1, op2);
	}

	result->length = op1->length >= 0 ? result_size : -result_size;
}