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
/// \file	joystick.hpp
/// \brief
/// \date	06/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef DRIVERS_JOYSTICK_THUMB_JOYSTICK_HPP_
#define DRIVERS_JOYSTICK_THUMB_JOYSTICK_HPP_

/// === Includes	================================================================================

#include <cstddef>
#include "stm32f4xx_hal.h"
#include "femtin/array.hpp"
#include "bsp/peripheral_handler.hpp"
#include "portable/pinout_mapping.hpp"

/// === Namespaces	================================================================================

namespace peripheral
{
namespace joystick_thumb
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class Joystick : public board::mcu::PeripheralHandler
{
public:
	/// === Public Constants	====================================================================
	/// === Public Declarations	====================================================================

	Joystick();

	bool initialize();

	uint32_t read_vertical() const;
	uint32_t read_horizontal() const;
	bool is_push() const;

private:
	///	=== Private Constants	====================================================================

	static const size_t DMA_BUFFER_SIZE = 64;

	/// === Private Declarations	================================================================

	virtual void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* _ADC_handle);

	/// === Private Attributes	====================================================================

	ADC_HandleTypeDef ADC_handle_;
	DMA_HandleTypeDef DMA_handle_;
	femtin::Array<uint32_t, DMA_BUFFER_SIZE> DMA_buffer_;

	uint32_t vertical_ = 0;
	uint32_t horizontal_ = 0;
};

/// === Inlines Definitions	========================================================================

inline uint32_t Joystick::read_vertical() const
{
	return vertical_;
}

inline uint32_t Joystick::read_horizontal() const
{
	return horizontal_;
}

inline bool Joystick::is_push() const
{
	return !HAL_GPIO_ReadPin(const_cast<GPIO_TypeDef*>(board::JOYSTICK_ADC_GPIO_PORT),
								board::JOYSTICK_ADC_SELECT_PIN);
}

///	=== Non-Members Definitions	====================================================================

/// ------------------------------------------------------------------------------------------------
}
}

#endif
/// === END OF FILE	================================================================================
