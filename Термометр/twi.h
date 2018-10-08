
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� TWI
// ��� ������� ����������� MLX90614
// ���� �������� �������������� 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_TWI_H
#define _TWI_H 1
	#include  <avr/io.h>
	#include  <util/delay.h>
	volatile uint8_t timer;


	// �������� ������� �����
	void TWI_Start(void);
	// �������� ����
	void TWI_Stop(void);
	//�������� �����
	void TWI_SendByte(uint8_t c);
	//������������� TWI ��� �����������
	void TWI_Init (void);
	//�������� SLA_W + ���� ������
	void TWI_SendPocket (uint8_t value,uint8_t adres_rw);
	//��������� ������� ������ �� TWI
	//������ �����
	uint8_t TWI_RecieveByte(void);
	//������ ���������� �����
	uint8_t TWI_RecieveLastByte(void);

#endif	/* TWI.h */