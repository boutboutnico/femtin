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
/// \file	scoped_locking.hpp
/// \brief	Implements scoped locking idiom.
/// \date	31/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_SCOPED_LOCKING_HPP_
#define FEMTIN_SCOPED_LOCKING_HPP_

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace femtin
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

template<class Lock>
class Guard
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// \brief	Store a reference to the lock and acquire it.
	Guard(Lock& _lock)
			: lock_(_lock)
	{
		is_acquired_ = lock_.acquire();
	}

	/// \brief	Release the lock when the guard goes out of scope
	~Guard()
	{
		if (is_acquired_ == true)
		{
			lock_.release();
		}
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	Lock& lock_;	///! Reference to managed lock.
	bool is_acquired_;    ///! Record if the lock was acquired.
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// femtin

#endif	/// FEMTIN_SCOPED_LOCKING_HPP_
/// === END OF FILE	================================================================================
