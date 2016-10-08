///
/// \file	trace.cpp
///	\brief	
///	\date	2 janv. 2016
/// \author	nb_work
///

#include "trace.hpp"
using namespace femtin;

#ifdef FEMTIN_TRACE

/// === Includes

#include <cstdarg>


/// === Static Definitions

char Trace::buffer_[BUFFER_LENGHT];

/// === Extern Declarations

extern void femtin_write(const char* _str, size_t _size);

/// === Public Definitions	========================================================================

void Trace::print(const char* _s)
{
	puts(_s);
}

/// ------------------------------------------------------------------------------------------------

void Trace::print(const char* _tag, const char* _format, ...)
{
	va_list arg;
	va_start(arg, _format);

	size_t size = vsprintf(buffer_, _format, arg);

	femtin_write(buffer_, size);

	va_end(arg);
}

/// ================================================================================================
#endif
