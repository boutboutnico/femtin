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
/// \file	string.hpp
/// \brief	String container
/// \date	02/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef STRING_HPP_
#define STRING_HPP_

/// ===	Includes	================================================================================

#include <stdint.h>
#include <cstring>
#include <assert.h>

#include "algorithm.hpp"

/// ===	Namespaces	================================================================================

namespace femtin
{

/// ===	Class Declarations	========================================================================

template<size_t Len>
class String
{
public:
	/// === Basic Types	============================================================================

	typedef char value_type;
	typedef value_type* pointer;
	typedef const value_type& const_reference;

	/// === Constants	============================================================================

	///	\brief	end of string indicator or error indicator
	static const size_t npos = -1;

	/// ===	Public Declarations	====================================================================

	/// --- Member functions	--------------------------------------------------------------------

	/// \brief	Construct an empty string null-terminated.
	///			String<10> s;
	String()
			: write_(elems_)
	{
		memset(elems_, npos, max_size());
		_M_Terminate();
	}

	/// \brief		Construct a string from an array of value_type.
	/// \warning	"ab" L = 3 '\0' is included
	template<size_t L>
	String(const value_type (&_str)[L])
			: String()
	{
		memmove(elems_, _str, min(L, max_size()));
		write_ = &elems_[min(L, max_size()) - 1];
		_M_Terminate();
	}

#if 0
	/// \brief		Construct a string with a substring [_pos; _pos + _count]
	///				from an array of value_type.
	/// \param[in]	_pos: start index
	/// \param[in]	_count: number of element to copy
	/// \warning	If _count-1 - _pos > max_size, the resulting substring is [_pos, _pos + size()].
	/// \warning	"ab" L = 3 '\0' is included
	template<size_t L>
	explicit String(const value_type (&_str)[L], size_t _pos, size_t _count = npos) :
	String()
	{
		assert(_pos < L);    /// Index out of range

		size_t i = 0;
		for (; i < min(_count, max_size()); i++)
		{
			elems_[i] = _str[i + _pos];
		}
		write_ = &elems_[++i];
		_M_Terminate();
	}
#endif

	/// --- Copy Constructors	--------------------------------------------------------------------

	/// \brief	Constructor String from string with same size
	String(const String& _s)
			: String()
	{
		memmove(elems_, _s.elems_, _s.size());
		write_ = &elems_[_s.size()];
		_M_Terminate();
	}

	/// \brief	Constructor String from string with smaller or bigger size
	template<size_t L>
	String(const String<L>& _s)
			: String()
	{
		size_t n = min(_s.size(), Len);
		memmove(elems_, _s.c_str(), n);
		write_ = &elems_[n];
		_M_Terminate();
	}

	/// \brief	Constructs the string with a substring [pos, pos+count) of other.
	template<size_t L>
	String(const String<L>& _s, size_t _pos, size_t _count = L)
			: String()
	{
		assert(_pos < L && _pos < _s.size());

		size_t i = 0;
		size_t n = min(_count, Len);
		while (i < n && _s.c_str()[i + _pos] != '\0')
		{
			elems_[i] = _s.c_str()[i + _pos];
			i++;
		}
		write_ = &elems_[i];
		_M_Terminate();
	}

	/// --- Copy Assignment	------------------------------------------------------------------------

	///	\brief	Copy assignment
	String& operator=(const String& _s)
	{
		memmove(elems_, _s.c_str(), femtin::min(_s.size(), Len));
		write_ = &elems_[femtin::min(_s.size(), Len)];
		_M_Terminate();
		return *this;
	}

	template<size_t L>
	String& operator=(const String<L>& _s)
	{
		memmove(elems_, _s.c_str(), femtin::min(_s.size(), Len));
		write_ = &elems_[femtin::min(_s.size(), Len)];
		_M_Terminate();
		return *this;
	}

	/// --- Move Constructor and Assignment	--------------------------------------------------------

