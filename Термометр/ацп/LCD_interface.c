

#include "LCD_interface.h"
//////////////////////////////////////////////////////////////
//��������� ��������� � �������
//////////////////////////////////////////////////////////////
 void enable(void) {
	PORT_MNG |= (1<<EN_PIN);
	_delay_us(2);
	PORT_MNG &= ~(1<<EN_PIN);
	_delay_us(40);
}

//////////////////////////////////////////////////////////////
//������������������ ������ ��� ������������� (������)
//////////////////////////////////////////////////////////////
 void LCD_init(void) {

	#if (IS_8_WIRES)
		PORT_LCD = 0;
		DDR_LCD  = 0xFF;
	#else
		PORT_LCD &= 0x0F;
		DDR_LCD  |= 0xF0;
	#endif
 
	DDR_MNG |= (1<<RS_PIN)|(1<<EN_PIN);
	PORT_MNG &= ~(1<<RS_PIN)|(1<<EN_PIN);
	//�� ������
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
	LCD_send_cmd(CMD_ENTRY_MODE_SET);
		
}

//////////////////////////////////////////////////////////////
//������� ����� ������ ��� ������
//�� ���� ������ ������ ��� �������
//////////////////////////////////////////////////////////////
void entering_data_or_command(uint8_t intering) {
	#if (IS_8_WIRES)
		PORT_LCD = intering;
		enable();
	#else
		PORT_LCD &= 0x0F;
		PORT_LCD |= (intering & 0xF0);
		enable();
		PORT_LCD &= 0x0F;
		PORT_LCD |= (intering << 4);
		enable();
	#endif
}

//////////////////////////////////////////////////////////////
//���� ������ 
//////////////////////////////////////////////////////////////
void LCD_send_data(uint8_t symbol) {
	//����� �������� ������, ���������� RS = 1 
	PORT_MNG |= (1<<RS_PIN);
	entering_data_or_command(symbol);
}

//////////////////////////////////////////////////////////////
//���� ������
//////////////////////////////////////////////////////////////
void LCD_send_cmd(uint8_t cmd) {
	//����� �������� �������, ���������� RS = 0 
	PORT_MNG &= ~(1<<RS_PIN);
	entering_data_or_command(cmd);	
}

//////////////////////////////////////////////////////////////
//������� ����������� ������� � �������� �������
//col - ����� ���������� �� �������������� ��� (�� 0 �� 15)
//row - ����� ������ (0 ��� 1) 
//////////////////////////////////////////////////////////////
void LCD_gotoXY(uint8_t col, uint8_t row){
    uint8_t adr;
	
    adr=0x40*row+col;
    adr|=0x80;
    LCD_send_cmd(adr);
}

//////////////////////////////////////////////////////////////
//�������������� ������ � ������ ��� ����� �� ����� 
//////////////////////////////////////////////////////////////
void LCD_putstring (uint8_t* s){
    for (uint8_t i=0; s[i]; i++)
	    LCD_send_data(s[i]);
}	


