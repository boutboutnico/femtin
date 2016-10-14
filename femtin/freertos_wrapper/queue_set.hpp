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
/// \brief	Cpp wrapper around FreeRTOS queue set
/// \date	14/10/2016
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_QUEUE_SET_HPP_
#define FEMTIN_QUEUE_SET_HPP_

/// === Includes

#include <cassert>

#include "FreeRTOS.h"
#include "queue.h"

/// === Namespaces

namespace femtin
{

/// === Class Declarations

class Queue_Set
{
public:
  /// --- Public Types

  typedef QueueSetHandle_t native_handle_t;
  typedef QueueSetMemberHandle_t member_handle_t; /// TODO Use same type as Queue::handle_t

  /// --- Public Functions

  Queue_Set(uint8_t _n_queue)
  {
    handle_ = xQueueCreateSet(_n_queue);
    assert(handle_);
  }

  /// --- Operations

  void add(member_handle_t _member);
  void remove(member_handle_t _member);
  member_handle_t select(const std::chrono::milliseconds& _time) const;

private:
  /// --- Private Attributes

  native_handle_t handle_;
};

/// === Inlines Definitions

inline void Queue_Set::add(member_handle_t _member)
{
  auto r = xQueueAddToSet(_member, handle_);
  assert(r == pdPASS);
}

inline void Queue_Set::remove(member_handle_t _member)
{
  auto r = xQueueRemoveFromSet(_member, handle_);
  assert(r == pdPASS);
}

Queue_Set::member_handle_t Queue_Set::select(const std::chrono::milliseconds& _time) const
{
  /// TODO xQueueSelectFromSetFromISR
  return xQueueSelectFromSet(handle_, ticks(_time).count());
}
}
#endif
/// === END OF FILE
