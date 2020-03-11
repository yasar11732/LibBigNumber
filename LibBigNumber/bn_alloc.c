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
#include <stdlib.h> // malloc/realloc

bn_digit_t *bn_xrealloc(bn_digit_t *p_old, bn_size_t size)
{
	bn_digit_t *p_new = realloc(p_old, size * sizeof(bn_digit_t));
	if (!p_new)
		exit(-1);
	return p_new;
}

bn_digit_t *bn_xmalloc(bn_size_t size)
{
	bn_digit_t *p = malloc(size * sizeof(bn_digit_t));
	if (!p)
		exit(-1);
	return p;
}

bn_digit_t *bnz_resize(bnz_ptr bn, bn_size_t size)
{
	if (bn->alloc)
		bn->digits = bn_xrealloc(bn->digits, size);
	else
		bn->digits = bn_xmalloc(size);

	bn->alloc = size;

	return bn->digits;
}