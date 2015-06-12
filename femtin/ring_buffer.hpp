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
/// \file	ring_buffer.hpp
/// \brief	Ring Buffer container
/// \date	25/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef RING_BUFFER_HPP_
#define RING_BUFFER_HPP_

/// ===	Includes	================================================================================

#include <cstddef>
#include <cstring>
#include <assert.h>

#include "algorithm.hpp"

/// ===	Namespaces	================================================================================

namespace femtin
{
/// ===	Class Declarations	========================================================================

///
/// \warning	Len limitation define by n_write_ and n_read_ variable numerical limits. In our case
///				count_value_type = uin16_t = 0xFFFF.
///
template<size_t Len>
class Ring_Buffer
{
public:
	/// === Basic Types	============================================================================

	typedef uint8_t value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef int16_t count_value_type;
	typedef uint16_t distance_type;

	/// ===	Public Enumerations	====================================================================
	/// ===	Public Declarations	====================================================================

	/// --- Member functions	--------------------------------------------------------------------

	/// \brief	Default constructor
	Ring_Buffer() :
			SIZE_MAX_(Len), end_(&mem_[Len])
	{
		assert(Len > 0);
		clear();
	}

	/// \brief	Copy constructor
	template<size_t L>
	Ring_Buffer(const Ring_Buffer<L>& _rb) :
			Ring_Buffer
			{ }
	{
		memmove(mem_, _rb.data(), sizeof(value_type) * femtin::min(Len, L));
		n_write_ = static_cast<count_value_type>(femtin::min(Len, L));
		write_ = &mem_[femtin::min(Len, L)];
	}

	/// \brief	Copy assignment
	Ring_Buffer& operator=(const Ring_Buffer& _rb) = delete;

	///	\brief	Move assignment
	Ring_Buffer& operator=(Ring_Buffer&& _rb) = delete;

	/// --- Element access	------------------------------------------------------------------------

	/// \brief	Access underlying array.
	inline const value_type* data() const
	{
		return mem_;
	}

	template<typename T>
	T read();

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

	void fill(const value_type _val, const size_t _size = 0xFFFFFFFF);

	template<typename T>
	size_t add(const T _val);

	template<typename T, size_t L>
	size_t add(const T (&_a)[L]);

protected:
	/// === Protected Declarations	================================================================

	inline void inc_write();

	inline void inc_read();

	/// === Protected Attributs	====================================================================

	value_type mem_[Len];
	const size_t SIZE_MAX_;

	const pointer end_;

	count_value_type n_write_;
	pointer write_;

	///<Mutable to allow a read() method const
	mutable count_value_type n_read_;
	mutable pointer read_;
};

/// === Public Inline Definitions	================================================================

template<size_t Len>
inline bool Ring_Buffer<Len>::empty() const
{
	return size() == 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline bool Ring_Buffer<Len>::full() const
{
	return size() == max_size();
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline size_t Ring_Buffer<Len>::max_size() const
{
	return SIZE_MAX_;
}

/// ------------------------------------------------------------------------------------------------

/// \brief	The unsigned difference (n_write_ - n_read_) always yields the number
///			of items placed in the buffer and not yet retrieved.
template<size_t Len>
inline size_t Ring_Buffer<Len>::size() const
{
	return static_cast<distance_type>(n_write_ - n_read_);
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline size_t Ring_Buffer<Len>::capacity() const
{
	return max_size() - size();
}

/// === Protected Inline Definitions	============================================================

template<size_t Len>
inline void Ring_Buffer<Len>::inc_write()
{
	n_write_++;
	if (++write_ == end_)
	{
		write_ = mem_;
	}
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
inline void Ring_Buffer<Len>::inc_read()
{
	n_read_++;
	if (++read_ == end_)
	{
		read_ = mem_;
	}
}

/// === Public Template Definitions	================================================================

template<size_t Len>
void Ring_Buffer<Len>::clear()
{
	fill(0);
	write_ = mem_;
	read_ = mem_;
	n_write_ = 0;
	n_read_ = 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
void Ring_Buffer<Len>::fill(const value_type _val, const size_t _size)
{
	/// TODO Increment write_ ?
	/// TODO Fill from write_ ?
	memset(mem_, _val, sizeof(value_type) * femtin::min(max_size(), _size));
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T>
size_t Ring_Buffer<Len>::add(const T _val)
{
	assert(sizeof(T) <= capacity());

	if (sizeof(T) <= capacity())
	{
		for (int8_t i = (int8_t) (sizeof(T) - 1); i >= 0; i--)
		{
			write_[0] = static_cast<value_type>(_val >> (i * 8));
			inc_write();
		}

		return sizeof(T);
	}
	return 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T, size_t L>
size_t Ring_Buffer<Len>::add(const T (&_a)[L])
{
	assert(L * sizeof(T) <= capacity());

	if (L * sizeof(T) <= capacity())
	{
		size_t n = 0;
		for (size_t i = 0; i < L; i++)
		{
			n += add(_a[i]);
		}
		return n;
	}
	return 0;
}

/// ------------------------------------------------------------------------------------------------

template<size_t Len>
template<typename T>
T Ring_Buffer<Len>::read()
{
	assert(sizeof(T) <= size());

	T tmp = 0;

	for (size_t i = 0; i < sizeof(T); i++)
	{
		tmp = static_cast<T>(tmp << 8);
		tmp = static_cast<T>(tmp | read_[0]);
		inc_read();
	}
	return tmp;
}

/// === Protected Template Definitions	============================================================
/// ------------------------------------------------------------------------------------------------
}/// Namespace femtin

#endif	/// RING_/// === END OF FILE	================================================================================
