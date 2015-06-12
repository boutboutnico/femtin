/*
 Femtin V0.0.1 - Copyright (C) 2015 Nicolas Boutin.
 All rights reserved

 This file is part of the Femtin distribution.

 Femtin is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation.

 Femtin is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.
 */

/// ================================================================================================
///
/// \file	xprintf.cpp
///	\brief	
///	\date	30/05/2015
/// \author	author
///
/// ================================================================================================
#include "xprintf.hpp"

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace femtin
{

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

void xvsnprintf(char* _buffer, size_t _buf_size, const char* _format, va_list _vlist)
{
	unsigned int r, i, j, w, f;
	unsigned long v;
	char s[16], c, d, *p;

	for (;;)
	{
		c = *_format++; /* Get a char */
		if (!c) break; /* End of format? */
		if (c != '%')
		{ /* Pass through it if not a % sequence */
//			xputc(c);
			*_buffer++ = c;
			continue;
		}
		f = 0;
		c = *_format++; /* Get first char of the sequence */
		if (c == '0')
		{ /* Flag: '0' padded */
			f = 1;
			c = *_format++;
		}
		else
		{
			if (c == '-')
			{ /* Flag: left justified */
				f = 2;
				c = *_format++;
			}
		}
		for (w = 0; c >= '0' && c <= '9'; c = *_format++) /* Minimum width */
			w = w * 10 + c - '0';
		if (c == 'l' || c == 'L')
		{ /* Prefix: Size is long int */
			f |= 4;
			c = *_format++;
		}
		if (!c) break; /* End of format? */
		d = c;
		if (d >= 'a') d -= 0x20;
		switch (d)
		{ /* Type is... */
		case 'S': /* String */
			p = va_arg(_vlist, char*);
			for (j = 0; p[j]; j++)
				;
			while (!(f & 2) && j++ < w)
//				xputc(' ');
				*_buffer++ = ' ';
//			xputs(p);
			while (*p)
//				xputc(*str++);
				*_buffer++ = *p++;
			while (j++ < w)
//				xputc(' ');
				*_buffer++ = ' ';
			continue;
		case 'C': /* Character */
//			xputc((char) va_arg(arp, int));
			*_buffer++ = (char) va_arg(_vlist, int);
			continue;
		case 'B': /* Binary */
			r = 2;
			break;
		case 'O': /* Octal */
			r = 8;
			break;
		case 'D': /* Signed decimal */
		case 'U': /* Unsigned decimal */
			r = 10;
			break;
		case 'X': /* Hexdecimal */
			r = 16;
			break;
		default: /* Unknown type (passthrough) */
//			xputc(c);
			*_buffer++ = c;
			continue;
		}

		/* Get an argument and put it in numeral */
		v = (f & 4) ?
				va_arg(_vlist, long) :
				((d == 'D') ? (long) va_arg(_vlist, int) : (long) va_arg(_vlist, unsigned int));
		if (d == 'D' && (v & 0x80000000))
		{
			v = 0 - v;
			f |= 8;
		}
		i = 0;
		do
		{
			d = (char) (v % r);
			v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			s[i++] = d + '0';
		}
		while (v && i < sizeof(s));
		if (f & 8) s[i++] = '-';
		j = i;
		d = (f & 1) ? '0' : ' ';
		while (!(f & 2) && j++ < w)
//			xputc(d);
			*_buffer++ = d;
		do
//			xputc(s[--i]);
			*_buffer++ = s[--i];
		while (i);
		while (j++ < w)
//			xputc(' ');
			*_buffer++ = ' ';
	}
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}///femtin
/// === END OF FILE	================================================================================
