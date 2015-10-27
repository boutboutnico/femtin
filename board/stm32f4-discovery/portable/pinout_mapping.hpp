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
/// \file	pinout_mapping.hpp
///	\brief	
///	\date	15/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef HAL_MSP_PINOUT_MAPPING_HPP_
#define HAL_MSP_PINOUT_MAPPING_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "bsp/peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

#ifdef __cplusplus
extern "C"
{
#endif

/// === Public Declarations	========================================================================

///	--- LED	----------------------------------------------------------------------------------------

///	Orange
extern GPIO_TypeDef* LED_ORANGE_GPIO_PORT;    /// GPIOD
const uint16_t LED_ORANGE_PIN = GPIO_PIN_13;

///	Green
extern GPIO_TypeDef* LED_GREEN_GPIO_PORT;    /// GPIOD
const uint16_t LED_GREEN_PIN = GPIO_PIN_12;

///	Red
extern GPIO_TypeDef* LED_RED_GPIO_PORT;    /// GPIOD
const uint16_t LED_RED_PIN = GPIO_PIN_14;

///	Blue
extern GPIO_TypeDef* LED_BLUE_GPIO_PORT;	/// GPIOD
const uint16_t LED_BLUE_PIN = GPIO_PIN_15;

/// --- UART3 - Trace	----------------------------------------------------------------------------

const mcu::Peripherals_e Trace_UART_e = mcu::Peripherals_e::UART_3;
extern USART_TypeDef* Trace_UART;
extern GPIO_TypeDef* Trace_UART_TX_GPIO_PORT;	/// GPIOD
const uint16_t Trace_UART_TX_PIN = GPIO_PIN_8;
const uint8_t Trace_UART_TX_PIN_AF = GPIO_AF7_USART3;

const IRQn_Type Trace_UART_IRQn = USART3_IRQn;
const uint8_t Trace_UART_IRQn_PRIO = 6;
const uint8_t Trace_UART_IRQn_SUBPRIO = 3;

inline void Trace_UART_CLK_ENABLE()
{
	__USART3_CLK_ENABLE();
}

inline void Trace_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
}

/// --- I2C1 - LCD	--------------------------------------------------------------------------------

const mcu::Peripherals_e LCD_I2C_e = mcu::Peripherals_e::I2C_1;
extern const I2C_TypeDef* LCD_I2C;
extern const GPIO_TypeDef* LCD_I2C_GPIO_PORT;
const uint16_t LCD_I2C_SCL_PIN = GPIO_PIN_6;
const uint8_t LCD_I2C_SCL_PIN_AF = GPIO_AF4_I2C1;
const uint16_t LCD_I2C_SDA_PIN = GPIO_PIN_9;
const uint8_t LCD_I2C_SDA_PIN_AF = GPIO_AF4_I2C1;

const IRQn_Type LCD_I2C_EV_IRQn = I2C1_EV_IRQn;
const uint8_t LCD_I2C_EV_IRQn_PRIO = 6;
const uint8_t LCD_I2C_EV_IRQn_SUBPRIO = 1;

const IRQn_Type LCD_I2C_ER_IRQn = I2C1_ER_IRQn;
const uint8_t LCD_I2C_ER_IRQn_PRIO = 6;
const uint8_t LCD_I2C_ER_IRQn_SUBPRIO = 2;

const uint8_t LCD_I2C_Address = 0;

inline void LCD_I2C_CLK_ENABLE()
{
	__HAL_RCC_I2C1_CLK_ENABLE();
}

inline void LCD_I2C_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

/// --- ADC1 - Joystick	----------------------------------------------------------------------------

const mcu::Peripherals_e JOYSTICK_ADC_e = mcu::Peripherals_e::ADC_1;
extern const ADC_TypeDef* JOYSTICK_ADC;    /// ADC1
extern const GPIO_TypeDef* JOYSTICK_ADC_GPIO_PORT;    /// GPIOA
extern const DMA_Stream_TypeDef* JOYSTICK_ADC_DMA;    /// DMA2_Stream4
const uint16_t JOYSTICK_ADC_VERTICAL_PIN = GPIO_PIN_1;
const uint16_t JOYSTICK_ADC_HORIZONTAL_PIN = GPIO_PIN_2;
const uint16_t JOYSTICK_ADC_SELECT_PIN = GPIO_PIN_3;
const uint32_t JOYSTICK_ADC_VERTICAL_CHANNEL = ADC_CHANNEL_1;
const uint32_t JOYSTICK_ADC_HORIZONTAL_CHANNEL = ADC_CHANNEL_2;
const uint32_t JOYSTICK_ADC_DMA_CHANNEL = DMA_CHANNEL_0;

const IRQn_Type JOYSTICK_ADC_DMA_IRQn = DMA2_Stream4_IRQn;
const uint8_t JOYSTICK_ADC_DMA_IRQn_PRIO = 6;
const uint8_t JOYSTICK_ADC_DMA_IRQn_SUBPRIO = 4;

inline void JOYSTICK_ADC_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

inline void JOYSTICK_ADC_CLK_ENABLE()
{
	__HAL_RCC_ADC1_CLK_ENABLE();
}

inline void JOYSTICK_ADC_DMA_CLK_ENABLE()
{
	__HAL_RCC_DMA2_CLK_ENABLE();
}

/// --- SPI2 - SD Card	----------------------------------------------------------------------------

//extern const SPI_TypeDef* SDCARD_SPI;
//extern const GPIO_TypeDef* SDCARD_SPI_GPIO_PORT;
//const uint16_t SDCARD_SPI_CS_PIN = GPIO_PIN_12;
//const uint16_t SDCARD_SPI_CLK_PIN = GPIO_PIN_13;
//const uint16_t SDCARD_SPI_MISO_PIN = GPIO_PIN_14;
//const uint16_t SDCARD_SPI_MOSI_PIN = GPIO_PIN_15;
//const uint8_t SDCARD_SPI_PIN_AF = GPIO_AF5_SPI2;
//
//const IRQn_Type SDCARD_SPI_IRQn = SPI2_IRQn;
//const uint8_t SDCARD_SPI_IRQn_PRIO = 6;
//const uint8_t SDCARD_SPI_IRQn_SUBPRIO = 2;
//
//inline void SDCARD_SPI_CLK_ENABLE()
//{
//	__HAL_RCC_SPI2_CLK_ENABLE();
//}
//
//inline void SDCARD_GPIO_CLK_ENABLE()
//{
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//}
//
//inline void SDCARD_SPI_FORCE_REALEASE_RESET()
//{
//	__HAL_RCC_SPI2_FORCE_RESET();
//	__HAL_RCC_SPI2_RELEASE_RESET();
//}

#ifdef __cplusplus
}
#endif

/// ------------------------------------------------------------------------------------------------
}

#endif	/// HAL_MSP_PINOUT_MAPPING_HPP_
/// === END OF FILE	================================================================================
