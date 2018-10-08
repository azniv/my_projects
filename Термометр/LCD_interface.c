//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��������� ��� LCD
// ���� �������� �������������� 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "LCD_interface.h"
#include <avr/pgmspace.h>

//////////////////////////////////////////////////////////////
//��������� ��������� � �������
//////////////////////////////////////////////////////////////
 void enable(void) {
	PORT_LCD_CONTROL |= (1<<EN_PIN);
	_delay_us(2);
	PORT_LCD_CONTROL &= ~(1<<EN_PIN);
	_delay_us(40);
}

//////////////////////////////////////////////////////////////
//������� ����� ������ ��� ������
//�� ���� ������ ������ ��� �������
//////////////////////////////////////////////////////////////
void entering_data_or_command(uint8_t intering) {
	#if (IS_8_WIRES)
		PORT_LCD_DATA = intering;
		enable();
	#else
		PORT_LCD_DATA &= 0xF0;
		PORT_LCD_DATA |= (intering >> 4);
		enable();
		PORT_LCD_DATA &= 0xF0;
		PORT_LCD_DATA |= (intering & 0x0F);
		enable();
			
	#endif
}



//////////////////////////////////////////////////////////////
//���� ������ 
//////////////////////////////////////////////////////////////
void LCD_send_data(uint8_t symbol) {
	//����� �������� ������, ���������� RS = 1 
	PORT_LCD_CONTROL |= (1<<RS_PIN);
	entering_data_or_command(symbol);
}

//////////////////////////////////////////////////////////////
//���� ������
//////////////////////////////////////////////////////////////
void LCD_send_cmd(uint8_t cmd) {
	//����� �������� �������, ���������� RS = 0 
	PORT_LCD_CONTROL &= ~(1<<RS_PIN);
	entering_data_or_command(cmd);	
}



//////////////////////////////////////////////////////////////
//�������������� ������ � ������ ��� ����� �� ����� 
//////////////////////////////////////////////////////////////
void LCD_putstring (uint8_t* s){
    for (uint8_t i=0; s[i]; i++)
	    LCD_send_data(s[i]);
}	


/*
    _delay_ms(15);
    LCD_send_cmd(CMD_INIT);
    _delay_ms(4);
    LCD_send_cmd(CMD_INIT);
    _delay_us(100);
	LCD_send_cmd(0b00000011);
	LCD_send_cmd(0b00000010);
    //LCD_send_cmd(CMD_SET_INTERFACE);
	LCD_send_cmd(CMD_SET_PARAMETRS);
	LCD_send_cmd(CMD_DISPLAY_OFF);
	LCD_send_cmd(CMD_DISPLAY_CLEAR);
	_delay_ms(5);
	LCD_send_cmd(CMD_ENTRY_MODE_SET);*/