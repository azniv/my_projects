//////////////////////////////////////////////////////////////////////////////////////////////
// 						ЧАСЫ-БУДИЛЬНИК                                                      //
// 						MCU ATMEGA48PA														//
// 						F_CPU 8 MHz															//
// Вход в режим редактирования:    Держать кнопу BUTTON_CONF более 2 с.			    		//
// Выход из режима редактирования: Держать кнопу BUTTON_CONF более 2 с.				    	//
//							   или автоматически через 8 c. без действий.					//	
// в режим редактирования отображается меню вида:                                           //
//                                 1)Time													//
//								   2)Alarm													//
// Перемещение курсора в нужную позицию: 			Короткое нажатие BUTTON_DEC				//
// Выбор того или иного режима:                     Короткое нажатие BUTTON_CONF			//
// Установка позиции курсора для изменения значений:Короткое нажатие BUTTON_CONF			//
// Изменение самих значений: 						Короткое нажатие BUTTON_INC				//
// Отключение будильника: 							Короткое нажатие BUTTON_DEC				// 
//											или  	Автоматически 	через 16 с. 			//							 		
// 				Дата крайнего редактирования: 26.07.2016									//
// 				Автор: Смбатян А.А.															//
//////////////////////////////////////////////////////////////////////////////////////////////

// В КОММЕНТАРИЯХ T0 дописать время


#include <avr/EEPROM.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "config.h"
#include "struct.h"
#include "ds1307.h"
#include "LCD_interface.h"



//#define SetCursor() LCD_gotoXY(pgm_read_byte(&X[conf_mode]), conf_mode>3)

//объект структуры для считывания времения с устройства 
volatile struct Time current_ds_Time;
volatile struct Time alarm_ds_Time;

//максимальные значения, которые достигаются при увеличении времени 
const  uint8_t   max_value[]  = {0, 0x23, 0x59, 0, 0x31, 0x12, 0x40};

//минимальные  значения, которые достигаются при уменьшении времени 
const  uint8_t   min_value[]  = {0,    0, 0x01, 0, 0x01, 0x01, 0x16};
//хранение времени и даты 
uint8_t buf_time[]       = {'0','0',':','0','0',':','0','0',0,'0','0',0,
                            '0','0','/','0','0','/','0','0',0};			  				  
//хранение времени и даты будильника  				  
uint8_t buf_alarm[]      = {'0','0',':','0','0',':','0','0',0,'0','0',0,
                            '0','0','/','0','0','/','0','0',0};
//Меню
uint8_t buf_menu[]       = {'1',')','T','i','m','e',' ',' ',0,'0','0',0,
                            '2',')','A','l','a','r','m',' ',0};				  
				  				  

//флаг для отслеживания новой минуты 		  
volatile uint8_t  update_flag           = 1;
//флаг для отслеживания новой минуты 		  
volatile uint8_t  update_alarm_flag     = 0;

//для звука будильника 
volatile uint8_t  sound_of_alarm        = 0;

//режим изменения времени
volatile uint8_t  conf_mode             = 0;
//меню
volatile uint8_t  clock_ticking         = 0;
volatile uint8_t  menu_conf_mode        = 0;
//Для подсчета вреиени нажатия кнопки 
volatile uint8_t  button_PIN2_counter   = 0;
volatile uint8_t  button_PIN1_counter   = 0;
//время  для автоматического выхода из режима редактирования
volatile uint16_t confmode_off          = 0;
// хранит время для автоматического выключения будильника 16с
volatile uint16_t timeout_alarm         = 0;



//uint8_t conf[] = {0, &current_ds_time.hours, &current_ds_time.minutes, &current_ds_time.seconds,
//					&current_ds_time.date, &current_ds_time.mounth, &current_ds_time.year};
					
//uint8_t reg[]  = {0, HOURS_REG, MINUTES_REG, SECONDS_REG,  DATE_REG, MONTH_REG, YEAR_REG};

//старший разряд числа секунд
volatile uint8_t seconds_hi = '0';
//младщий разряд числа секунд
volatile uint8_t seconds_lo = '0';
//перемещение курсора вверх/вниз в меню                                      
volatile uint8_t menu_item = 0;

//срабатывание будильника 
inline static void AlarmOn(void);
//выключение будильника 
void AlarmOff(void);
//проверка установки будильника 
void AlarmCheck(void);
//отображение врмени
void DisplayTime(void);
//отображение времени при установке будильника 
void DisplayAlarmTime(void);
//вывод меню 
void DisplayMenu(void);
// Перемщение курсора при изменении времени
void SetCursor(void);
//увеличение времени
void SetTime(void);
void Set(struct Time* ds,  uint8_t t);
//установка будильника
void SetAlarmTime(void);


