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
/// \file	ios.hpp
/// \brief
/// \date	02/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_IOS_HPP_
#define FEMTIN_IOS_HPP_

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace femtin
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================

enum ios_fmtflags
{
	ios_boolalpha = (1 << 0),    ///< Boolean values printed as text.
	ios_dec = (1 << 1),    ///< Decimal number output.
	ios_fixed = (1 << 2),    ///< Fixed-point float output.
	ios_hex = (1 << 3),    ///< Hexadecimal number output.
	ios_internal = (1 << 4),
	ios_left = (1 << 5),    ///< Left alignment.
	ios_oct = (1 << 6),    ///< Octal number output.
	ios_right = (1 << 7),    ///< Right alignment.
	ios_scientific = (1 << 8),    ///< Scientific float format.
	ios_showbase = (1 << 9),    ///< Add 0x or 0 prefixes on hex and octal numbers.
	ios_showpoint = (1 << 10),    ///< Print decimal point.
	ios_showpos = (1 << 11),
	ios_skipws = (1 << 12),    ///< Skip whitespace when reading.
	ios_unitbuf = (1 << 13),
	ios_uppercase = (1 << 14),
	ios_adjustfield = ios_left | ios_right | ios_internal,
	ios_basefield = ios_dec | ios_oct | ios_hex,
	ios_floatfield = ios_scientific | ios_fixed,
};

inline constexpr ios_fmtflags operator&(ios_fmtflags _a, ios_fmtflags _b)
{
	return ios_fmtflags(static_cast<int>(_a) & static_cast<int>(_b));
}

inline constexpr ios_fmtflags operator|(ios_fmtflags _a, ios_fmtflags _b)
{
	return ios_fmtflags(static_cast<int>(_a) | static_cast<int>(_b));
}

inline constexpr ios_fmtflags operator^(ios_fmtflags _a, ios_fmtflags _b)
{
	return ios_fmtflags(static_cast<int>(_a) ^ static_cast<int>(_b));
}

inline constexpr ios_fmtflags operator~(ios_fmtflags _a)
{
	return ios_fmtflags(~static_cast<int>(_a));
}

inline const ios_fmtflags& operator|=(ios_fmtflags& _a, ios_fmtflags _b)
{
	return _a = _a | _b;
}

inline const ios_fmtflags& operator&=(ios_fmtflags& _a, ios_fmtflags _b)
{
	return _a = _a & _b;
}

inline const ios_fmtflags& operator^=(ios_fmtflags& _a, ios_fmtflags _b)
{
	return _a = _a ^ _b;
}

/// === Class Declarations	========================================================================

class ios_base
{
public:
	///	=== Basic Types	============================================================================

	typedef ios_fmtflags fmtflags;

	/// === Public Constants	====================================================================

	static const fmtflags boolalpha = ios_boolalpha;

	/// Converts integer input or generates integer output in decimal base.
	static const fmtflags dec = ios_dec;

	/// Generate floating-point output in fixed-point notation.
	static const fmtflags fixed = ios_fixed;

	/// Converts integer input or generates integer output in hexadecimal base.
	static const fmtflags hex = ios_hex;

	/// Adds fill characters at a designated internal point in certain
	/// generated output, or identical to @c right if no such point is
	/// designated.
	static const fmtflags internal = ios_internal;

	/// Adds fill characters on the right (final positions) of certain
	/// generated output.  (I.e., the thing you print is flush left.)
	static const fmtflags left = ios_left;

	/// Converts integer input or generates integer output in octal base.
	static const fmtflags oct = ios_oct;

	/// Adds fill characters on the left (initial positions) of certain
	/// generated output.  (I.e., the thing you print is flush right.)
	static const fmtflags right = ios_right;

	/// Generates floating-point output in scientific notation.
	static const fmtflags scientific = ios_scientific;

	/// Generates a prefix indicating the numeric base of generated integer
	/// output.
	static const fmtflags showbase = ios_showbase;

	/// Generates a decimal-point character unconditionally in generated
	/// floating-point output.
	static const fmtflags showpoint = ios_showpoint;

	/// Generates a + sign in non-negative generated numeric output.
	static const fmtflags showpos = ios_showpos;

	/// Skips leading white space before certain input operations.
	static const fmtflags skipws = ios_skipws;

	/// Flushes output after each output operation.
	static const fmtflags unitbuf = ios_unitbuf;

	/// Replaces certain lowercase letters with their uppercase equivalents
	/// in generated output.
	static const fmtflags uppercase = ios_uppercase;

	/// A mask of left|right|internal.  Useful for the 2-arg form of @c setf.
	static const fmtflags adjustfield = ios_adjustfield;

	/// A mask of dec|oct|hex.  Useful for the 2-arg form of @c setf.
	static const fmtflags basefield = ios_basefield;

	/// A mask of scientific|fixed.  Useful for the 2-arg form of @c setf.
	static const fmtflags floatfield = ios_floatfield;

	///	=== Public Enumerations	====================================================================

