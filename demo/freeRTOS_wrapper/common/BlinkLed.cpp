//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "BlinkLed.h"

BlinkLed LED_Green(3, 12);
BlinkLed LED_Orange(3, 13);
BlinkLed LED_Red(3, 14);
BlinkLed LED_Blue(3, 15);

BlinkLed::BlinkLed(port_type _port, pin_type _pin)
		: pin_(_pin), port_(_port)
{
	powerUp();
}

// ----------------------------------------------------------------------------

void BlinkLed::powerUp()
{
	// Enable GPIO Peripheral clock
	RCC->AHB1ENR |= BLINK_RCC_MASKx(port_);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = BLINK_PIN_MASK(pin_);
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(BLINK_GPIOx(port_), &GPIO_InitStructure);

	// Start with led turned off
	turnOff();
}

// ----------------------------------------------------------------------------