///////////////////////////////////////////////////
// Обработчик прерываний по T0: время срабатывания = 1с
///////////////////////////////////////////////////
ISR(TIMER0_OVF_vect) {
	//будильник не сработает в режиме редактирования 
	if (!clock_ticking){
		//будильник звенит до тех пор, пока 
		//не нажата кнопка и не истекло время ожидания
		if (sound_of_alarm && timeout_alarm){
			AlarmOn();
		}
		else {
			write_DS(0x0F, 0); 
			PORTC &= ~SND_PIN;
		}		
	}
	
	
	//выход из режима редактирования по истечении 8сек без действий 
	if (confmode_off) {	
		confmode_off--;
		if(!confmode_off) {
			clock_ticking = 0;	
			if (!clock_ticking){
				DisplayTime();
				LCD_send_cmd(CMD_CURSOR_OFF);
			}
		}
	}
	
	//режим редактирования
    if (button_PIN2_counter) {
	    button_PIN2_counter--;
        if(!button_PIN2_counter && BUTTON_CONF) {
			clock_ticking = 1;		// нужно, чтобы 
									//остановить тики во время редактирования
			menu_conf_mode ^= 1;	// = 1 режим редактирования 
			if (menu_conf_mode){
				DisplayMenu();		//вывод меню 	
				LCD_send_cmd(CMD_CURSOR_ON);
				LCD_gotoXY(0,0);
			}
			//при выходе из режима редактирования сбрасываем все переменные 
			else {
				DisplayTime();
				LCD_send_cmd(CMD_CURSOR_OFF);
				clock_ticking = 0;
				menu_item=0;
				conf_mode = 0;
			}	
		}
	}
	
	
}

///////////////////////////////////////////////////
// Увеличивание секунд 
// Импульсы приходят о выводы INT/SQW
///////////////////////////////////////////////////
ISR(INT1_vect){
	//не увеличиваем секунды при индикации, 
	//если включен режим установки для будильника 
	if (!clock_ticking){
    // инкрементирование секунд 
		seconds_lo++;
		// инкерментирование секунд по BCD правилам 
		if (seconds_lo > '9') {
		    seconds_lo = '0';
			seconds_hi++;
		    if (seconds_hi  > '5') {
			    seconds_lo  = '0';
			    seconds_hi  = '0';					
				update_flag = 1;	
				
			}
		}
		//SetCursor();
		//перевод курсора на позицию секунд
		//каждую секунду переписывем только новое значение секуны   
		LCD_gotoXY(6,0);
		LCD_send_data(seconds_hi);
		LCD_send_data(seconds_lo);
	}
			
			
}

///////////////////////////////////////////////////
// Изменение времени 
/////////////////////////////////////////////////// 
ISR(PCINT2_vect) {
	//при любой нажатии отсчитываем время 8сек 
	confmode_off  = COUNTER_FOR_AUTOMATIC_OFF;  	
						
	//режим изменения времени и перемещение позиции курсора 
	if  (!button_PIN2_counter &&  BUTTON_CONF)
		button_PIN2_counter = COUNTER_FOR_BUTTONS;				
		
	if (sound_of_alarm && timeout_alarm && BUTTON_DEC)
		AlarmOff();
	
	if (menu_conf_mode) {		//если режим редактирования
		//
		if (BUTTON_DEC) {		//перемещение позиции курсора :вверх, вниз.
			menu_item ^= 1;			// !а - позиция 1)Time
								//  menu_item - позиция 2)Alarm
			LCD_gotoXY(0, menu_item);
			conf_mode = 0;
		}
		
		if (BUTTON_CONF){		//короткое нажатие конфигурационной кнопки в режиме редактирования 
			conf_mode = (conf_mode < MAX_CONF_MODE) ? conf_mode+1:0; 
			if (!menu_item) { 	//если положение Time 
				DisplayTime();	//меняем текущее время 
				
			}	
			else {	
				DisplayAlarmTime();	// устанавливаем время будильника
			}		
			SetCursor();
		}
		
		if (BUTTON_INC){		     //меняем время
				if (!menu_item){		 //если Time
					SetTime();		 //текущее время
					///Set(&current_ds_Time, max_value, min_value, conf_mode);
				}	
				else {		 //если Alarm
					SetAlarmTime();	 //время будильника
				}	
                SetCursor();
		}
	}	
	
	
	
}		
   

////////////////////////////////////////////////////
// Увеличиваем время на секунду и выводим на экран
// Раз в 24 часа считываем время с устройства 
////////////////////////////////////////////////////	

__attribute__((naked)) int main(void){

	
	
	wdt_reset();
	wdt_enable(WDTO_4S);

	LCD_init();	
	init_DS();
			
		write_DS(0x0F, 0); 
		write_DS(0x08, 0x02);		
		write_DS(0x09, 0x00);
		write_DS(0x00, 0x55);	
		write_DS(0x01, 0x01);		
		write_DS(0x02, 0x00);	

	while(1) {

		
		
		wdt_reset();
		//обновление текущего времени
		if (update_flag){
			if (ALARM_CHECK)
				AlarmCheck();			
			DisplayTime();
			//срабатывание будильника 	
			update_flag = 0;
			SetCursor();
		}
		
		//update_alarm_flag = 1;
		if (update_alarm_flag){
			DisplayAlarmTime();
			update_alarm_flag = 0;
			SetCursor();	
		}
		
	}
}


