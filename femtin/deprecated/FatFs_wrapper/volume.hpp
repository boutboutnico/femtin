///
/// \file	volume.hpp
///	\brief	
///	\date	23/04/2015
/// \author	nboutin
///
#ifndef APPLICATION_FATFS_WRAPPER_VOLUME_HPP_
#define APPLICATION_FATFS_WRAPPER_VOLUME_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include "../chanN/FatFs/src/ff.h"

/// === Namespaces	================================================================================

namespace femtin
{

namespace fatfs
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class Volume
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	Volume();

	/// TODO constructor equivalent to mount

	/// TODO handle return value
	/// TODO use string
	/// TODO C++ concept: bitmaskType
	FRESULT mount(const char* _path, uint8_t _option);

	FRESULT unmount(const char* _path, uint8_t _option);

	uint32_t capacity() const;

	uint32_t free() const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	FATFS fatfs_;
//	femtin::String<11> path_;
	char path_[12];
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// fatfs
}	/// femtin

#endif	/// APPLICATION_FATFS_WRAPPER_VOLUME_HPP_
/// === END OF FILE	================================================================================
