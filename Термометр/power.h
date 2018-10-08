
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Настройка питания отдельных модулей 
// Для датчика температуры MLX90614
// Дата крайнего редактирования 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _POWER_H
#define _POWER_H_1
	
	#include <avr/io.h>
	#include "common.h"
	
	#define POWER_PORTNAME D

	//номера выводов 
	//питание дисплея 
	#define POWER_LCD_PIN     7
	//питание датчика
	#define POWER_SENSOR_PIN  1
	//питание делителя напряжения
	#define POWER_DIV_PIN     0
	//питание для шим
	#define POWER_PWM_PIN     6
	
	
	#define POWER_DDR           CONCAT(DDR,  POWER_PORTNAME)
	#define POWER_PORT          CONCAT(PORT, POWER_PORTNAME)
	#define POWER_PIN           CONCAT(PIN,  POWER_PORTNAME)

	// Настройка направления ввода-вывода порта питания
	#define POWER_INIT()	    (POWER_DDR = (1<<POWER_LCD_PIN) | (1<<POWER_SENSOR_PIN) | (1<<POWER_DIV_PIN) | (1<< POWER_PWM_PIN) )
// Макросы для включенияи выключения отдельных потребителей
	#define POWER_ON_PIN(X)     (POWER_PORT|= (1<<(X)))
	#define POWER_OFF_PIN(X)    (POWER_PORT &= ~(1<<(X)))
	//включение питания  дисплея и датчика
	#define POWER_ON()      	(POWER_PORT = (1<<POWER_SENSOR_PIN) |(1<<POWER_LCD_PIN) )
	//выключение питания 
	#define POWER_OFF()      	(POWER_PORT = 0)
	
	// режим Power-down
	#define SLEEP_MODE()        (SMCR  = (1<<SM1)|(1<<SE))
	
	
	 // Прерывание по переполнению T0   
	#define INTERRUPT_INIT()		{										\
										PCICR  = (1<<PCIF1);				\
										PCMSK1 = (1<<PCINT8)|(1<<PCINT10);  \
										TIMSK0 = (1<<0);           			\
									}
	
	
	//режим сна
	#define SLEEP_AND_POWER_OFF() 	{										\
										POWER_OFF();						\
										(PORTB  = 0);						\
										asm volatile ("nop");    			\
										asm volatile ("nop");  				\
										asm volatile ("sleep"); 	   	    \
									}


/*(ADCSRA = 0);						
(TCCR0A = 0);(TCCR0B = 0);
						*/
#endif /*power.h*/