	/// === Public Declarations	====================================================================

//	ios_base(const ios_base&) = delete;

	///	---	Formatting	----------------------------------------------------------------------------

	fmtflags flags() const;
	fmtflags flags(fmtflags _flags);
	fmtflags setf(fmtflags _flags);
	fmtflags setf(fmtflags _flags, fmtflags _mask);
	void unsetf(fmtflags _mask);

	size_t width() const;
	size_t width(size_t _size);

	size_t precision() const;
	size_t precision(size_t _precision);

protected:
	///	===	Protected Declarations	================================================================

//	ios_base();

	/// === Protected Attributes	================================================================

	fmtflags flags_;
	size_t width_;
	size_t precision_;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================
};

/// === Inlines Definitions	========================================================================

inline ios_base::fmtflags ios_base::flags() const
{
	return flags_;
}

inline ios_base::fmtflags ios_base::flags(fmtflags _flags)
{
	fmtflags old = flags_;
	flags_ |= _flags;
	return old;
}

inline ios_base::fmtflags ios_base::setf(fmtflags _flags)
{
	fmtflags old = flags_;
	flags_ = _flags;
	return old;
}

inline ios_base::fmtflags ios_base::setf(fmtflags _flags, fmtflags _mask)
{
	fmtflags old = flags_;
	flags_ &= ~_mask;
	flags_ |= (_flags & _mask);
	return old;
}

inline void ios_base::unsetf(fmtflags _mask)
{
	flags_ &= ~_mask;
}

inline size_t ios_base::width() const
{
	return width_;
}

inline size_t ios_base::width(size_t _width)
{
	size_t old = width_;
	width_ = _width;
	return old;
}

inline size_t ios_base::precision() const
{
	return precision_;
}

inline size_t ios_base::precision(size_t _precision)
{
	size_t old = precision_;
	precision_ = _precision;
	return old;
}

///	=== Non-Members Definitions	====================================================================

inline ios_base& boolalpha(ios_base& _base)
{
	_base.setf(ios_base::boolalpha);
	return _base;
}

inline ios_base& noboolalpha(ios_base& _base)
{
	_base.unsetf(ios_base::boolalpha);
	return _base;
}

inline ios_base& showbase(ios_base& _base)
{
	_base.setf(ios_base::showbase);
	return _base;
}

inline ios_base& noshowbase(ios_base& _base)
{
	_base.unsetf(ios_base::showbase);
	return _base;
}

inline ios_base& showpoint(ios_base& _base)
{
	_base.setf(ios_base::showpoint);
	return _base;
}

inline ios_base& noshowpoint(ios_base& _base)
{
	_base.unsetf(ios_base::showpoint);
	return _base;
}

inline ios_base& showpos(ios_base& _base)
{
	_base.setf(ios_base::showpos);
	return _base;
}

inline ios_base& noshowpos(ios_base& _base)
{
	_base.unsetf(ios_base::showpos);
	return _base;
}

inline ios_base& skipws(ios_base& _base)
{
	_base.setf(ios_base::skipws);
	return _base;
}

inline ios_base& noskipws(ios_base& _base)
{
	_base.unsetf(ios_base::skipws);
	return _base;
}

inline ios_base& uppercase(ios_base& _base)
{
	_base.setf(ios_base::uppercase);
	return _base;
}

inline ios_base& nouppercase(ios_base& _base)
{
	_base.unsetf(ios_base::uppercase);
	return _base;
}

inline ios_base& unitbuf(ios_base& _base)
{
	_base.setf(ios_base::unitbuf);
	return _base;
}

inline ios_base& nounitbuf(ios_base& _base)
{
	_base.unsetf(ios_base::unitbuf);
	return _base;
}

inline ios_base& internal(ios_base& _base)
{
	_base.setf(ios_base::internal, ios_base::adjustfield);
	return _base;
}

inline ios_base& left(ios_base& _base)
{
	_base.setf(ios_base::left, ios_base::adjustfield);
	return _base;
}

inline ios_base& right(ios_base& _base)
{
	_base.setf(ios_base::right, ios_base::adjustfield);
	return _base;
}

inline ios_base& dec(ios_base& _base)
{
	_base.setf(ios_base::dec, ios_base::basefield);
	return _base;
}

inline ios_base& hex(ios_base& _base)
{
	_base.setf(ios_base::hex, ios_base::basefield);
	return _base;
}

inline ios_base& oct(ios_base& _base)
{
	_base.setf(ios_base::oct, ios_base::basefield);
	return _base;
}

inline ios_base& fixed(ios_base& _base)
{
	_base.setf(ios_base::fixed, ios_base::floatfield);
	return _base;
}

inline ios_base& scientific(ios_base& _base)
{
	_base.setf(ios_base::scientific, ios_base::floatfield);
	return _base;
}

/// ------------------------------------------------------------------------------------------------
}/// femtin

#endif	/// FOLDER_TEMPLATE_HPP_
/// === END OF FILE	================================================================================
