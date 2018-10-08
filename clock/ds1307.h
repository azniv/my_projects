
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Дата создания 17.12.2015
// Дата крайнего редактирования 12.02.2016
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_DS1307_H
#define _DS1307_H 1

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include "struct.h"
	
	
	//регистры часов 
	#define SECONDS_REG        0x00
	#define MINUTES_REG        0x01
	#define HOURS_REG          0x02
	#define DAY_REG            0x03
	#define DATE_REG           0x04
	#define MONTH_REG          0x05
	#define YEAR_REG           0x06
	
	//регистры времени будильника 
	#define ALARM_SECONDS_REG  0x07
	#define ALARM_MINUTES_REG  0x08
	#define ALARM_HOURS_REG    0x09
	#define ALARM_MASK_REG     0xA

	
	//Преобразование данных из двоично-десятичной системы в десятичную 
	#define BCD2DEC(X) (X) = ((((X) & 0xF0) >> 4)*10)+((X) & (0x0F))
	
	//Преобразование данных из десятичной системы в двоично-десятичную
	#define DEC2BCD(X) (X) = (((X)/10)<<4) + ((X)%10)

	//адрес микросхемы DS1307
	#define ADDRESS_DS 0b1101000
	
	//адрес с учетом бита для записи данных 
	#define ADDRESS_W (ADDRESS_DS<<1)
	
	//адрес с учетом бита для чтения
	#define ADDRESS_R ((ADDRESS_DS<<1)|1)
    
	//переход на необходимый регистр
	#define DS_SETADDRESS(x)  TWI_SendPocket(x,ADDRESS_W)
	
	//меняет местами биты 
	#define INTERCHANGE_BYTES(A,B,TEMP) (TEMP)=(A);\
	                                    (A)=(B);\
								        (B)=(TEMP);
	
	//__attribute__((always_inline)) void init_DS(void);

    //описание структуры времени
	void write_DS(uint8_t reg, uint8_t time);
	uint8_t read_DS(uint8_t reg);
	//инициализация часов 
	void init_DS(void);
	void time2str(struct Time* ds, uint8_t* s);
	


#endif	/* ds1307.h */
