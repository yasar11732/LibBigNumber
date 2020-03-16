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

#include <stdio.h>

// returns d % n != 0
int bnz_div(bnz_ptr q, bnz_ptr r, bnz_constptr n, bnz_constptr d)
{
	bn_size_t
		nlen, // len of num.
		dlen, // len of denum.
		qlen, // len of quot.
		qsign, // sign of quot
		nsign, // sign of num.
		i;

	bn_digit_t *qp, *rp;

	nlen = n->length;
	dlen = d->length;

	if (dlen == 0)
	{
		fputs("Division By Zero", stderr);
		exit(-1);
	}

	if (nlen == 0)
	{
		if (q) q->length = 0;
		if (r) r->length = 0;
		return 0;
	}

	qsign = nlen ^ dlen;
	nsign = n->length < 0;

	dlen = BN_ABS(dlen);
	nlen = nsign ? -nlen : nlen;

	if (nlen < dlen)
	{
		if (r)
		{
			BN_GROW(r, nlen);
			i = nlen;
			while (--i >= 0)
			{
				r->digits[i] = n->digits[i];
			}
			r->length = n->length < 0 ? -nlen : nlen;
				
		}

		if (q)
			q->length = 0;

		return 1;
	}

	qlen = nlen - dlen + 1;
	if (q)
	{
		qp = BN_GROW(q, qlen);
	}
	else
	{
		qp = bn_xmalloc(qlen);
	}

	if (r)
	{
		rp = BN_GROW(r, dlen);
	}
	else
	{
		rp = bn_xmalloc(dlen);
	}

	if (dlen == 1)
		*rp = bn_div_n1(qp, n->digits, nlen, d->digits[0]);
	else
		bn_div_n(qp, rp, n->digits, nlen, d->digits, dlen);
	
	bn_size_t rlen = bn_trim(rp, dlen);

	if (r)
	{
		r->length = nsign ? -rlen : rlen;
	}
	else
	{
		free(rp);
	}

	qlen = bn_trim(qp, qlen);
	if (q)
	{
		q->length = qsign < 0? -qlen : qlen;
	}
	else
	{
		free(qp);
	}



	return rlen != 0;
}