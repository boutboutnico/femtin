///
/// \file		endian.h
/// \brief		Endian manipulation utility
/// \author		nboutin
/// \date
///

#ifndef ENDIAN_H_
#define ENDIAN_H_

/// ===	INCLUDES	================================================================================

/// ===	NAMESPACES	================================================================================

namespace femtin
{

/// TODO Use ARM specific ASM instruction
template<typename T>
T endian_swap(const T _val)
{
	union
	{
		T val_;
		uint8_t a_[sizeof(T)];
	} source, dest;

	source.val_ = _val;

	for (size_t i = 0; i < sizeof(T); i++)
	{
		dest.a_[i] = source.a_[sizeof(T) - i - 1];
	}

	return dest.val_;
}

} /// Namespace femtin

#endif	/// ENDIAN_H_
/// === END OF FILE	================================================================================
