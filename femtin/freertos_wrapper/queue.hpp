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

template <class T>
class Queue
{
public:
  /// --- Public Types

  typedef QueueHandle_t native_handle_t;

  /// --- Public Declarations

  Queue(const uint32_t _n_msg)
  {
    handle_ = xQueueCreate(_n_msg, sizeof(T));
    assert(handle_);
  }
  ~Queue() { vQueueDelete(handle_); };

  /// --- Element Access

  native_handle_t native_handle() const { return handle_; }

  /// --- Capacity

  uint32_t messages_waiting() const { return uxQueueMessagesWaiting(handle_); }
  uint32_t spaces_available() const { return uxQueueSpacesAvailable(handle_); }

  /// --- Operations

  void reset();

  void send_to_back(const T& _item) const;
  bool send_to_back_for(const T& _item, const std::chrono::milliseconds& _time) const;

  void send_to_front(const T& _item) const;
  bool send_to_front_for(const T& _item, const std::chrono::milliseconds& _time) const;

  bool receive(T& _item, const std::chrono::milliseconds& _time) const;

private:
  /// --- Private Attributs

  native_handle_t handle_;
};

/// === Inline Definitions

//// Since FreeRTOS V7.2.0 xQueueReset() always returns pdPASS.
// inline void Queue::reset() { xQueueReset(handle_); }

template <class T>
inline void Queue<T>::send_to_back(const T& _item) const
{
  xQueueSendToBack(handle_, &_item, TIMEOUT_MAX);
}

template <class T>
inline bool Queue<T>::send_to_back_for(const T& _item, const std::chrono::milliseconds& _time) const
{
  return xQueueSendToBack(handle_, _item, ticks(_time).count());
}

template <class T>
inline void Queue<T>::send_to_front(const T& _item) const
{
  xQueueSendToFront(handle_, _item, TIMEOUT_MAX);
}

template <class T>
inline bool Queue<T>::send_to_front_for(const T& _item,
                                        const std::chrono::milliseconds& _time) const
{
  return xQueueSendToFront(handle_, _item, ticks(_time).count());
}

template <class T>
inline bool Queue<T>::receive(T& _pBuffer, const std::chrono::milliseconds& _time) const
{
  return xQueueReceive(handle_, &_pBuffer, ticks(_time).count());
}
}
#endif
/// === END OF FILE
