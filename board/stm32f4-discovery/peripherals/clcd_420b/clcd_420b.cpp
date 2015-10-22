///
/// \file	lcd_i2c_driver.cpp
///	\brief	
///	\date	28/09/2015
/// \author	nboutin
///

#include "clcd_420b.hpp"
using namespace peripheral::lcd;

/// === Includes	================================================================================

#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "portable/pinout_mapping.hpp"
#include "bsp/led/led.hpp"
//#include "trace/trace.hpp"

/// === Namespaces	================================================================================

using namespace femtin;
using namespace femtin::os;
using namespace femtin::unit;
using namespace board;
using namespace board::mcu;

/// === Public Definitions	========================================================================

CLCD_420B::CLCD_420B()
		: PeripheralHandler(LCD_I2C_e, &I2C_handle_), ostream(buffer_), current_row_(0), SEM_I2C(0)
{
}

/// ------------------------------------------------------------------------------------------------

bool CLCD_420B::initialize()
{
	/// --- Clocks

	/// Enable UART interface clock
	LCD_I2C_CLK_ENABLE();

	/// Enable the clocks for UART GPIOs
	LCD_I2C_GPIO_CLK_ENABLE();

	/// --- GPIOs

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	/// SCL
	GPIO_InitStruct.Pin = LCD_I2C_SCL_PIN;
	GPIO_InitStruct.Alternate = LCD_I2C_SCL_PIN_AF;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(LCD_I2C_GPIO_PORT), &GPIO_InitStruct);

	/// SDA
	GPIO_InitStruct.Pin = LCD_I2C_SDA_PIN;
	GPIO_InitStruct.Alternate = LCD_I2C_SDA_PIN_AF;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(LCD_I2C_GPIO_PORT), &GPIO_InitStruct);

	/// --- Interrupt

	/// \warning	Must be lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	///				to be able to call a freeRTOS ISR routine

	/// Event Handler
	/// Configure the I2C interrupt priority
	HAL_NVIC_SetPriority(LCD_I2C_EV_IRQn, LCD_I2C_EV_IRQn_PRIO, LCD_I2C_EV_IRQn_SUBPRIO);

	/// Enable NVIC I2C IRQ handle
	HAL_NVIC_EnableIRQ(LCD_I2C_EV_IRQn);

	/// Error Handler
	/// Configure the I2C interrupt priority
	HAL_NVIC_SetPriority(LCD_I2C_ER_IRQn, LCD_I2C_ER_IRQn_PRIO, LCD_I2C_ER_IRQn_SUBPRIO);

	/// Enable NVIC I2C IRQ handle
	HAL_NVIC_EnableIRQ(LCD_I2C_ER_IRQn);

	/// --- I2C

	I2C_handle_.Instance = const_cast<I2C_TypeDef*>(LCD_I2C);
	I2C_handle_.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_handle_.Init.ClockSpeed = 400000;
	I2C_handle_.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	I2C_handle_.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
	I2C_handle_.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	I2C_handle_.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	I2C_handle_.Init.OwnAddress1 = LCD_I2C_Address;
	I2C_handle_.Init.OwnAddress2 = 0;

	/// User param
	I2C_handle_.user_param = this;

	if (HAL_I2C_Init(&I2C_handle_) != HAL_OK)
	{
		return false;
	}

	return true;
}

