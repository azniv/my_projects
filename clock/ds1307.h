
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// ���� �������� 17.12.2015
// ���� �������� �������������� 12.02.2016
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_DS1307_H
#define _DS1307_H 1

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include "struct.h"
	
	
	//�������� ����� 
	#define SECONDS_REG        0x00
	#define MINUTES_REG        0x01
	#define HOURS_REG          0x02
	#define DAY_REG            0x03
	#define DATE_REG           0x04
	#define MONTH_REG          0x05
	#define YEAR_REG           0x06
	
	//�������� ������� ���������� 
	#define ALARM_SECONDS_REG  0x07
	#define ALARM_MINUTES_REG  0x08
	#define ALARM_HOURS_REG    0x09
	#define ALARM_MASK_REG     0xA

	
	//�������������� ������ �� �������-���������� ������� � ���������� 
	#define BCD2DEC(X) (X) = ((((X) & 0xF0) >> 4)*10)+((X) & (0x0F))
	
	//�������������� ������ �� ���������� ������� � �������-����������
	#define DEC2BCD(X) (X) = (((X)/10)<<4) + ((X)%10)

	//����� ���������� DS1307
	#define ADDRESS_DS 0b1101000
	
	//����� � ������ ���� ��� ������ ������ 
	#define ADDRESS_W (ADDRESS_DS<<1)
	
	//����� � ������ ���� ��� ������
	#define ADDRESS_R ((ADDRESS_DS<<1)|1)
    
	//������� �� ����������� �������
	#define DS_SETADDRESS(x)  TWI_SendPocket(x,ADDRESS_W)
	
	//������ ������� ���� 
	#define INTERCHANGE_BYTES(A,B,TEMP) (TEMP)=(A);\
	                                    (A)=(B);\
								        (B)=(TEMP);
	
	//__attribute__((always_inline)) void init_DS(void);

    //�������� ��������� �������
	void write_DS(uint8_t reg, uint8_t time);
	uint8_t read_DS(uint8_t reg);
	//������������� ����� 
	void init_DS(void);
	void time2str(struct Time* ds, uint8_t* s);
	


#endif	/* ds1307.h */
