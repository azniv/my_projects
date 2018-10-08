
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Настройка кнопок
// Для датчика температуры MLX90614
// Дата крайнего редактирования 19.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BUTTONS_H
#define _BUTTONS_H_1
	
	#include <avr/io.h>
	#include "common.h"
	
	#define BUTTONS_PORTNAME C
	
	// Номера выводов в порте для кнопок
	// левая
	#define BUTTON1 0
	// правая
	#define BUTTON2 2
		
	
	#define BUTTONS_DDR           CONCAT(DDR,  BUTTONS_PORTNAME)
	#define BUTTONS_PORT          CONCAT(PORT, BUTTONS_PORTNAME)
	#define BUTTONS_PIN           CONCAT(PIN,  BUTTONS_PORTNAME)
	
	
	
    //кнопка нажата 
	#define BUTTON_PRESSED(x)   (~BUTTONS_PIN&(1<<(x)))
	//кнопка №
	#define BUTTON_RELEASED(X)  (BUTTONS_PIN&(1<<(x)))
	
	// Инициализация кнопок: подтяжка к питанию внутренними резисторами
	#define BUTTONS_INIT() (BUTTONS_PORT = (1<<BUTTON1)|(1<<BUTTON2))   			


#endif /*buttons.h*/