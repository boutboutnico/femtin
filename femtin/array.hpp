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
/// \file	array.hpp
/// \brief	Smart array
/// \date	05/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_ARRAY_HPP_
#define FEMTIN_ARRAY_HPP_

/// === Includes	================================================================================

#include <cstddef>
#include <assert.h>
#include <cstring>
#include "algorithm.hpp"

/// === Namespaces	================================================================================

namespace femtin
{

/// === Forward Declarations	====================================================================

template<typename T>
class Array_ptr;

/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

template<typename T, size_t L>
class Array
{
public:
	/// === Basic Types	============================================================================

	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;

	/// === Public Declarations	====================================================================

	Array() = default;

	/// --- Capacity	----------------------------------------------------------------------------

	/// \brief	Returns the maximum number of elements the array is able to hold due to system
	///			or library implementation limitations.
	inline size_t max_size() const
	{
		return L;
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline reference operator[](size_t _pos)
	{
		assert(_pos < max_size());
		return array_[_pos];
	}

	inline const_reference operator[](size_t _pos) const
	{
		assert(_pos < max_size());
		return array_[_pos];
	}

	inline iterator data()
	{
		return array_;
	}

	inline const_iterator data() const
	{
		return array_;
	}

	/// \brief
	/// \param[in]	_pos	Position of the first character to include
	/// \param[in] _count	Length of the subarray
	Array_ptr<T> subarray(size_t _pos = 0, size_t _count = L)
	{
		return Array_ptr<T>(&array_[min(_pos, L - 1)], min(L - _pos, _count));
	}

	/// \brief
	/// \param[in]	_pos	Position of the first character to include
	/// \param[in] _count	Length of the subarray
	Array_ptr<const T> subarray(size_t _pos = 0, size_t _count = L) const
	{
		return Array_ptr<const T>(&array_[min(_pos, L - 1)], min(L - _pos, _count));
	}

	/// --- Operations	----------------------------------------------------------------------------

	inline void clear()
	{
		memset(array_, 0x00, sizeof(value_type) * L);
	}

	/// --- Iterators	----------------------------------------------------------------------------

	inline iterator begin()
	{
		return array_;
	}

	inline const_iterator begin() const
	{
		return array_;
	}

	inline iterator end()
	{
		return &array_[L];
	}

	inline const_iterator end() const
	{
		return &array_[L];
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	T array_[L];
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------

/// ================================================================================================
/// === Class Declarations	========================================================================

template<typename T>
class Array_ptr
{
public:
	/// === Basic Types	============================================================================

	typedef T* iterator;
	typedef T& reference;

	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// \brief	Default constructor
	Array_ptr()
			: array_(NULL), size_(0)
	{
	}

	/// \brief	Construct provided for compatibility with code that does not use Array_ptr
	///			It can deduce array size at compile-time.
	/// \warning	New code should not use this constructor
	template<size_t L>
	Array_ptr(T (&_array)[L])
			: array_(&_array[0]), size_(L)
	{
	}

	/// \brief	Construct provided for compatibility with code that does not use Array_ptr
	/// \warning	New code should not use this constructor
	Array_ptr(T* const _data, const size_t _len)
			: array_(_data), size_(_len)
	{
	}

	template<size_t L>
	Array_ptr(Array<T, L>& _array)
			: array_(_array.begin()), size_(L)
	{
	}

	template<typename T2>
	Array_ptr(Array_ptr<T2> _array)
			: array_(reinterpret_cast<iterator>(_array.begin())), size_(_array.max_size())
	{

	}

	/// --- Capacity	----------------------------------------------------------------------------

	/// \brief	Returns the maximum number of elements the array is able to hold due to system
	///			or library implementation limitations.
	inline size_t max_size() const
	{
		return size_;
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline reference operator[](size_t _pos)
	{
		assert(_pos < max_size());
		return array_[_pos];
	}

	inline iterator data()
	{
		return array_;
	}

	/// \brief
	/// \param[in]	_pos	Position of the first character to include
	/// \param[in] _count	Length of the subarray
	Array_ptr<T> subarray(size_t _pos, size_t _count)
	{
		return Array_ptr<T>(&array_[min(_pos, size_ - 1)], min(size_ - _pos, _count));
	}

	/// \brief
	/// \param[in]	_pos	Position of the first character to include
	/// \param[in] _count	Length of the subarray
	const Array_ptr<const T> subarray(size_t _pos, size_t _count) const
	{
		return Array_ptr<const T>(&array_[min(_pos, size_ - 1)], min(size_ - _pos, _count));
	}

	/// --- Iterators	----------------------------------------------------------------------------

	inline iterator begin()
	{
		return array_;
	}

	inline iterator end()
	{
		return &array_[size_];
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	T* array_;
	const size_t size_;
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
/// ================================================================================================
/// === Class Declarations	========================================================================

template<typename T>
class Array_ptr<const T>
{
public:
	/// === Basic Types	============================================================================

	typedef const T* const_iterator;
	typedef const T& const_reference;

	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// \brief	Default constructor
	Array_ptr()
			: array_(NULL), size_(0)
	{
	}

	/// \brief	Construct provided for compatibility with code that does not use Array_ptr
	///			It can deduce array size at compile-time.
	/// \warning	New code should not use this constructor
	template<size_t L>
	Array_ptr(const T (&_array)[L])
			: array_(&_array[0]), size_(L)
	{
	}

	/// \brief	Construct provided for compatibility with code that does not use Array_ptr
	/// \warning	New code should not use this constructor
	Array_ptr(const T* const _data, const size_t _len)
			: array_(_data), size_(_len)
	{
	}

	template<size_t L>
	Array_ptr(const Array<T, L>& _array)
			: array_(_array.begin()), size_(L)
	{
	}

	template<typename T2>
	Array_ptr(const Array_ptr<const T2> _array)
			: array_(reinterpret_cast<const T*>(_array.begin())), size_(_array.max_size())
	{

	}

	/// --- Capacity	----------------------------------------------------------------------------

	/// \brief	Returns the maximum number of elements the array is able to hold due to system
	///			or library implementation limitations.
	inline size_t max_size() const
	{
		return size_;
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline const_reference operator[](size_t _pos) const
	{
		assert(_pos < max_size());
		return array_[_pos];
	}

	inline const_iterator data() const
	{
		return array_;
	}

	/// \brief
	/// \param[in]	_pos	Position of the first character to include
	/// \param[in] _count	Length of the subarray
	const Array_ptr<const T> subarray(size_t _pos, size_t _count) const
	{
		return Array_ptr<const T>(&array_[min(_pos, size_ - 1)], min(size_ - _pos, _count));
	}

	/// --- Iterators	----------------------------------------------------------------------------

	inline const_iterator begin() const
	{
		return array_;
	}

	inline const_iterator end() const
	{
		return &array_[size_];
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	const T* array_;
	const size_t size_;
};
}    /// femtin

#endif	/// FEMTIN_ARRAY_HPP_
/// === END OF FILE	================================================================================
