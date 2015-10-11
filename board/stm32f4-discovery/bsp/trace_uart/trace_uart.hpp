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
/// \file	trace_uart.hpp
/// \brief
/// \date	08/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef BSP_TRACE_UART_TRACE_UART_HPP_
#define BSP_TRACE_UART_TRACE_UART_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "femtin/ostream.hpp"
#include "femtin/freeRTOS_wrapper/semaphore/semaphore.hpp"
#include "femtin/freeRTOS_wrapper/semaphore/mutex.hpp"
#include "bsp/peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{
/// === Forward Declarations	====================================================================

class Trace_UART;

/// === Extern Declarations	========================================================================

extern Trace_UART trace;

/// === Class Declarations	========================================================================

class Trace_UART : public PeripheralHandler, public femtin::ostream
{
public:
	/// === Public Declarations	====================================================================

	Trace_UART();

	bool initialize(uint32_t _speed);

private:
	/// === Private Constants	====================================================================

	static const size_t BUFFER_SIZE = 128;

	/// === Private Declarations	================================================================

	virtual void iwrite(const femtin::Array_ptr<const uint8_t> _buf);

	virtual void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart);
	virtual void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart);

	/// === Private Attributes	====================================================================

	femtin::Array<char, BUFFER_SIZE> buffer_;
	UART_HandleTypeDef UART_handle_;
	femtin::os::Semaphore SEM_UART;
	femtin::os::Mutex MUT_trace;
};
/// === Inlines Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}///mcu
}    /// board
#endif
/// === END OF FILE	================================================================================
