///
/// \file	lcd_i2c_driver.hpp
///	\brief	
///	\date	28/09/2015
/// \author	nboutin
///
#ifndef BOARD_DRIVERS_CLCD_420B_HPP_
#define BOARD_DRIVERS_CLCD_420B_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "femtin/ostream.hpp"
#include "femtin/freeRTOS_wrapper/semaphore/semaphore.hpp"
#include "bsp/peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace peripheral
{

namespace lcd
{

/// === Class Declarations	========================================================================

class CLCD_420B : public board::mcu::PeripheralHandler, public femtin::ostream
{
public:
	/// === Public Constants	====================================================================

	static const uint8_t COLUMN_NUMBER = 20;
	static const uint8_t ROW_NUMBER = 4;

	/// === Public Declarations	====================================================================

	CLCD_420B();
	virtual ~CLCD_420B();    /// TODO useless ?

	bool initialize();

	///	--- Operations	----------------------------------------------------------------------------

	void clear();
	void backlight(bool _is_on);
	void cursor(bool _is_on);
	void home();
	void cursor_xy(uint8_t _x, uint8_t _y);
	void move_to_row(uint8_t _y);
	void next_row();
	void store_custom(uint8_t _code, const uint8_t* _data);
	void call_custom(uint8_t _code);

//	CLCD_420B& operator<<(CLCD_420B& (*_pf)(CLCD_420B&))
//	{
//		return _pf(*this);
//	}

//	CLCD_420B& operator<<(femtin::ostream& (*_pf)(femtin::ostream&))
//	{
//		_pf(*this);
//		return *this;
//	}

	virtual ostream& endl();

private:
	/// === Private Constants	====================================================================

	static const uint8_t BUFFER_SIZE = 4;

	static const uint8_t ROW_0 = 0x01;
	static const uint8_t ROW_1 = 0x02;
	static const uint8_t ROW_2 = 0x03;
	static const uint8_t ROW_3 = 0x04;
	static const uint8_t COMMAND = 0x1B;
	static const uint8_t CLEAR = 0x43;
	static const uint8_t BACKLIGHT_ON = 0x42;
	static const uint8_t CUSTOM_CHAR = 0x44;
	static const uint8_t HOME = 0x48;
	static const uint8_t CURSOR_POS = 0x4C;
	static const uint8_t CURSOR_ON = 0x53;
	static const uint8_t BACKLIGHT_OFF = 0x62;
	static const uint8_t CURSOR_OFF = 0x73;

	/// === Private Declarations	================================================================

	virtual void write(const uint8_t* _buf, size_t _size);

	virtual void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *_I2C_handle);
	virtual void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* _I2C_handle);

	/// === Private Attributes	====================================================================

	uint8_t buffer_write_[BUFFER_SIZE];
	femtin::Array<char, COLUMN_NUMBER * ROW_NUMBER> buffer_;
	uint8_t current_row_;
	I2C_HandleTypeDef I2C_handle_;
	femtin::os::Semaphore SEM_I2C;
};
/// === Inlines Definitions	========================================================================

inline femtin::ostream& CLCD_420B::endl()
{
	next_row();
	return *this;
}

/// === Non-Members functions	====================================================================

//inline femtin::ostream& endl(CLCD_420B& _stream)
//{
//	_stream.next_row();
//	return _stream;
//}

/// ------------------------------------------------------------------------------------------------

struct _set_xy
{
	uint8_t x_;
	uint8_t y_;
};

inline _set_xy xy(uint8_t _x, uint8_t _y)
{
	return
	{	_x, _y};
}

inline CLCD_420B& operator<<(CLCD_420B& _stream, _set_xy _xy)
{
	_stream.cursor_xy(_xy.x_, _xy.y_);
	return _stream;
}

/// ------------------------------------------------------------------------------------------------

struct _set_row
{
	uint8_t y_;
};

inline _set_row row(uint8_t _y)
{
	return
	{	_y};
}

inline CLCD_420B& operator<<(CLCD_420B& _stream, _set_row _y)
{
	_stream.move_to_row(_y.y_);
	return _stream;
}

/// ------------------------------------------------------------------------------------------------
}///mcu
}    /// board
#endif
/// === END OF FILE	================================================================================
