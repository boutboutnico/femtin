///
/// \file		trace.hpp
/// \brief		Trace utility
/// \author		nboutin
/// \date
///

#ifndef FEMTIN_TRACE_HPP
#define FEMTIN_TRACE_HPP

/// ===	INCLUDES	================================================================================

#include <stdio.h>
#include <string.h>

/// ===	NAMESPACES	================================================================================

#ifdef FEMTIN_TRACE

namespace femtin
{

class Trace
{
public:
	/// --- Public Functions

	static void print(const char* _s);
	static void print(const char* _tag, const char* _format, ...);

private:
	/// --- Private Constants

	static const uint8_t BUFFER_LENGHT = 128;

	/// --- Private Attributs

	static char buffer_[BUFFER_LENGHT];
};

#endif

/// ------------------------------------------------------------------------------------------------

#ifdef FEMTIN_TRACE

#define TRACE(_str) femtin::Trace::print(_str)
#define TRACE_F(_tag, _fmt, ...) femtin::Trace::print(_tag, _fmt, ##__VA_ARGS__)

#else

#define TRACE(_str)
#define TRACE_F(_tag, _fmt, ...)

#endif

}
#endif
/// === END OF FILE	===============================================================================
