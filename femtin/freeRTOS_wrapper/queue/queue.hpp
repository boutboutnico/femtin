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
/// \file	queue.hpp
/// \brief	Cpp wrapper around FreeRTOS queue
/// \date	06/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_QUEUE_HPP_
#define FEMTIN_QUEUE_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "queue.h"

#include "femtin/freeRTOS_wrapper/freeRTOS_wrapper.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace os
{

/// === Class Declarations	========================================================================

class Queue
{
public:
	/// Public Declarations	========================================================================

	Queue(const UBaseType_t _n_msg, const UBaseType_t _msg_size);

	/// --- Element Access	------------------------------------------------------------------------

	inline QueueHandle_t handle() const;

	/// --- Capacity	----------------------------------------------------------------------------

	inline UBaseType_t messagesWaiting() const;
	inline UBaseType_t spacesAvailable() const;

	/// --- Operations	----------------------------------------------------------------------------

	inline void reset();

	bool sendToBack(const void* _pItem, TickType_t _timeout_ms = TIMEOUT_MAX) const;
	bool sendToFront(const void* _pItem, TickType_t _timeout_ms = TIMEOUT_MAX) const;

	bool receive(void* _pBuffer, TickType_t _timeout_ms = TIMEOUT_MAX);

private:
	/// Private Declarations	====================================================================
	/// Private Attributs	========================================================================

	QueueHandle_t handle_;

};

/// === Inline Definitions	========================================================================

inline QueueHandle_t Queue::handle() const
{
	return handle_;
}

/// ------------------------------------------------------------------------------------------------

inline UBaseType_t Queue::messagesWaiting() const
{
	return uxQueueMessagesWaiting(handle_);
}

/// ------------------------------------------------------------------------------------------------

inline UBaseType_t Queue::spacesAvailable() const
{
	return uxQueueSpacesAvailable(handle_);
}

/// ------------------------------------------------------------------------------------------------

inline void Queue::reset()
{
	xQueueReset(handle_);
}

/// ------------------------------------------------------------------------------------------------

}
}
#endif
/// END OF FILE	====================================================================================
