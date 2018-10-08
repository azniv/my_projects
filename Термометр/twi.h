
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Настройка TWI
// Для датчика температуры MLX90614
// Дата крайнего редактирования 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_TWI_H
#define _TWI_H 1
	#include  <avr/io.h>
	#include  <util/delay.h>
	volatile uint8_t timer;


	// отправка команды СТАРТ
	void TWI_Start(void);
	// отправка СТОП
	void TWI_Stop(void);
	//отправка байта
	void TWI_SendByte(uint8_t c);
	//инициализация TWI как передатчика
	void TWI_Init (void);
	//отправка SLA_W + байт данных
	void TWI_SendPocket (uint8_t value,uint8_t adres_rw);
	//добавляем функции чтения по TWI
	//чтение байта
	uint8_t TWI_RecieveByte(void);
	//чтение последнего байта
	uint8_t TWI_RecieveLastByte(void);

#endif	/* TWI.h */