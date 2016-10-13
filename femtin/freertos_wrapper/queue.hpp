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

/// === Includes

#include <cassert>

#include "FreeRTOS.h"
#include "queue.h"

/// === Namespaces

namespace femtin
{

/// === Class Declarations

class Queue
{
public:
  /// --- Public Types

  typedef QueueHandle_t native_handle_t;

  /// --- Public Declarations

  /// TODO deduce msg_size at compile time
  Queue(const uint32_t _n_msg, const uint32_t _msg_size)
  {
    handle_ = xQueueCreate(_n_msg, _msg_size);
    assert(handle_);
  }

  /// --- Element Access

  native_handle_t native_handle() const;

  /// --- Capacity

  uint32_t messages_waiting() const;
  uint32_t spaces_available() const;

  /// --- Operations

  void reset();

  /// TODO use better-type argument
  void send_to_back(const void* _pItem) const;
  bool send_to_back_for(const void* _pItem, const std::chrono::milliseconds& _time) const;

  void send_to_front(const void* _pItem) const;
  bool send_to_front_for(const void* _pItem, const std::chrono::milliseconds& _time) const;

  bool receive(void* _pBuffer, const std::chrono::milliseconds& _time);

private:
  /// --- Private Attributs

  native_handle_t handle_;
};

/// === Inline Definitions

inline Queue::native_handle_t Queue::native_handle() const { return handle_; }

inline uint32_t Queue::messages_waiting() const { return uxQueueMessagesWaiting(handle_); }

inline uint32_t Queue::spaces_available() const { return uxQueueSpacesAvailable(handle_); }

// Since FreeRTOS V7.2.0 xQueueReset() always returns pdPASS.
inline void Queue::reset() { xQueueReset(handle_); }

inline void Queue::send_to_back(const void* _pItem) const
{
  xQueueSendToBack(handle_, _pItem, TIMEOUT_MAX);
}

inline bool Queue::send_to_back_for(const void* _pItem,
                                    const std::chrono::milliseconds& _time) const
{
  return xQueueSendToBack(handle_, _pItem, ticks(_time).count());
}

inline void Queue::send_to_front(const void* _pItem) const
{
  xQueueSendToFront(handle_, _pItem, TIMEOUT_MAX);
}

inline bool Queue::send_to_front_for(const void* _pItem,
                                     const std::chrono::milliseconds& _time) const
{
  return xQueueSendToFront(handle_, _pItem, ticks(_time).count());
}

inline bool Queue::receive(void* _pBuffer, const std::chrono::milliseconds& _time)
{
  return xQueueReceive(handle_, _pBuffer, ticks(_time).count());
}
}
#endif
/// === END OF FILE
