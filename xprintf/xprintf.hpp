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
/// \file	xprtinf.hpp
/// \brief
/// \date	30/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_XPRINTF_HPP_
#define FEMTIN_XPRINTF_HPP_

/// === Includes	================================================================================

#include <cstddef>
#include <stdarg.h>

/// === Namespaces	================================================================================

namespace femtin
{

void xvsnprintf(char* _buffer, size_t _buf_size, const char* _format, va_list _vlist);

}    /// femtin

#endif	/// FEMTIN_XPRINTF_HPP_
/// === END OF FILE	================================================================================
