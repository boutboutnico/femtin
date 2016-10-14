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
/// \file	queue_set_demo.cpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

#include "queue_set_demo.hpp"
using namespace femtin::demo;

/// === Includes

#include "bsp/led/led.hpp"

#include "freertos_wrapper/queue.hpp"
#include "freertos_wrapper/queue_set.hpp"

/// === Namespaces

using namespace board::led;

/// === Static Definitions

static const uint16_t VAL16 = 0x1234;
static const uint32_t VAL32 = 0x56789ABC;
femtin::Queue<uint32_t> queue(2);

struct msg_t
{
  uint16_t u16;
  uint32_t u32;

  friend bool operator==(msg_t _x, msg_t _y) { return (_x.u16 == _y.u16 && _x.u32 == _y.u32); }
};

static const msg_t MSG{ VAL16, VAL32 };

femtin::Queue<msg_t> queue_msg(2);

/// === Public Definitions

Task1::Task1() : Task("Task1", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void Task1::run()
{
  uint32_t write = VAL32;
  msg_t msg      = MSG;

  for (;;)
  {
    LED_Green.on();
    this_task::sleep_for(std::chrono::seconds(1));
    queue.send_to_back(write);
    this_task::sleep_for(std::chrono::seconds(1));

    LED_Blue.on();
    this_task::sleep_for(std::chrono::seconds(1));
    queue_msg.send_to_back(msg);
    this_task::sleep_for(std::chrono::seconds(1));
  }
}

/// ------------------------------------------------------------------------------------------------

Task2::Task2() : Task("Task2", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void Task2::run()
{
  uint32_t read = 0;
  auto msg_read = msg_t{};

  Queue_Set qset(2);
  qset.add(queue.native_handle());
  qset.add(queue_msg.native_handle());

  for (;;)
  {

    auto member = qset.select(std::chrono::seconds(5));

    if (member == queue.native_handle())
    {
      queue.receive(read, std::chrono::seconds(0));

      if (read == VAL32)
        LED_Green.off();
      else
        LED_Red.on();
    }
    else if (member == queue_msg.native_handle())
    {
      queue_msg.receive(msg_read, std::chrono::seconds(0));

      if (msg_read == MSG)
        LED_Blue.off();
      else
        LED_Red.on();
    }
    /// Timeout
    else
    {
      LED_Orange.toggle();
      this_task::sleep_for(std::chrono::milliseconds(500));
    }
  }
}

/// === END OF FILE
