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
/// \file	pinout_mapping.cpp
/// \brief
/// \date	16/04/2015
/// \author	nboutin
///
/// ================================================================================================
#include "pinout_mapping.hpp"

namespace board
{

///	--- LED	----------------------------------------------------------------------------------------

///	Orange
GPIO_TypeDef* LED_ORANGE_GPIO_PORT = GPIOD;

///	Green
GPIO_TypeDef* LED_GREEN_GPIO_PORT = GPIOD;

///	Red
GPIO_TypeDef* LED_RED_GPIO_PORT = GPIOD;

///	Blue
GPIO_TypeDef* LED_BLUE_GPIO_PORT = GPIOD;

/// --- UART3 - Trace	----------------------------------------------------------------------------

//USART_TypeDef* Trace_UART = USART3;
GPIO_TypeDef* Trace_UART_TX_GPIO_PORT = GPIOD;

/// --- I2C1 - LCD	--------------------------------------------------------------------------------

const I2C_TypeDef* LCD_I2C = I2C1;
const GPIO_TypeDef* LCD_I2C_GPIO_PORT = GPIOB;

/// --- ADC1 - Joystick	----------------------------------------------------------------------------

const ADC_TypeDef* JOYSTICK_ADC = ADC1;
const GPIO_TypeDef* JOYSTICK_ADC_GPIO_PORT = GPIOA;
const DMA_Stream_TypeDef* JOYSTICK_ADC_DMA = DMA2_Stream4;

/// --- SPI2 - SD Card	----------------------------------------------------------------------------

//const SPI_TypeDef* SDCARD_SPI = SPI2;
//const GPIO_TypeDef* SDCARD_SPI_GPIO_PORT = GPIOB;
}

/// === END OF FILE	================================================================================
