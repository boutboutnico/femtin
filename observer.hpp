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
/// \file	observer.hpp
/// \brief	Design pattern observer implementation
/// \date	19/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

/// ===	Includes	================================================================================

#include <cstdint>
#include <cstddef>
#include <cstring>

#include "femtin/algorithm.hpp"

/// === Namespaces	================================================================================
namespace femtin
{

/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

template<typename T>
class Observer
{
public:
	/// === Public Declarations	====================================================================

	Observer();

	virtual void update(const T& _data) const = 0;
};
/// === Public Template Definitions	================================================================

template<typename T>
Observer<T>::Observer()
{
	/// Nothing to do
}

/// === Class Declarations	========================================================================

template<typename T, size_t N>
class Observable
{
public:
	/// === Public Declarations	====================================================================

	Observable()
			: count_(0)
	{
		memset(listeners_, 0x00, sizeof(const Observer<T>*) * N);
	}

	bool subscribe(const Observer<T>& _observer)
	{
		if (count_ < N)
		{
			listeners_[count_++] = &_observer;
			return true;
		}
		else
		{
			return false;
		}
	}

	void notify(const T& _data)
	{
		for (size_t i = 0; i < min<size_t>(count_, N); i++)
		{
			if (listeners_[i] != NULL)
			{
				listeners_[i]->update(_data);
			}
		}
	}

private:
	/// === Private Attributes	====================================================================

	const Observer<T>* listeners_[N];    /// TODO use femtin::Array
	size_t count_;
};

#pragma GCC diagnostic pop

/// ------------------------------------------------------------------------------------------------
}/// femtin
#endif /// OBSERVER_HPP_
/// ===	END OF FILE	================================================================================
