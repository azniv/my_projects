#ifndef	_CONFIG_H
#define _CONFIG_H 1    
	
	//кнопка №3
	#define BUTTON_CONF  (~PIND&(1<<2))
	//кнопка №2
	#define BUTTON_DEC	 (~PIND&(1<<1))
	//кнопка №1
	#define BUTTON_INC	 (~PIND&(1<<0))
	
	//динамик
	#define SND_PIN		 (1<<0)	
	//регистр будильника
	#define ALARM_CHECK	 (read_DS(0x0F) & 0b1)	

	//счетчик при изменении времени 
	#define MAX_CONF_MODE  6

	
	// 127 = 1 секунда
	#define COUNTER_FOR_BUTTONS           127

	// Счетчик для автоматического выхода 
	//    из режима редактирования(8 сек)
	#define COUNTER_FOR_AUTOMATIC_OFF     1016
	
	//время для автоматического выключения будильника 16с
	#define COUNTER_FOR_SOUND             1016
#endif	/* config.h */
	