///////////////////////////////////////////////////
// Отображение врмени 
///////////////////////////////////////////////////
void DisplayTime(void){
	cli();
	// Считываем время 		
	ds_GetTime(&current_ds_Time);
	sei();	
	//преобразовываем значения времени в строку для вывода на экран 
	time2str(&current_ds_Time, buf_time);
	seconds_hi = buf_time[6];
	seconds_lo = buf_time[7];
	
	//вывод времени
	LCD_gotoXY(0,0);
	LCD_putstring(buf_time);
	//вывод даты 
	LCD_gotoXY(0,1);
	LCD_putstring(buf_time+12);
}

///////////////////////////////////////////////////
// Вывод времени 
///////////////////////////////////////////////////
void DisplayMenu(void){
	update_flag = 0;
	seconds_hi = buf_menu[6];
	seconds_lo = buf_menu[7];
	
	LCD_gotoXY(0,0);
	LCD_putstring(buf_menu);
	LCD_gotoXY(0,1);
	LCD_putstring(buf_menu+12);	
}

///////////////////////////////////////////////////
// Отображение времени при установке будильника
///////////////////////////////////////////////////
void DisplayAlarmTime(void){				
	//преобразовываем значения в строку для вывода на экран 
	time2str(&alarm_ds_Time, buf_alarm);
	seconds_hi = buf_alarm[6];
	seconds_lo = buf_alarm[7];
	
	//вывод времени
	LCD_gotoXY(0,0);
	LCD_putstring(buf_alarm);
	//вывод даты 
	LCD_gotoXY(0,1);
	LCD_putstring(buf_alarm+12);	
	
}

///////////////////////////////////////////////////
// Установка курсора при изменении времени 
///////////////////////////////////////////////////
const PROGMEM uint8_t X[] = {8,1,4,7,1,4,7};
void SetCursor(void){
	//мигание курсора
	LCD_gotoXY(pgm_read_byte(&X[conf_mode]), conf_mode>3);
}


void Set(struct Time* ds,uint8_t t) {
	uint8_t* p = (uint8_t*)ds;
		*p = (*p < max_value[conf_mode])? *p+1:min_value[conf_mode];
		if ((*p & 0x0F) > 0x09) {
				*p = (*p & 0xF0) + 0x10;
		}
		write_DS(t, *p);
		if (!menu_item)
			update_flag       = 1;
		else 
			update_alarm_flag = 1;
}



void SetAlarmTime(void){
	switch(conf_mode){
	
		//часы
		case 1: 
			Set(&alarm_ds_Time.hours, ALARM_HOURS_REG);
			break;
		//минуты
		case 2:		
			Set(&alarm_ds_Time.minutes, ALARM_MINUTES_REG);
			break;
		//дни
		case 4: 
			Set(&alarm_ds_Time.date, ALARM_MASK_REG);
			break;	
	}	
}

///////////////////////////////////////////////////
// Увеличение времени 
///////////////////////////////////////////////////
void SetTime(void){
	switch(conf_mode){
		//часы
		case 1: 
			Set(&current_ds_Time.hours, HOURS_REG);
			break;
		//минуты
		case 2:			
			Set(&current_ds_Time.minutes,MINUTES_REG);
			break;
		//дни
		case 4: 
			Set(&current_ds_Time.date, DATE_REG);
			break;
		//месяцы
		case 5: 
			Set(&current_ds_Time.month, MONTH_REG);
			break;
		//годы
		case 6: 
			Set(&current_ds_Time.year,  YEAR_REG);
			break;
		
	}	

}

///////////////////////////////////////////////////
// Срабатывание будильника 
///////////////////////////////////////////////////
inline static void AlarmOn(void){	
	//сигнал будильника по возрастающему фронту 
    if (PIND & (1<<3)){
        PORTC |= SND_PIN;
        //16 сек 
        timeout_alarm--;	
    }
    else
        PORTC &= ~SND_PIN;
}

///////////////////////////////////////////////////
// Выключение будильника 
///////////////////////////////////////////////////
void AlarmOff(void){
	//сбрасываем регистр будильника 
	write_DS(0x0F, 0);
	_delay_ms(500);
	//выключаем звук 
	sound_of_alarm = 0;
}

///////////////////////////////////////////////////
// Проверка будильника
///////////////////////////////////////////////////
void AlarmCheck(void){
	timeout_alarm= COUNTER_FOR_SOUND;
	sound_of_alarm = 1;
	_delay_ms(500);
}
