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
/// \file	buffer.hpp
/// \brief	Buffer manipulation utility
/// \date	25/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef BUFFER_HPP_
#define BUFFER_HPP_

/// ===	Includes	================================================================================

#include <stdint.h>
#include <cstring>
#include <assert.h>

#include "algorithm.hpp"
#include "endian.hpp"
#include "string.hpp"

/// ===	Namespaces	================================================================================

namespace femtin
{
/// ===	Class Declarations	========================================================================

///
/// \warning	Len limitation define by n_write_ and n_read_ variable numerical limits. In our case
///				count_value_type = uin16_t = 0xFFFF.
///
template<size_t Len>
class Buffer
{

public:
	/// === Basic Types	============================================================================

	typedef uint8_t value_type;
	typedef value_type* pointer;
	typedef const pointer const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	/// ===	Public Enumerations	====================================================================
	/// ===	Public Declarations	====================================================================

	/// --- Member functions	--------------------------------------------------------------------

	/// \brief	Default constructor
	Buffer() :
			SIZE_MAX_(Len)
	{
		assert(Len > 0);
		clear();
	}

	/// \brief		Copy constructor.
	template<size_t L>
	Buffer(const Buffer<L>& _b) :
			Buffer
			{ }
	{
		memmove(mem_, _b.data(), sizeof(value_type) * femtin::min(Len, L));
		write_ = &mem_[femtin::min(Len, L)];
	}

	/// \brief	Copy constructor
	Buffer(const Buffer& _b) = delete;

	/// \brief	Copy assignment
//	Buffer& operator=(const Buffer& _b) = delete;

	///	\brief	Copy assignment
	Buffer& operator=(const Buffer& _b)
	{
		assert(_b.size() <= capacity());

		memmove(mem_, _b.data(), sizeof(value_type) * femtin::min(capacity(), _b.size()));
		write_ = &mem_[femtin::min(capacity(), _b.size())];
		read_ = mem_;
		return *this;
	}

	template<size_t L>
	Buffer& operator=(const Buffer<L>& _b)
	{
		assert(_b.size() <= capacity());

		memmove(mem_, _b.data(), sizeof(value_type) * femtin::min(capacity(), _b.size()));
		write_ = &mem_[femtin::min(capacity(), _b.size())];
		read_ = mem_;
		return *this;
	}

	///	\brief	Move assignment
	Buffer& operator=(Buffer&& _rb) = delete;

	/// --- Element access	------------------------------------------------------------------------

	inline const_reference end() const
	{
		assert(empty() == false);

		return *(write_ - 1);
	}

	const_reference operator[](const size_t _i) const
	{
		assert(_i <= size());
		return mem_[_i];
	}

	inline const value_type* data() const
	{
		return mem_;
	}

	template<typename T>
	T read() const;

	/// --- Capacity	----------------------------------------------------------------------------

	/// \brief	Is the buffer empty ?
	inline bool empty() const;

	/// \brief	Is the buffer full ?
	inline bool full() const;

	/// \brief	Returns the maximum number of elements the buffer is able to hold due to system
	///			or library implementation limitations.
	inline size_t max_size() const;

	/// \brief	Get the number of elements currently stored in the buffer.
	inline size_t size() const;

	/// \brief	Get number of elements which can be stored in the buffer.
	inline size_t capacity() const;

	/// --- Operations	----------------------------------------------------------------------------

	void clear();

	void fill(const value_type _val, const size_t _size = 0xFFFF);

	template<typename T>
	size_t add(const T _val);

	template<typename T, size_t L>
	size_t add(const T (&_a)[L]);

protected:
	/// === Protected Declarations	================================================================

	template<typename T>
	T get(const size_t _offset) const;

	/// === Protected Attributs	====================================================================

	value_type mem_[Len];
	const size_t SIZE_MAX_;

	pointer write_;
	mutable pointer read_;	///<Mutable to allow a read() method const
};

/// === Inline Definitions	========================================================================

template<size_t Len>
inline bool Buffer<Len>::empty() const
{
	return size() == 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline bool Buffer<Len>::full() const
{
	return size() == max_size();
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline size_t Buffer<Len>::max_size() const
{
	return SIZE_MAX_;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline size_t Buffer<Len>::size() const
{
	return reinterpret_cast<uint32_t>(write_) - reinterpret_cast<uint32_t>(mem_);
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline size_t Buffer<Len>::capacity() const
{
	return max_size() - size();
}

/// === Public Template Definitions	================================================================

/// TODO : Update destination attributs ?
//Buffer<Len>& Buffer<Len>::operator=(const Buffer<Len>& _b)
//{
//	clear();
//
//	assert(SIZE_MAX_ >= _b.max_size());
//
//	/// Ensure that destination buffer has enough space;
//	if (SIZE_MAX_ >= _b.max_size())
//	{
//		memmove(start_, _b.start_, _b.max_size());
//	}
//
//	return *this;
//}

/// ------------------------------------------------------------------------------------------------

//template<size_t Len>
//Buffer<Len>::const_reference Buffer<Len>::operator[](const size_t _i)
//{
//	assert(_i < size());
//
//	if (_i < size())
//	{
//		return mem_[_i];
//	}
//	else
//	{
//		return mem_[size() - 1];
//	}
//}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T>
T Buffer<Len>::read() const
{
	size_t offset = read_ - mem_;
	read_ += sizeof(T);
	return get<T>(offset);
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
void Buffer<Len>::clear()
{
	fill(0x00);
	write_ = mem_;
	read_ = mem_;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
void Buffer<Len>::fill(const value_type _val, const size_t _size)
{
	/// TODO Increment write_ ?
	/// TODO Fill from write_ ?
	memset(mem_, _val, sizeof(value_type) * min(max_size(), _size));
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T>
size_t Buffer<Len>::add(const T _val)
{
	assert(sizeof(T) <= capacity());

	if (sizeof(T) <= capacity())
	{
		T t_temp = endian_swap<T>(_val);
		memmove(write_, &t_temp, sizeof(T));

		write_ += sizeof(T);
		return sizeof(T);
	}
	return 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T, size_t L>
size_t Buffer<Len>::add(const T (&_a)[L])
{
	assert(Len * sizeof(T) <= capacity());

	/// Vérifier la place disponible
	if (Len * sizeof(T) <= capacity())
	{
		/// TODO use memmove ?
		memcpy(write_, &_a[0], Len * sizeof(T));
		write_ += Len * sizeof(T);
		return Len * sizeof(T);
	}
	return 0;
}

/// === Protected Template Definitions	============================================================

template<size_t Len>
template<typename T>
T Buffer<Len>::get(const size_t _offset) const
{
	assert((_offset + sizeof(T)) <= max_size());

	T temp = reinterpret_cast<const T*>(mem_ + _offset)[0];
	return endian_swap<T>(temp);
}

/// ------------------------------------------------------------------------------------------------
}/// Namespace femtin

#endif	/// BUFFER_HPP_/// === END OF FILE	================================================================================
