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
/// \file	trace_uart.cpp
/// \brief
/// \date	08/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "trace_uart.hpp"
using namespace board::mcu;

/// === Includes	================================================================================

#include "femtin/scoped_locking.hpp"
#include "portable/pinout_mapping.hpp"
#include "bsp/led/led.hpp"

/// === Static Instantiation	====================================================================

Trace_UART board::mcu::trace;

///	=== Namespaces	================================================================================
/// === Public Definitions	========================================================================

Trace_UART::Trace_UART()
		: PeripheralHandler(Trace_UART_e, &UART_handle_), ostream(buffer_), SEM_UART(0), MUT_trace()
{
	initialize(115200);
}

/// ------------------------------------------------------------------------------------------------
bool Trace_UART::initialize(uint32_t _speed)
{
	/// --- Clocks

	/// Enable UART interface clock
	Trace_UART_CLK_ENABLE();

	/// Enable the clocks for UART GPIOs
	Trace_GPIO_CLK_ENABLE();

	/// --- GPIOs

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = Trace_UART_TX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = Trace_UART_TX_PIN_AF;

	HAL_GPIO_Init(Trace_UART_TX_GPIO_PORT, &GPIO_InitStruct);

	/// --- Interrupt

	/// \warning	Must be lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	///				to be able to call a freeRTOS ISR routine

	/// Configure the UART interrupt priority
	HAL_NVIC_SetPriority(Trace_UART_IRQn, Trace_UART_IRQn_PRIO, Trace_UART_IRQn_SUBPRIO);

	/// Enable NVIC UART IRQ handle
	HAL_NVIC_EnableIRQ(Trace_UART_IRQn);

	/// --- UART

	UART_handle_.Instance = board::Trace_UART;
	UART_handle_.Init.BaudRate = _speed;
	UART_handle_.Init.WordLength = UART_WORDLENGTH_9B;
	UART_handle_.Init.StopBits = UART_STOPBITS_1;
	UART_handle_.Init.Parity = UART_PARITY_EVEN;
	UART_handle_.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_handle_.Init.Mode = UART_MODE_TX;

	/// User param
	UART_handle_.user_param = this;

	if (HAL_UART_Init(&UART_handle_) != HAL_OK)
	{
		return false;
	}

	return true;
}

/// === Private Definitions	========================================================================

void Trace_UART::iwrite(const femtin::Array_ptr<const uint8_t> _buf)
{
	femtin::Guard<femtin::os::Mutex> guard(MUT_trace, femtin::unit::millisecond(200));

	if (HAL_UART_Transmit_IT(&UART_handle_, _buf.data(), _buf.max_size()) != HAL_OK)
	{
		board::led::LED_Red.on();
	}

	if (SEM_UART.take(femtin::unit::millisecond(200)) == false)
	{
		while (1)
		{
		}
	}
}

/// ------------------------------------------------------------------------------------------------

void Trace_UART::HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == board::Trace_UART)
	{
		SEM_UART.giveFromISR();
	}
}

/// ------------------------------------------------------------------------------------------------

void Trace_UART::HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == board::Trace_UART)
	{
		switch (_huart->ErrorCode)
		{
		case HAL_UART_ERROR_PE:
		case HAL_UART_ERROR_NE:
		case HAL_UART_ERROR_FE:
		case HAL_UART_ERROR_ORE:
		case HAL_UART_ERROR_DMA:

			board::led::LED_Red.on();
			while (1)
			{
			}
			break;
		}
	}
}

/// === END OF FILE	================================================================================
