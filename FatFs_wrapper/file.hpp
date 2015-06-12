///
/// \file	file.hpp
///	\brief	
///	\date	24/04/2015
/// \author	nboutin
///
#ifndef APPLICATION_FATFS_WRAPPER_FILE_HPP_
#define APPLICATION_FATFS_WRAPPER_FILE_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <cstddef>
#include "femtin/string.hpp"
#include "../chanN/FatFs/src/ff.h"

/// === Namespaces	================================================================================

namespace femtin
{

namespace fatfs
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class File
{
public:
	/// === Constants	============================================================================

	static const size_t FILENAME_SIZE = 8 + 1 + 3;

	/// === Public Declarations	====================================================================

	File();

	FRESULT open(const femtin::String<FILENAME_SIZE>& _filename, uint8_t _mode);
	FRESULT close();
	FRESULT sync();
	FRESULT lseek(uint32_t _offset);

	char* gets(char* _str, size_t _len);

//	int16_t putc(const char _c);
	int16_t puts(const char* _str);

	inline uint32_t size() const;

	inline bool eof() const;

	/// --- Accessors	----------------------------------------------------------------------------

	inline const femtin::String<FILENAME_SIZE>& name() const
	{
		return name_;
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	FIL file_;
	femtin::String<FILENAME_SIZE> name_;
};

/// === Inlines Declarations	====================================================================

inline uint32_t File::size() const
{
	return f_size(&file_);
}

/// ------------------------------------------------------------------------------------------------

inline bool File::eof() const
{
	return f_eof(&file_);
}

/// ------------------------------------------------------------------------------------------------
}/// fatfs
}    /// femtin

#endif	/// APPLICATION_FATFS_WRAPPER_FILE_HPP_
/// === END OF FILE	================================================================================
