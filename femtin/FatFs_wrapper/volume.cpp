///
/// \file	volume.cpp
///	\brief	
///	\date	23/04/2015
/// \author	nboutin
///

#include "volume.hpp"
using namespace femtin::fatfs;

/// === Includes	================================================================================

#include <cstddef>
#include <cstring>

/// === Namespaces	================================================================================
/// === Constants	================================================================================
/// === Public Definitions	========================================================================

Volume::Volume()
		: fatfs_(), path_()
{
	memset(path_, 0, sizeof(char) * 12);
}

/// ------------------------------------------------------------------------------------------------

FRESULT Volume::mount(const char* _path, uint8_t _option)
{
	memcpy(path_, _path, sizeof(char) * 12);
	return f_mount(&fatfs_, _path, _option);
}

/// ------------------------------------------------------------------------------------------------

FRESULT Volume::unmount(const char* _path, uint8_t _option)
{
	return f_mount(NULL, _path, _option);
}

/// ------------------------------------------------------------------------------------------------

uint32_t Volume::capacity() const
{
	FATFS *fs;
	uint32_t free_cluster = 0;

	FRESULT fres = f_getfree(path_, &free_cluster, &fs);

	if (fres == FR_OK)
	{
		return ((fs->n_fatent - 2) * fs->csize) / 2;
	}
	else
	{
		return 0;
	}
}

/// ------------------------------------------------------------------------------------------------

uint32_t Volume::free() const
{

	FATFS *fs;
	uint32_t free_cluster = 0;

	FRESULT fres = f_getfree(path_, &free_cluster, &fs);

	if (fres == FR_OK)
	{
		return (free_cluster * fs->csize) / 2;
	}
	else
	{
		return 0;
	}
}

/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
