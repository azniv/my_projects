//////////////////////////////////////////////////////////////////////////////////////////////
// 						����-���������                                                      //
// 						MCU ATMEGA48PA														//
// 						F_CPU 8 MHz															//
// ���� � ����� ��������������:    ������� ����� BUTTON_CONF ����� 2 �.			    		//
// ����� �� ������ ��������������: ������� ����� BUTTON_CONF ����� 2 �.				    	//
//							   ��� ������������� ����� 8 c. ��� ��������.					//	
// � ����� �������������� ������������ ���� ����:                                           //
//                                 1)Time													//
//								   2)Alarm													//
// ����������� ������� � ������ �������: 			�������� ������� BUTTON_DEC				//
// ����� ���� ��� ����� ������:                     �������� ������� BUTTON_CONF			//
// ��������� ������� ������� ��� ��������� ��������:�������� ������� BUTTON_CONF			//
// ��������� ����� ��������: 						�������� ������� BUTTON_INC				//
// ���������� ����������: 							�������� ������� BUTTON_DEC				// 
//											���  	������������� 	����� 16 �. 			//							 		
// 				���� �������� ��������������: 26.07.2016									//
// 				�����: ������� �.�.															//
//////////////////////////////////////////////////////////////////////////////////////////////

// � ������������ T0 �������� �����


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

//������ ��������� ��� ���������� �������� � ���������� 
volatile struct Time current_ds_Time;
volatile struct Time alarm_ds_Time;

//������������ ��������, ������� ����������� ��� ���������� ������� 
const  uint8_t   max_value[]  = {0, 0x23, 0x59, 0, 0x31, 0x12, 0x40};

//�����������  ��������, ������� ����������� ��� ���������� ������� 
const  uint8_t   min_value[]  = {0,    0, 0x01, 0, 0x01, 0x01, 0x16};
//�������� ������� � ���� 
uint8_t buf_time[]       = {'0','0',':','0','0',':','0','0',0,'0','0',0,
                            '0','0','/','0','0','/','0','0',0};			  				  
//�������� ������� � ���� ����������  				  
uint8_t buf_alarm[]      = {'0','0',':','0','0',':','0','0',0,'0','0',0,
                            '0','0','/','0','0','/','0','0',0};
//����
uint8_t buf_menu[]       = {'1',')','T','i','m','e',' ',' ',0,'0','0',0,
                            '2',')','A','l','a','r','m',' ',0};				  
				  				  

//���� ��� ������������ ����� ������ 		  
volatile uint8_t  update_flag           = 1;
//���� ��� ������������ ����� ������ 		  
volatile uint8_t  update_alarm_flag     = 0;

//��� ����� ���������� 
volatile uint8_t  sound_of_alarm        = 0;

//����� ��������� �������
volatile uint8_t  conf_mode             = 0;
//����
volatile uint8_t  clock_ticking         = 0;
volatile uint8_t  menu_conf_mode        = 0;
//��� �������� ������� ������� ������ 
volatile uint8_t  button_PIN2_counter   = 0;
volatile uint8_t  button_PIN1_counter   = 0;
//�����  ��� ��������������� ������ �� ������ ��������������
volatile uint16_t confmode_off          = 0;
// ������ ����� ��� ��������������� ���������� ���������� 16�
volatile uint16_t timeout_alarm         = 0;



//uint8_t conf[] = {0, &current_ds_time.hours, &current_ds_time.minutes, &current_ds_time.seconds,
//					&current_ds_time.date, &current_ds_time.mounth, &current_ds_time.year};
					
//uint8_t reg[]  = {0, HOURS_REG, MINUTES_REG, SECONDS_REG,  DATE_REG, MONTH_REG, YEAR_REG};

//������� ������ ����� ������
volatile uint8_t seconds_hi = '0';
//������� ������ ����� ������
volatile uint8_t seconds_lo = '0';
//����������� ������� �����/���� � ����                                      
volatile uint8_t menu_item = 0;

