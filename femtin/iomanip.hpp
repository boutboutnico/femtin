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
/// \file	iomanip.hpp
/// \brief
/// \date	06/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_IOMANIP_HPP_
#define FEMTIN_IOMANIP_HPP_

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace femtin
{

/// === Inlines Definitions	========================================================================

struct _Setw
{
	size_t _M_n;
};

inline _Setw width(int _w)
{
	return
	{	_w};
}

inline ostream& operator<<(ostream& _stream, _Setw _w)
{
	_stream.width(_w._M_n);
	return _stream;
}

/// ------------------------------------------------------------------------------------------------
}
/// femtin

#endif
/// === END OF FILE	================================================================================
