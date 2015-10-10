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
/// \file	joystick.cpp
///	\brief	
///	\date	06/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "joystick.hpp"
using namespace peripheral::joystick_thumb;

/// === Includes	================================================================================

#include "portable/pinout_mapping.hpp"
#include "bsp/led/led.hpp"

/// === Namespaces	================================================================================

using namespace board;
using namespace board::led;
using namespace board::mcu;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

Joystick::Joystick()
		: PeripheralHandler(board::JOYSTICK_ADC_e, &ADC_handle_)
{
}

/// ------------------------------------------------------------------------------------------------

bool Joystick::initialize()
{
	/// --- Clocks

	/// Enable ADC interface clock
	JOYSTICK_ADC_CLK_ENABLE();

	/// Enable the clocks for ADC GPIOs
	JOYSTICK_ADC_GPIO_CLK_ENABLE();

	/// --- GPIOs

	/// Vertical
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = JOYSTICK_ADC_VERTICAL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(JOYSTICK_ADC_GPIO_PORT), &GPIO_InitStruct);

	/// Horizontal
	GPIO_InitStruct.Pin = JOYSTICK_ADC_HORIZONTAL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(JOYSTICK_ADC_GPIO_PORT), &GPIO_InitStruct);

	/// Select
	GPIO_InitStruct.Pin = JOYSTICK_ADC_SELECT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(JOYSTICK_ADC_GPIO_PORT), &GPIO_InitStruct);

	///	--- ADC

	ADC_handle_.Instance = const_cast<ADC_TypeDef*>(JOYSTICK_ADC);

	ADC_handle_.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	ADC_handle_.Init.Resolution = ADC_RESOLUTION10b;
	ADC_handle_.Init.ScanConvMode = ENABLE;
	ADC_handle_.Init.ContinuousConvMode = ENABLE;
	ADC_handle_.Init.DiscontinuousConvMode = DISABLE;
	ADC_handle_.Init.NbrOfDiscConversion = 0;
	ADC_handle_.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC_handle_.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	ADC_handle_.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC_handle_.Init.NbrOfConversion = 2;
	ADC_handle_.Init.DMAContinuousRequests = ENABLE;
	ADC_handle_.Init.EOCSelection = DISABLE;

	/// User param
	ADC_handle_.user_param = this;

	if (HAL_ADC_Init(&ADC_handle_) != HAL_OK)
	{
		LED_Red.on();
		return false;
	}

	///	--- ADC Channel

	/// Vertical
	ADC_ChannelConfTypeDef ADC_channel_conf;
	ADC_channel_conf.Channel = JOYSTICK_ADC_VERTICAL_CHANNEL;
	ADC_channel_conf.Rank = 1;
	ADC_channel_conf.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC_channel_conf.Offset = 0;

	if (HAL_ADC_ConfigChannel(&ADC_handle_, &ADC_channel_conf) != HAL_OK)
	{
		LED_Red.on();
		return false;
	}

	/// Horizontal
	ADC_channel_conf.Channel = JOYSTICK_ADC_HORIZONTAL_CHANNEL;
	ADC_channel_conf.Rank = 2;
	ADC_channel_conf.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC_channel_conf.Offset = 0;

	if (HAL_ADC_ConfigChannel(&ADC_handle_, &ADC_channel_conf) != HAL_OK)
	{
		LED_Red.on();
		return false;
	}

	/// --- ADC DMA

	/// Clock
	JOYSTICK_ADC_DMA_CLK_ENABLE();

	DMA_handle_.Instance = const_cast<DMA_Stream_TypeDef*>(JOYSTICK_ADC_DMA);
	DMA_handle_.Init.Channel = JOYSTICK_ADC_DMA_CHANNEL;
	DMA_handle_.Init.Direction = DMA_PERIPH_TO_MEMORY;
	DMA_handle_.Init.PeriphInc = DMA_PINC_DISABLE;
	DMA_handle_.Init.MemInc = DMA_MINC_ENABLE;
	DMA_handle_.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	DMA_handle_.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	DMA_handle_.Init.Mode = DMA_CIRCULAR;
	DMA_handle_.Init.Priority = DMA_PRIORITY_HIGH;
	DMA_handle_.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	DMA_handle_.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
	DMA_handle_.Init.MemBurst = DMA_MBURST_SINGLE;
	DMA_handle_.Init.PeriphBurst = DMA_PBURST_SINGLE;

	HAL_DMA_Init(&DMA_handle_);

	__HAL_LINKDMA(&ADC_handle_, DMA_Handle, DMA_handle_);

	///	--- Interrupt

	HAL_NVIC_SetPriority(JOYSTICK_ADC_DMA_IRQn, JOYSTICK_ADC_DMA_IRQn_PRIO,
							JOYSTICK_ADC_DMA_IRQn_SUBPRIO);
	HAL_NVIC_EnableIRQ(JOYSTICK_ADC_DMA_IRQn);

	///	--- Start

	if (HAL_ADC_Start_DMA(&ADC_handle_, DMA_buffer_.data(), DMA_BUFFER_SIZE) != HAL_OK)
	{
		LED_Red.on();
		return 0;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================

void Joystick::HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* _ADC_handle)
{
	if (_ADC_handle->Instance == JOYSTICK_ADC)
	{
		LED_Blue.toggle();
		vertical_ = DMA_buffer_[0];
		horizontal_ = DMA_buffer_[1];
	}
}

/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