//������������ ���������� 
inline static void AlarmOn(void);
//���������� ���������� 
void AlarmOff(void);
//�������� ��������� ���������� 
void AlarmCheck(void);
//����������� ������
void DisplayTime(void);
//����������� ������� ��� ��������� ���������� 
void DisplayAlarmTime(void);
//����� ���� 
void DisplayMenu(void);
// ���������� ������� ��� ��������� �������
void SetCursor(void);
//���������� �������
void SetTime(void);
void Set(struct Time* ds,  uint8_t t);
//��������� ����������
void SetAlarmTime(void);


///////////////////////////////////////////////////
// ���������� ���������� �� T0: ����� ������������ = 1�
///////////////////////////////////////////////////
ISR(TIMER0_OVF_vect) {
	//��������� �� ��������� � ������ �������������� 
	if (!clock_ticking){
		//��������� ������ �� ��� ���, ���� 
		//�� ������ ������ � �� ������� ����� ��������
		if (sound_of_alarm && timeout_alarm){
			AlarmOn();
		}
		else {
			write_DS(0x0F, 0); 
			PORTC &= ~SND_PIN;
		}		
	}
	
	
	//����� �� ������ �������������� �� ��������� 8��� ��� �������� 
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
	
	//����� ��������������
    if (button_PIN2_counter) {
	    button_PIN2_counter--;
        if(!button_PIN2_counter && BUTTON_CONF) {
			clock_ticking = 1;		// �����, ����� 
									//���������� ���� �� ����� ��������������
			menu_conf_mode ^= 1;	// = 1 ����� �������������� 
			if (menu_conf_mode){
				DisplayMenu();		//����� ���� 	
				LCD_send_cmd(CMD_CURSOR_ON);
				LCD_gotoXY(0,0);
			}
			//��� ������ �� ������ �������������� ���������� ��� ���������� 
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
// ������������ ������ 
// �������� �������� � ������ INT/SQW
///////////////////////////////////////////////////
ISR(INT1_vect){
	//�� ����������� ������� ��� ���������, 
	//���� ������� ����� ��������� ��� ���������� 
	if (!clock_ticking){
    // ����������������� ������ 
		seconds_lo++;
		// ����������������� ������ �� BCD �������� 
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
		//������� ������� �� ������� ������
		//������ ������� ����������� ������ ����� �������� ������   
		LCD_gotoXY(6,0);
		LCD_send_data(seconds_hi);
		LCD_send_data(seconds_lo);
	}
			
			
}

///////////////////////////////////////////////////
// ��������� ������� 
/////////////////////////////////////////////////// 
ISR(PCINT2_vect) {
	//��� ����� ������� ����������� ����� 8��� 
	confmode_off  = COUNTER_FOR_AUTOMATIC_OFF;  	
						
	//����� ��������� ������� � ����������� ������� ������� 
	if  (!button_PIN2_counter &&  BUTTON_CONF)
		button_PIN2_counter = COUNTER_FOR_BUTTONS;				
		
	if (sound_of_alarm && timeout_alarm && BUTTON_DEC)
		AlarmOff();
	
	if (menu_conf_mode) {		//���� ����� ��������������
		//
		if (BUTTON_DEC) {		//����������� ������� ������� :�����, ����.
			menu_item ^= 1;			// !� - ������� 1)Time
								//  menu_item - ������� 2)Alarm
			LCD_gotoXY(0, menu_item);
			conf_mode = 0;
		}
		
		if (BUTTON_CONF){		//�������� ������� ���������������� ������ � ������ �������������� 
			conf_mode = (conf_mode < MAX_CONF_MODE) ? conf_mode+1:0; 
			if (!menu_item) { 	//���� ��������� Time 
				DisplayTime();	//������ ������� ����� 
				
			}	
			else {	
				DisplayAlarmTime();	// ������������� ����� ����������
			}		
			SetCursor();
		}
		
		if (BUTTON_INC){		     //������ �����
				if (!menu_item){		 //���� Time
					SetTime();		 //������� �����
					///Set(&current_ds_Time, max_value, min_value, conf_mode);
				}	
				else {		 //���� Alarm
					SetAlarmTime();	 //����� ����������
				}	
                SetCursor();
		}
	}	
	
	
	
}		
   

////////////////////////////////////////////////////
// ����������� ����� �� ������� � ������� �� �����
// ��� � 24 ���� ��������� ����� � ���������� 
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
		//���������� �������� �������
		if (update_flag){
			if (ALARM_CHECK)
				AlarmCheck();			
			DisplayTime();
			//������������ ���������� 	
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
// ����������� ������ 
///////////////////////////////////////////////////
void DisplayTime(void){
	cli();
	// ��������� ����� 		
	ds_GetTime(&current_ds_Time);
	sei();	
	//��������������� �������� ������� � ������ ��� ������ �� ����� 
	time2str(&current_ds_Time, buf_time);
	seconds_hi = buf_time[6];
	seconds_lo = buf_time[7];
	
	//����� �������
	LCD_gotoXY(0,0);
	LCD_putstring(buf_time);
	//����� ���� 
	LCD_gotoXY(0,1);
	LCD_putstring(buf_time+12);
}

///////////////////////////////////////////////////
// ����� ������� 
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
// ����������� ������� ��� ��������� ����������
///////////////////////////////////////////////////
void DisplayAlarmTime(void){				
	//��������������� �������� � ������ ��� ������ �� ����� 
	time2str(&alarm_ds_Time, buf_alarm);
	seconds_hi = buf_alarm[6];
	seconds_lo = buf_alarm[7];
	
	//����� �������
	LCD_gotoXY(0,0);
	LCD_putstring(buf_alarm);
	//����� ���� 
	LCD_gotoXY(0,1);
	LCD_putstring(buf_alarm+12);	
	
}

///////////////////////////////////////////////////
// ��������� ������� ��� ��������� ������� 
///////////////////////////////////////////////////
const PROGMEM uint8_t X[] = {8,1,4,7,1,4,7};
void SetCursor(void){
	//������� �������
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
	
		//����
		case 1: 
			Set(&alarm_ds_Time.hours, ALARM_HOURS_REG);
			break;
		//������
		case 2:		
			Set(&alarm_ds_Time.minutes, ALARM_MINUTES_REG);
			break;
		//���
		case 4: 
			Set(&alarm_ds_Time.date, ALARM_MASK_REG);
			break;	
	}	
}

///////////////////////////////////////////////////
// ���������� ������� 
///////////////////////////////////////////////////
void SetTime(void){
	switch(conf_mode){
		//����
		case 1: 
			Set(&current_ds_Time.hours, HOURS_REG);
			break;
		//������
		case 2:			
			Set(&current_ds_Time.minutes,MINUTES_REG);
			break;
		//���
		case 4: 
			Set(&current_ds_Time.date, DATE_REG);
			break;
		//������
		case 5: 
			Set(&current_ds_Time.month, MONTH_REG);
			break;
		//����
		case 6: 
			Set(&current_ds_Time.year,  YEAR_REG);
			break;
		
	}	

}

///////////////////////////////////////////////////
// ������������ ���������� 
///////////////////////////////////////////////////
inline static void AlarmOn(void){	
	//������ ���������� �� ������������� ������ 
    if (PIND & (1<<3)){
        PORTC |= SND_PIN;
        //16 ��� 
        timeout_alarm--;	
    }
    else
        PORTC &= ~SND_PIN;
}

///////////////////////////////////////////////////
// ���������� ���������� 
///////////////////////////////////////////////////
void AlarmOff(void){
	//���������� ������� ���������� 
	write_DS(0x0F, 0);
	_delay_ms(500);
	//��������� ���� 
	sound_of_alarm = 0;
}

///////////////////////////////////////////////////
// �������� ����������
///////////////////////////////////////////////////
void AlarmCheck(void){
	timeout_alarm= COUNTER_FOR_SOUND;
	sound_of_alarm = 1;
	_delay_ms(500);
}
