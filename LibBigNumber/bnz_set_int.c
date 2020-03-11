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

void bnz_set_int(bnz_ptr bn, int i)
{
	if (!i)
	{
		bn->length = 0;
		return;
	}

	bn_size_t num_digits = ((sizeof(int) - 1) / sizeof(bn_digit_t)) + 1;
	bn_digit_t *rp = BN_GROW(bn, num_digits);
	*((int *)rp) = BN_ABS(i);
	if (*((int *)rp) == i) // sayi positif
		bn->length = bn_trim(rp, num_digits);
	else // sayi negatif
		bn->length = -bn_trim(rp, num_digits);
}