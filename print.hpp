///
/// \file		print.h
/// \brief		Print utility
/// \author		nboutin
/// \date
///

#ifndef PRINT_H_
#define PRINT_H_

/// ===	INCLUDES	================================================================================

#include <stdio.h>
#include <string.h>

/// ===	NAMESPACES	================================================================================

#undef printd

//#ifdef	__cplusplus
//extern "C" {
//#endif

#ifdef FEMTIN_DEBUG_

#define printd(fmt, args...) ( printf(fmt, ##args); printf("\n"); )

#else

#define printd(fmt, args...)	((void)0)

#endif

//#ifdef	__cplusplus
//}
//#endif

#endif	/// PRINT_H_
/// === END OF FILE	===============================================================================
