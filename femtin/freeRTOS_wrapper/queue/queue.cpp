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
/// \file	queue.cpp
/// \brief	Cpp wrapper around FreeRTOS queue
/// \date	06/04/2015
/// \author	nboutin
///
/// ================================================================================================
#include "queue.hpp"
using namespace os;

/// === Includes	================================================================================

#include <cassert>

/// === Public Definitions	========================================================================

Queue::Queue(const UBaseType_t _n_msg, const UBaseType_t _msg_size)
		: handle_()
{
	handle_ = xQueueCreate(_n_msg, _msg_size);

	assert(handle_ != 0);
}

/// ------------------------------------------------------------------------------------------------

bool Queue::sendToBack(const void* _pItem, TickType_t _timeout_ms) const
{
	return xQueueSendToBack(handle_, _pItem, _timeout_ms);
}

/// ------------------------------------------------------------------------------------------------

bool Queue::sendToFront(const void* _pItem, TickType_t _timeout_ms) const
{
	return xQueueSendToFront(handle_, _pItem, _timeout_ms);
}

/// ------------------------------------------------------------------------------------------------

bool Queue::receive(void* _pBuffer, TickType_t _timeout_ms)
{
	return xQueueReceive(handle_, _pBuffer, _timeout_ms);
}

/// === Private Definitions	========================================================================
/// === END OF FILE	================================================================================
