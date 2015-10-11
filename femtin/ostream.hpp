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
/// \file	ostream.hpp
/// \brief
/// \date	02/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_OSTREAM_HPP_
#define FEMTIN_OSTREAM_HPP_

/// === Includes	================================================================================

#include <cstddef>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "femtin/array.hpp"
#include "femtin/ulimits.h"
#include "femtin/ios.hpp"

/// === Namespaces	================================================================================

namespace femtin
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class ostream : public ios_base
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	ostream(Array_ptr<char> _buffer);

//	void write(float _n);
//	void write(double _n);

	ostream& operator<<(ostream& (*_pf)(ostream&))
	{
		return _pf(*this);
	}

//	ostream& operator<<(ios_base& (*_pf)(ios_base&))
//	{
//		_pf(*this);
//		return *this;
//	}

	ostream& operator<<(char _c)
	{
		return iformat(_c);
	}

	ostream& operator<<(const char* _s)
	{
		return iformat(_s);
	}

	ostream& operator<<(long _n)
	{
		return iformat(_n);
	}

	ostream& operator<<(unsigned long _n)
	{
		return iformat(_n);
	}

//	ostream& operator<<(bool _n)
//	{
//		return iformat(_n);
//	}

	ostream& operator<<(short _n)
	{
		return iformat(_n);
	}

	ostream& operator<<(unsigned short _n)
	{
		return iformat(static_cast<unsigned long>(_n));
	}

	ostream& operator<<(int _n)
	{
		return iformat(_n);
	}

	ostream& operator<<(unsigned int _n)
	{
		return iformat(static_cast<unsigned long>(_n));
	}

	ostream& operator<<(ios_base::fmtflags _f)
	{
		switch (_f)
		{
		case boolalpha:
			femtin::boolalpha(*this);
			break;
		case dec:
			femtin::dec(*this);
			break;
		case fixed:
			femtin::fixed(*this);
			break;
		case hex:
			femtin::hex(*this);
			break;
		case internal:
			femtin::internal(*this);
			break;
		case left:
			femtin::left(*this);
			break;
		case oct:
			femtin::oct(*this);
			break;
		case right:
			femtin::right(*this);
			break;
		case scientific:
			femtin::scientific(*this);
			break;
		case showbase:
			femtin::showbase(*this);
			break;
		case showpoint:
			femtin::showpoint(*this);
			break;
		case showpos:
			femtin::showpos(*this);
			break;
		case skipws:
			femtin::skipws(*this);
			break;
		case unitbuf:
			femtin::unitbuf(*this);
			break;
		case uppercase:
			femtin::uppercase(*this);
			break;
		case adjustfield:
		case basefield:
		case floatfield:
		default:
			assert(false);
			break;
		}

		return *this;
	}

	virtual ostream& endl()
	{
//		write("\n", 1);
		write("\n");
		return *this;
	}

protected:
	///	===	Protected Declarations	================================================================

//	void write(const char* _s, size_t _size);
	virtual void write(const Array_ptr<const char> _s);
//	virtual void write(const uint8_t* _buf, size_t _size) =0;
	virtual void iwrite(const Array_ptr<const uint8_t> _buf) = 0;

	template<typename T> ostream& iformat(T v);

	///	Enables the compiler to check the format string against the parameters provided throughout
	///	the code.
	///	The (m) is the number of the "format string" parameter, and (n) is the number of the first
	///	variadic parameter
	int format(const char* fmt, ...) __attribute__((__format__(__printf__, 2, 3)));
	int format(const char* fmt, va_list args);
	void fmtstring(char* fmt, const char* typestr, bool bInteger) const;
	char* encode_dec(char* fmt, uint32_t n) const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	Array_ptr<char> buffer_;
};

/// === Members Definitions	========================================================================

///	Centralized cast from char* to uint8_t*
//inline void ostream::write(const char* _s, size_t _size)
//{
//	write(reinterpret_cast<const uint8_t*>(_s), _size);
//}

inline void ostream::write(const Array_ptr<const char> _s)
{
//	write(reinterpret_cast<const uint8_t*>(_s), _size);
//	write(static_cast<Array_ptr<const uint8_t> >(_s));
	iwrite(Array_ptr<const uint8_t>(_s));
//	iwrite(_s);
}

template<typename T>
inline const char* printf_typestring(const T)
{
	return "";
}
#define PRINTF_TYPESTRING_SPEC(type, str)	\
template <> inline const char* printf_typestring (const type)	{ return str; }
PRINTF_TYPESTRING_SPEC(char, "c")
PRINTF_TYPESTRING_SPEC(char*, "s")
PRINTF_TYPESTRING_SPEC(int8_t, "d")
PRINTF_TYPESTRING_SPEC(uint8_t, "u")
PRINTF_TYPESTRING_SPEC(int16_t, "d")
PRINTF_TYPESTRING_SPEC(uint16_t, "u")
PRINTF_TYPESTRING_SPEC(int, "d")
PRINTF_TYPESTRING_SPEC(unsigned int, "u")
PRINTF_TYPESTRING_SPEC(long, "ld")
PRINTF_TYPESTRING_SPEC(unsigned long, "lu")
PRINTF_TYPESTRING_SPEC(float, "f")
PRINTF_TYPESTRING_SPEC(double, "lf")
#if HAVE_LONG_LONG
PRINTF_TYPESTRING_SPEC (long long, "lld")
PRINTF_TYPESTRING_SPEC (unsigned long long, "llu")
#endif
#undef PRINTF_TYPESTRING_SPEC

template<typename T>
ostream& ostream::iformat(T v)
{
	char fmt[16] = { 0 };    /// TODO Fix me
	fmtstring(fmt, printf_typestring(v), ustl::numeric_limits<T>::is_integer);

	/// Always set back to zero
	width(0L);

	format(fmt, v);

	return *this;
}

inline char* ostream::encode_dec(char* fmt, uint32_t n) const
{
	do
	{
		*fmt++ = static_cast<char>('0' + n % 10);
	}
	while (n /= 10);
	return fmt;
}

///	=== Non-Members Definitions	====================================================================

inline ostream& endl(ostream& _stream)
{
	return _stream.endl();
}

/// ------------------------------------------------------------------------------------------------
}/// femtin

#endif
/// === END OF FILE	================================================================================
