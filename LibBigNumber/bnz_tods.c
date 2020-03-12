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

void * memmove(void *to, const void *from, size_t numBytes);

char *BN_ZERO = "0";

char *bnz_tods(bn_constptr bnz)
{
	char *ds;
	bn_size_t length = BN_ABS(bnz->length);
	bn_size_t nbits = length * BN_DIGIT_BITS - nlz(bnz->digits[length - 1]);

	// may be off by one
	// gercek degerinden 1 fazla olabilir
	bn_size_t ndecimals = ((bn_long_digit_t)nbits * 1292913986 >> 32) + 1;
	if (bnz->length < 0)
		ndecimals++;

	if (!length)
	{
		return BN_ZERO;
	}

	ds = malloc(ndecimals + 1);

	bn_digit_t *tmp = alloca(length * sizeof(bn_digit_t));
	bn_size_t i;

	for (i = 0; i < length; i++)
	{
		tmp[i] = bnz->digits[i];
	}

	char *tds = ds + ndecimals;
	*tds-- = 0;

	while (length)
	{
		*tds-- = '0' + bn_div_n1(tmp, tmp, length, 10);
		length = bn_trim(tmp, length);
	}

	if (bnz->length < 0)
		*tds-- = '-';

	if (tds == ds)
	{
		memmove(ds, ++tds, ndecimals);
	}


	return ds;
}