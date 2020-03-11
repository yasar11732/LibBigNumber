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

struct rngstate
{
	uint8_t i, j, s[256];
};

static struct rngstate RNGSTATE;

void init_rng(char *key)
{
	size_t keysize = strlen(key);
	RNGSTATE.i = 0;
	RNGSTATE.j = 0;

	int i;
	uint8_t j;
	for (i = 0; i < 256; i++)
	{
		RNGSTATE.s[i] = i;
	}

	j = 0;
	for (i = 0; i < 256; i++)
	{
		j += RNGSTATE.s[i] + key[i % keysize];
		int tmp = RNGSTATE.s[i];
		RNGSTATE.s[i] = RNGSTATE.s[j];
		RNGSTATE.s[j] = tmp;
	}
}

uint8_t randomc()
{
	RNGSTATE.i++;
	RNGSTATE.j += RNGSTATE.s[RNGSTATE.i];
	uint8_t temp = RNGSTATE.s[RNGSTATE.i];
	RNGSTATE.s[RNGSTATE.i] = RNGSTATE.s[RNGSTATE.j];
	RNGSTATE.s[RNGSTATE.j] = temp;
	return RNGSTATE.s[(uint8_t)(RNGSTATE.i + RNGSTATE.j)];
}

void fill_random(bn_digit_t *arr, bn_size_t len)
{
	do {
		bn_digit_t num = 0;
		bn_digit_t k = randomc() % 33;
		bn_digit_t _nlz = 32;

		while (_nlz > (32 - k))
		{
			int shift = (_nlz + k) - 32;
			if (shift > 8)
				shift = 8;

			int mask = (1 << shift) - 1;
			num = (num << shift) | (randomc() & mask);
			_nlz = nlz(num);
		}

		arr[--len] = num;

	} while (len);
}