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
/// \file	unit.hpp
/// \brief
/// \date	03/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_UNIT_UNIT_HPP_
#define FEMTIN_UNIT_UNIT_HPP_

/// === Includes	================================================================================

#ifdef _WIN32
//#include <cstdint>
//#include <iostream>
#endif
#include "femtin/mpl/mpl_utility.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace unit
{
/// === Class Declarations	========================================================================

template<typename T, int8_t l, int8_t m, int8_t t, int8_t i, int8_t expo>
class Unit
{
	/// === Basic Types	============================================================================

	typedef Unit<T, l, m, t, i, expo> self_type;

public:
	/// === Public Declarations	====================================================================

	explicit inline Unit(T _val = 0)
			: val_(_val)
	{
	}

	//* (l + m + t + i)
	template<int8_t expo2>
	inline Unit(const Unit<T, l, m, t, i, expo2>& _val)
			: val_(ScaleConverter<T, expo * (l + m + t + i), expo2 * (l + m + t + i)>::convert(
					_val.value()))
	{
	}

	/// --- Compound Assignment Operators	--------------------------------------------------------

	self_type& operator+=(const self_type& rhs)
	{
		val_ += rhs.val_;
		return *this;
	}

	template<int8_t expo2>
	self_type& operator+=(const Unit<T, l, m, t, i, expo2>& rhs)
	{
		val_ += ScaleConverter<T, expo, expo2>::convert(rhs.value());
		return *this;
	}

	self_type& operator*=(T rhs)
	{
		val_ *= rhs;
		return *this;
	}

	self_type& operator/=(T rhs)
	{
		val_ /= rhs;
		return *this;
	}

	/// --- Accessors	----------------------------------------------------------------------------

	T value() const
	{
		return val_;
	}

	T& value()
	{
		return val_;
	}

private:
	/// === Private Attributes	====================================================================
	T val_;
};

/// === Non-Members Definitions	====================================================================

#ifdef _WIN32
template<typename T, int8_t l, int8_t m, int8_t t, int8_t i, int8_t expo>
std::ostream& operator<<(std::ostream& os, const Unit<T, l, m, t, i, expo>& obj)
{
	// write obj to stream
	os << obj.value();
	return os;
}
#endif
/// ------------------------------------------------------------------------------------------------

template<typename T, int8_t l, int8_t m, int8_t t, int8_t i, int8_t expo>
const Unit<T, l, m, t, i, expo> operator+(	const Unit<T, l, m, t, i, expo>& lhs,
											const Unit<T, l, m, t, i, expo>& rhs)
{
	Unit<T, l, m, t, i, expo> result(lhs);
	return result += rhs;
}

/// ------------------------------------------------------------------------------------------------
#if 0
template<typename T, int8_t l, int8_t m, int8_t t, int8_t i, int8_t expo, int8_t expo2>
const Unit<T, l, m, t, i, expo> operator+( const Unit<T, l, m, t, i, expo>& lhs,
		const Unit<T, l, m, t, i, expo2>& rhs)
{
	assert(expo <= expo2);

//#if expo > expo2
//#warning "conversion error, loose precision";
//#endif
	Unit<T, l, m, t, i, expo> result(lhs);
	return result += rhs;

//	static const int8_t RESULT = StaticIf<int8_t, expo <= expo2, expo, expo2>::VALUE;
//
//	return StaticIf<Unit<T, l, m, t, i, RESULT>, expo <= expo2, Unit<T, l,m,t,i, RESULT>,
}
#endif
/// ------------------------------------------------------------------------------------------------

template<typename T, int8_t l1, int8_t m1, int8_t t1, int8_t i1, int8_t l2, int8_t m2, int8_t t2,
		int8_t i2, int8_t expo>
const Unit<T, l1 + l2, m1 + m2, t1 + t2, i1 + i2, expo> operator*(	const Unit<T, l1, m1, t1, i1,
																			expo>& lhs,
																	const Unit<T, l2, m2, t2, i2,
																			expo>& rhs)
{
	typedef Unit<T, l1 + l2, m1 + m2, t1 + t2, i1 + i2, expo> result_t;
	return result_t(lhs.value() * rhs.value());
}

/// ------------------------------------------------------------------------------------------------
#if 0
template<typename T, int8_t l1, int8_t m1, int8_t t1, int8_t i1, int8_t l2, int8_t m2, int8_t t2,
int8_t i2, int8_t expo, int8_t expo2>
const Unit<T, l1 + l2, m1 + m2, t1 + t2, i1 + i2, expo> operator*( const Unit<T, l1, m1, t1, i1,
		expo>& lhs,
		const Unit<T, l2, m2, t2, i2,
		expo2>& rhs)
{
//	typedef Unit<T, l1 + l2, m1 + m2, t1 + t2, i1 + i2, expo> result_t;
//	return result_t(lhs.value() * ScaleConverter<T, expo, expo2>::convert(rhs.value()));

	Unit<T, l2, m2, t2, i2, expo> tmp(rhs);
	return lhs * tmp;
}
#endif
/// ------------------------------------------------------------------------------------------------

template<typename T, int8_t l1, int8_t m1, int8_t t1, int8_t i1, int8_t l2, int8_t m2, int8_t t2,
		int8_t i2, int8_t expo>
const Unit<T, l1 - l2, m1 - m2, t1 - t2, i1 - i2, expo> operator/(	const Unit<T, l1, m1, t1, i1,
																			expo>& lhs,
																	const Unit<T, l2, m2, t2, i2,
																			expo>& rhs)
{
	assert(rhs.value() != 0);

	typedef Unit<T, l1 - l2, m1 - m2, t1 - t2, i1 - i2, expo> result_t;
	return result_t(lhs.value() / rhs.value());
}

/// ------------------------------------------------------------------------------------------------
}/// unit
}    /// femtin
#endif	/// FEMTIN_UNIT_HPP_
/// === END OF FILE	================================================================================
