#include "bn.h"

#if defined(_MSC_VER)
#include <malloc.h>
#define alloca _alloca
#else
#include <alloc.h>
#endif

void bn_div_n(bn_digit_t *q, bn_digit_t *r, bn_digit_t *n, bn_size_t nlen, bn_digit_t *d, bn_size_t dlen)
{
	// Geçiçi kullanýlacak hafýza alanlarý.

	// nn => Bölünenin normalizasyon geçirmiþ hali
	bn_digit_t *nn = alloca((nlen + 1) * sizeof(bn_digit_t));

	// dn => Bölenin normalizasyon geçirmiþ hali.
	bn_digit_t *dn = alloca((dlen) * sizeof(bn_digit_t));


	// D.1
	// ================

	// normalizasyon için kaydýrma miktarý
	int s = nlz(d[dlen - 1]);

	// Kaydýrma iþlemleri
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

	// D.2 DÖNGÜ
	for (i = nlen - dlen; i >= 0; i--)
	{
		// D.3 - þapkalý q hesabý için, 64 bit aritmetik kullanacaðýz.
		bn_long_digit_t qhat;
		bn_long_digit_t rhat;
		bn_long_digit_t ulong = ((bn_long_digit_t)(nn[dlen + i]) << BN_DIGIT_BITS) + (bn_long_digit_t)(nn[dlen + i - 1]);

		qhat = ulong / dn[dlen - 1];

		// Düzgün bir derleyici (i.e GCC/Clang) bunu optimize edecektir.
		// eðer etmiyorsa, rhat = ulong - (qhat * dn[dlen - 1])
		rhat = ulong % dn[dlen - 1];

		// qhat 2 haneli mi kontrolü
		if (qhat > BN_DIGIT_MAX)
		{
			--qhat;
			rhat += dn[dlen - 1];
		}

		// Düzeltme döngüsü
		while ((rhat >> BN_DIGIT_BITS) == 0 && (qhat * dn[dlen - 2]) > ((rhat << BN_DIGIT_BITS) + nn[dlen + i - 2]))
		{
			--qhat;
			rhat += dn[dlen - 1];
		}

		// D.4 - Çarp-Çýkar
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

		// Elimizde kalaný bir üst haneye taþýmak için
		ulong = borrow;
		borrow = (nn[i + k] < borrow);
		nn[i + k] -= (bn_digit_t)ulong;

		// D.6 - Çýkarma sonucu negatif ise, düzelt. Burasý nadiren çalýþacak.
		if (borrow)
		{
			--qhat;
			bn_add_n(nn + i, nn + i, dn, dlen);
		}

		// D.5 - Sonucun ilgili hanesini yazýyoruz.
		q[i] = (bn_digit_t)qhat;

		// D.7 - i'yi eksiltip, i >= 0 ise D.3'e geç.
	}

	// D.8 Eðer kalan istenmiþse, düzelt
	if (r)
	{
		for (i = 0; i < dlen - 1; i++)
		{
			r[i] = (nn[i] >> s) | ((bn_long_digit_t)nn[i + 1]) << (BN_DIGIT_BITS - s);
		}
		r[i] = nn[i] >> s;
	}
}