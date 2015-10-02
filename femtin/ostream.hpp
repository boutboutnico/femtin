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
#include "ios.hpp"

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

	void write(char _c);
	void write(const char* _s);
//	void write(int8_t _n);
//	void write(int16_t _n);
//	void write(int32_t _n);
//	void write(uint8_t _n);
//	void write(uint16_t _n);
//	void write(uint32_t _n);
//	void write(float _n);
////	void write(double _n);
//	void write(bool _b);
//	void write(fmtflags _f);

protected:
	///	===	Protected Declarations	================================================================

	virtual void write(const char* _s, size_t _size) = 0;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================
};

/// === Inlines Definitions	========================================================================

inline void ostream::write(char _c)
{
	write(&_c, 1);
}

inline void ostream::write(const char* _s)
{
	write(_s, strlen(_s));
}

///	=== Non-Members Definitions	====================================================================

template<class T>
inline ostream& operator<<(ostream& _stream, T _arg)
{
	_stream.write(_arg);
	return _stream;
}

/// ------------------------------------------------------------------------------------------------
}/// femtin

#endif
/// === END OF FILE	================================================================================
