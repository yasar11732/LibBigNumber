/*

	Copyright (C) 2020  Ya�ar Arabac�

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

int bn_cmp_n(const bn_digit_t *op1, const bn_digit_t *op2, bn_size_t opsize)
{
	while (--opsize >= 0)
	{
		if (op1[opsize] != op2[opsize])
		{
			return (op1[opsize] > op2[opsize]) - (op1[opsize] < op2[opsize]);
		}
	}
	return 0;
}