
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� TWI
// ��� ������� ����������� MLX90614
// ���� �������� �������������� 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "twi.h"

// �������� ������� �����
void TWI_Start(void){
	timer = ~0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ( timer && !(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
}

// �������� ����
void TWI_Stop(void){
	//TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	//while((TWCR & (1<<TWINT)));
	 TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWSTO);
    // wait until stop condition is executed and bus released
    while(  timer &&(TWCR & _BV(TWSTO)));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//�������� �����
void TWI_SendByte(uint8_t c){
	TWDR = c;//�������� �������� � ������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//������ �������� ����� ������
	while (timer && !(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
}

//������������� TWI ��� �����������
void TWI_Init (void){
	TWBR=32;         //�������� ��������
	//_delay_ms(7); 	 //�������� ���������� ��� �������������

}

//�������� SLA_W + ���� ������
void TWI_SendPocket (uint8_t value,uint8_t adres_rw){
	TWI_Start(); // ���������� ������� �����
	TWI_SendByte(adres_rw); //��������� ����� ����������+��� ������
	TWI_SendByte(value);//���������� ���� ������
	TWI_Stop();//���������� ������� ����
}

//��������� ������� ������ �� TWI
//������ �����
uint8_t TWI_RecieveByte(void){
	uint8_t dat;//���������� �������� ��������
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (timer && !(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	dat = TWDR;//������ ������� ������
	return dat;
}

//������ ���������� �����
uint8_t TWI_RecieveLastByte(void){
	uint8_t dat;//���������� �������� ��������	
	TWCR = (1<<TWINT)|(1<<TWEN);//������ ���������� �����
	while ( timer && !(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	dat = TWDR;//������ ������� ������	
	return dat;
}	


