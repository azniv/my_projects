
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ќачальные настройки дл€ LCD
// ƒата крайнего редактировани€ 17.12.2015
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_LCD_INTERACE_H
#define _LCD_INTERACE_H 1

	#include  <avr/io.h>
	#include  <util/delay.h>

	// PIN дл€ передачи  данных или команд
	#define RS_PIN 1
	// PIN дл€ обращени€ к дисплею 
	#define EN_PIN 0

	#define DDR_MNG DDRB
	#define DDR_LCD DDRD

	#define PORT_MNG PORTB
	#define PORT_LCD PORTD
	
	// 0 - 4 провода, 1 - 8 проводов
	#define IS_8_WIRES 0
	
	//////////////////////////////////////////////////////////////
	//команды дл€ инициализации 
	///////////////////////////////////////////////////////////////

	//установка разр€дности интерфейса
	#define CMD_INIT     		  0b00000011
	#define CMD_SET_INTERFACE     0b00110010
	//установка параметров
	#define CMD_SET_PARAMETRS     (0b00101100 | (IS_8_WIRES<<4))
	//выключение диспле€
	#define CMD_DISPLAY_OFF       0b1100
	
	#define CMD_CURSOR_ON         0b1101
	#define CMD_CURSOR_OFF        0b1100
	//ќчищает модуль и помещает
	//курсор в самую левую позицию
	#define CMD_DISPLAY_CLEAR     0b1
	//установка режима ввода данных
	#define CMD_ENTRY_MODE_SET    0b110
	

	void LCD_send_data(uint8_t symbol);
	void LCD_send_cmd(uint8_t cmd);
	void LCD_init(void);
	void LCD_gotoXY(uint8_t col, uint8_t row);
	void LCD_putstring (uint8_t*);

#endif	/* lcd_interface.h */