	String(String&& _s)
	{
		memmove(elems_, _s.c_str(), femtin::min(_s.size(), Len));
		write_ = &elems_[femtin::min(_s.size(), Len)];
		_M_Terminate();
	}

#if 0
//	String()
//			: write_(elems_)
//	{
//		_M_Terminate(size());
//	}
//

//
//	String(String&& _s) = default;
//
//	String(const char* _str, size_t _count)
//	{
//		assert(Len >= _count);
//		memmove(elems_, _str, _count);
//		write_ = &elems_[_count];
//		_M_Terminate(_count);
//	}
//
/////
///// \brief	Constructs the string with a substring [pos, pos+count) of other.
/////
//	template<size_t L>
//	String(const String<L>& _s, size_t _pos = 0, size_t _count = Len)
//			: String()
//	{
//		assert(_pos < L);
//		assert(max_size() >= _count - _pos);
//
//		memmove(elems_, &_s.c_str()[_pos], _count);
//		write_ = &elems_[_count - _pos];
//		_M_Terminate(size());
//	}
//
//	///	\brief	Copy assignment
//	String& operator=(const String& _s)
//	{
////		assert(_s.max_size() <= max_size());
//
//		memmove(elems_, _s.c_str(), sizeof(value_type) * femtin::min(_s.max_size(), max_size()));
//		write_ = &elems_[femtin::min(_s.max_size(), max_size())];
//		_M_Terminate(size());
//		return *this;
//	}
//

//
//	///	\brief	Move assignment
//	/// TODO not really a move assignment!!!
//	String& operator=(String&& _s)
//	{
//		assert(_s.size() <= capacity());
//
//		memmove(elems_, _s.c_str(), sizeof(value_type) * femtin::min(capacity(), _s.size()));
//		write_ = &elems_[femtin::min(capacity(), _s.size())];
//		_M_Terminate(size());
//		return *this;
//	}
#endif

	/// --- Element access	------------------------------------------------------------------------

	inline const value_type* c_str() const
	{
		return elems_;
	}

	const_reference operator[](const size_t _i) const
	{
		assert(_i <= size());
		return elems_[_i];
	}

	/// --- Capacity	----------------------------------------------------------------------------

	/// \brief	Is the buffer empty ?
	inline bool empty() const
	{
		return (size() == 0 && Len != 0);
	}

	/// \brief	Is the buffer full ?
	inline bool full() const
	{
		return size() == Len;
	}

	/// \brief	Get the number of elements currently stored in the buffer.
	inline size_t size() const
	{
		return reinterpret_cast<uint32_t>(write_) - reinterpret_cast<uint32_t>(elems_);
	}

	/// \brief	Get number of elements which can be stored in the buffer.
	inline size_t capacity() const
	{
		return Len - size();
	}

	/// --- Operations	----------------------------------------------------------------------------

	String& operator+=(value_type _c)
	{
		assert(capacity() >= 1);

		*write_ = _c;
		write_++;
		_M_Terminate();
		return *this;
	}

	String& operator+=(const String& _s)
	{
		assert(_s.size() <= capacity());

		memcpy(write_, _s.c_str(), _s.size());
		write_ += _s.size();
		_M_Terminate();
		return *this;
	}

	void clear()
	{
		write_ = elems_;
		_M_Terminate();
	}

	size_t count(const char _c, size_t _pos = 0, size_t _count = Len) const
	{
		if (_pos >= size()) return 0;

		size_t n = 0;
		for (size_t i = _pos; i <= min(_count, size()); i++)
		{
			if (elems_[i] == _c)
			{
				n++;
			}
		}
		return n;
	}

	size_t find(const char _c, size_t _pos = 0, size_t _count = Len) const
	{
		if (_pos >= size()) return npos;

		for (size_t i = _pos; i <= min(_count, size()); i++)
		{
			if (elems_[i] == _c)
			{
				return i;
			}
		}
		return npos;
	}

	String substr(size_t _pos, size_t _count = Len) const
	{
		return String(*this, _pos, _count);
	}

protected:
	/// === Protected Declarations	================================================================

	/// \brief	Returns the maximum number of elements the string is able to hold due to system
	///			or library implementation limitations.
	/// \warning include '\0', equal to Len + 1
	inline size_t max_size() const
	{
		return Len + 1;
	}

	void _M_Terminate()
	{
		*write_ = '\0';
	}

	/// === Protected Attributs		================================================================

	value_type elems_[Len + 1];    /// include '\0'

	pointer write_;
};

/// === Public Inline Definitions	================================================================

/// ------------------------------------------------------------------------------------------------

template<size_t Ll, size_t Lr>
inline bool operator==(const String<Ll>& _lhs, const String<Lr>& _rhs)
{
	return ((_lhs.size() == _rhs.size()    ///
				&& memcmp(_lhs.c_str(), _rhs.c_str(), _lhs.size()) == 0) ? true : false);
}

/// ------------------------------------------------------------------------------------------------

template<size_t Ll, size_t Lr>
inline bool operator!=(const String<Ll>& _lhs, const String<Lr>& _rhs)
{
	return (_lhs == _rhs) ? false : true;
}

}    /// Namespace femtin

#endif	/// STRING_H_
/// === END OF FILE	================================================================================
