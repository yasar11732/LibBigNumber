#include "bn.h"

#if defined(_MSC_VER)
#include <malloc.h>
#define alloca _alloca
#else
#include <alloc.h>
#endif

void bn_div_n(bn_digit_t *q, bn_digit_t *r, bn_digit_t *n, bn_size_t nlen, bn_digit_t *d, bn_size_t dlen)
{
	// Ge�i�i kullan�lacak haf�za alanlar�.

	// nn => B�l�nenin normalizasyon ge�irmi� hali
	bn_digit_t *nn = alloca((nlen + 1) * sizeof(bn_digit_t));

	// dn => B�lenin normalizasyon ge�irmi� hali.
	bn_digit_t *dn = alloca((dlen) * sizeof(bn_digit_t));


	// D.1
	// ================

	// normalizasyon i�in kayd�rma miktar�
	int s = nlz(d[dlen - 1]);

	// Kayd�rma i�lemleri
	bn_size_t i;

	for (i = dlen - 1; i > 0; i--)
	{
		dn[i] = (d[i] << s) | ((bn_long_digit_t)(d[i - 1]) >> (BN_DIGIT_BITS - s));
	}
	dn[0] = d[0] << s;

	nn[nlen] = ((bn_long_digit_t)(n[nlen - 1]) >> (BN_DIGIT_BITS - s));
	for (i = nlen - 1; i > 0; i--)
	{
		nn[i] = (n[i] << s) | ((bn_long_digit_t)(n[i - 1]) >> (BN_DIGIT_BITS - s));
	}
	nn[0] = n[0] << s;

	// D.2 D�NG�
	for (i = nlen - dlen; i >= 0; i--)
	{
		// D.3 - �apkal� q hesab� i�in, 64 bit aritmetik kullanaca��z.
		bn_long_digit_t qhat;
		bn_long_digit_t rhat;
		bn_long_digit_t ulong = ((bn_long_digit_t)(nn[dlen + i]) << BN_DIGIT_BITS) + (bn_long_digit_t)(nn[dlen + i - 1]);

		qhat = ulong / dn[dlen - 1];

		// D�zg�n bir derleyici (i.e GCC/Clang) bunu optimize edecektir.
		// e�er etmiyorsa, rhat = ulong - (qhat * dn[dlen - 1])
		rhat = ulong % dn[dlen - 1];

		// qhat 2 haneli mi kontrol�
		if (qhat > BN_DIGIT_MAX)
		{
			--qhat;
			rhat += dn[dlen - 1];
		}

		// D�zeltme d�ng�s�
		while ((rhat >> BN_DIGIT_BITS) == 0 && (qhat * dn[dlen - 2]) > ((rhat << BN_DIGIT_BITS) + nn[dlen + i - 2]))
		{
			--qhat;
			rhat += dn[dlen - 1];
		}

		// D.4 - �arp-��kar
		bn_digit_t borrow = 0;
		bn_size_t k;
		for (k = 0; k < dlen; k++)
		{
			ulong = dn[k] * qhat;
			ulong += borrow;
			borrow = nn[i + k] < ((bn_digit_t)ulong);
			nn[i + k] -= (bn_digit_t)ulong;
			borrow += ulong >> BN_DIGIT_BITS;
		}

		// Elimizde kalan� bir �st haneye ta��mak i�in
		ulong = borrow;
		borrow = (nn[i + k] < borrow);
		nn[i + k] -= (bn_digit_t)ulong;

		// D.6 - ��karma sonucu negatif ise, d�zelt. Buras� nadiren �al��acak.
		if (borrow)
		{
			--qhat;
			bn_add_n(nn + i, nn + i, dn, dlen);
		}

		// D.5 - Sonucun ilgili hanesini yaz�yoruz.
		q[i] = (bn_digit_t)qhat;

		// D.7 - i'yi eksiltip, i >= 0 ise D.3'e ge�.
	}

	// D.8 E�er kalan istenmi�se, d�zelt
	if (r)
	{
		for (i = 0; i < dlen - 1; i++)
		{
			r[i] = (nn[i] >> s) | ((bn_long_digit_t)nn[i + 1]) << (BN_DIGIT_BITS - s);
		}
		r[i] = nn[i] >> s;
	}
}