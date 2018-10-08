
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��������� ��� LCD
// ���� �������� �������������� 25.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_LCD_INTERACE_H
#define _LCD_INTERACE_H 1

	#include  <avr/io.h>
	#include  <util/delay.h>
#include  "power.h"

	// PIN ��� ��������  ������ ��� ������
	#define RS_PIN 4
	// PIN ��� ��������� � ������� 
	#define EN_PIN 5

//	#define DDR_MNG DDRB
	//#define DDR_LCD DDRB

	//#define PORT_MNG PORTB
	//#define PORT_LCD PORTB
	
	// ����� ����� � ��������
	#define LCD_DATA_PORTNAME    B
	#define LCD_CONTROL_PORTNAME B
	
	// 0 - 4 �������, 1 - 8 ��������
	#define IS_8_WIRES 0
	
	//////////////////////////////////////////////////////////////
	//������� ��� ������������� 
	///////////////////////////////////////////////////////////////

	//��������� ����������� ����������
	#define CMD_INIT     		  (0b00000011 | (IS_8_WIRES<<4) |(IS_8_WIRES<<5))
	#define CMD_SET_INTERFACE     0b00000010
	//��������� ����������
	#define CMD_SET_PARAMETRS     (0b00101100 | (IS_8_WIRES<<4))
	//���������� �������
	#define CMD_DISPLAY_ON        0b1100
	#define CMD_DISPLAY_OFF       0b1000
	#define CMD_CURSOR_ON         0b1101
	#define CMD_CURSOR_OFF        0b1100
	//������� ������ � ��������
	//������ � ����� ����� �������
	#define CMD_DISPLAY_CLEAR     0b0001
	//��������� ������ ����� ������
	#define CMD_ENTRY_MODE_SET    0b0110
	
		
		
	///////////////////////////////////////////////////////////////////////////////
	// �������
	////////////////////////////////////////////////////////////////////////////////

	// ������� ��� ����������� DDRx, PORTx, PINx
	#define DDR_LCD_DATA       CONCAT(DDR,  LCD_DATA_PORTNAME)
	#define PORT_LCD_DATA      CONCAT(PORT, LCD_DATA_PORTNAME)
	#define PIN_LCD_DATA       CONCAT(PIN,  LCD_DATA_PORTNAME)
	#define DDR_LCD_CONTROL    CONCAT(DDR,  LCD_CONTROL_PORTNAME)
	#define PORT_LCD_CONTROL   CONCAT(PORT, LCD_CONTROL_PORTNAME)
	#define PIN_LCD_CONTROL    CONCAT(PIN,  LCD_CONTROL_PORTNAME)

	// ��������� ������� � ��������� �����
	// row (������) = 0 ��� 1, col (�������) = �� 0 �� 7
	#define LCD_SETCURSOR(ROW, COL) LCD_SENDCOMMAND(0b10000000 | ((ROW)<<6) | (COL))

	// �������� ������� (��������� RS � 0, ��������� ��� �������, � �� ������, � ����� ToLCD)
	#define LCD_SENDCOMMAND(CMD){                                         				    \
									PORT_LCD_CONTROL &= ~(1<<LCD_RS_PIN);                   \
									ToLCD(CMD);                                             \
								}

	#define LCD_INIT() 			do{                                                         \
									DDR_LCD_CONTROL = 0b111111; 							\
									for (uint8_t i = 0; i<sizeof(FOR_INIT); i++) {          \
										_delay_ms(17);                                      \
										LCD_send_cmd(pgm_read_byte(&(FOR_INIT[i])));	 	\
									}                                                       \
								} while(0)


		

	/////////////////////////////////////////////////////////////
	//������� ����������� ������� � �������� �������
	//X - ����� ���������� �� �������������� ��� (�� 0 �� 7)
	//Y - ����� ������ (0 ��� 1) 
	//////////////////////////////////////////////////////////////
	#define LCD_SET_POSITION(ROW, COL) do{													\
										 LCD_send_cmd(0b10000000 | ((COL)<<6) | (ROW));     \
									} while(0)                                              \
								



	void LCD_send_data(uint8_t symbol);
	void LCD_send_cmd(uint8_t cmd);
	void LCD_putstring (uint8_t*);

#endif	/* lcd_interface.h */
