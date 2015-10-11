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
/// \file	ostream.cpp
///	\brief	
///	\date	03/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "ostream.hpp"
using namespace femtin;

/// === Includes	================================================================================

#include <cstdio>

/// === Namespaces	================================================================================
/// === Constants	================================================================================
/// === Public Definitions	========================================================================

ostream::ostream(femtin::Array_ptr<char> _buffer)
		: buffer_(_buffer)
{
}

/// ------------------------------------------------------------------------------------------------

///	=== Protected Definitions	====================================================================

/// === Private Definitions	========================================================================

int ostream::format(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	const int rv = format(fmt, args);
	va_end(args);
	return rv;
}

/// ------------------------------------------------------------------------------------------------

int ostream::format(const char* fmt, va_list args)
{
	uint32_t ret = vsnprintf(buffer_.begin(), buffer_.max_size(), fmt, args);
	if (ret > 0)
	{
//		write(buffer_.begin(), ret);
		write(buffer_.subarray(0, ret));
	}
	return ret;
}

/// ------------------------------------------------------------------------------------------------

void ostream::fmtstring(char* fmt, const char* _specifier, bool _is_integer) const
{
	/// introductory % character
	*fmt++ = '%';

	if (flags_ & left) *fmt++ = '-';

	if (*_specifier == 'c' || *_specifier == 's')
	{
		/// Copy conversion specifier
		while (*_specifier)
			*fmt++ = *_specifier++;
	}
	else if (_is_integer)
	{
		if (flags_ & dec)
		{
			if (width_) fmt = encode_dec(fmt, width_);
			while (*_specifier)
				*fmt++ = *_specifier++;
		}
		else if (flags_ & oct)
		{
			if (flags_ & showbase) *fmt++ = '#';
			if (width_) fmt = encode_dec(fmt, width_);
			*fmt++ = 'o';
		}
		else if (flags_ & hex)
		{
			if (flags_ & showbase) *fmt++ = '#';
			if (width_) fmt = encode_dec(fmt, width_);
			*fmt++ = 'X';
		}
	}

	/// Null-terminated string
	*fmt = '\0';
}

/// === END OF FILE	================================================================================