///	------------------------------------------------------------------------------------------------
void CLCD_420B::clear()
{
	current_row_ = 0;

	buffer_write_[0] = COMMAND;
	buffer_write_[1] = CLEAR;
	write(buffer_write_, 2);
	task_delay(millisecond(15));
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::backlight(const bool _is_on)
{
	buffer_write_[0] = COMMAND;
	buffer_write_[1] = _is_on ? BACKLIGHT_ON : BACKLIGHT_OFF;
	write(buffer_write_, 2);
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::cursor(const bool _is_on)
{
	buffer_write_[0] = COMMAND;
	buffer_write_[1] = _is_on ? CURSOR_ON : CURSOR_OFF;
	write(buffer_write_, 2);
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::home()
{
	current_row_ = 0;

	buffer_write_[0] = COMMAND;
	buffer_write_[1] = HOME;
	write(buffer_write_, 2);
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::cursor_xy(uint8_t _x, uint8_t _y)
{
	assert(_x < COLUMN_NUMBER);
	assert(_y < ROW_NUMBER);

	current_row_ = _y;

	buffer_write_[0] = COMMAND;
	buffer_write_[1] = CURSOR_POS;
	buffer_write_[2] = _x;
	buffer_write_[3] = _y;
	write(buffer_write_, 4);
	/// TODO : add delay 100us
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::move_to_row(uint8_t _y)
{
	assert(_y < ROW_NUMBER);

	current_row_ = _y;

	buffer_write_[0] = static_cast<char>(_y + 1);
	write(buffer_write_, 1);
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::next_row()
{
	if (++current_row_ >= ROW_NUMBER)
	{
		current_row_ = 0;
	}

	move_to_row(current_row_);
}

///	------------------------------------------------------------------------------------------------

///static const uint8_t custom_8[8] = { 0b00000, 0b11011, 0b10101, 0b10001, 0b01010, 0b00100,
///										0b00000, 0b00000 };
///
///static const uint8_t custom_9[8] = { 0b01110, 0b11111, 0b10001, 0b10001, 0b10001, 0b11111,
///										0b11111, 0b11111 };
///
///lcd_i2c_driver_.store_custom(8, custom_8);
///lcd_i2c_driver_.store_custom(9, custom_9);
///lcd_i2c_driver_.home();
///lcd_i2c_driver_.call_custom(8);
///lcd_i2c_driver_.call_custom(9);

void CLCD_420B::store_custom(uint8_t _code, const uint8_t* _data)
{
	assert(_code >= 8 && _code <= 15);

	static const size_t size = 3 + 8;
	uint8_t buffer[size];

	buffer[0] = COMMAND;
	buffer[1] = CUSTOM_CHAR;
	buffer[2] = _code;
	memcpy(&buffer[3], _data, 8);
	write(buffer, size);
}

/// ------------------------------------------------------------------------------------------------

void CLCD_420B::call_custom(uint8_t _code)
{
	assert(_code >= 8 && _code <= 15);

	buffer_write_[0] = _code;
	write(buffer_write_, 1);
}

/// === Private Definitions	========================================================================

void CLCD_420B::write(const uint8_t* _buf, size_t _size)
{
// HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

	if (HAL_I2C_Master_Transmit_IT(&I2C_handle_, LCD_I2C_Address << 1, const_cast<uint8_t*>(_buf),
									static_cast<uint16_t>(_size))
		!= HAL_OK)
	{
		board::led::LED_Red.on();
//		trace_printf("I2C Error: %d\n", HAL_I2C_GetError(&I2C_handle_));
	}

	if (SEM_I2C.take(femtin::unit::millisecond(200)) == false)
	{
		while (1)
		{
		}
	}
}

///	------------------------------------------------------------------------------------------------

void CLCD_420B::HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *_I2C_handle)
{
	if (_I2C_handle->Instance == LCD_I2C)
	{
		SEM_I2C.giveFromISR();
	}
}

/// ------------------------------------------------------------------------------------------------

void CLCD_420B::HAL_I2C_ErrorCallback(I2C_HandleTypeDef* _I2C_handle)
{
	if (_I2C_handle->Instance == LCD_I2C)
	{
		switch (_I2C_handle->ErrorCode)
		{
		case HAL_I2C_ERROR_NONE:
		case HAL_I2C_ERROR_BERR:
		case HAL_I2C_ERROR_ARLO:
		case HAL_I2C_ERROR_AF:
		case HAL_I2C_ERROR_OVR:
		case HAL_I2C_ERROR_DMA:
		case HAL_I2C_ERROR_TIMEOUT:

			board::led::LED_Red.on();
			while (1)
			{
			}
			break;
		}
	}
}

/// === END OF FILE	================================================================================
