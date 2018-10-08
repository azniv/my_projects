#include  <avr/interrupt.h>
#include  <avr/io.h>
#include  <util/delay.h>
#include <avr/pgmspace.h>


#include  "LCD_interface.h"
#include  "adc.h"
#include  "buttons.h"
#include  "mlx.h"
#include  "power.h"
#include  "pwm.h"
PROGMEM const uint8_t FOR_INIT[]  = {CMD_INIT, CMD_INIT, CMD_INIT,CMD_SET_INTERFACE,  CMD_SET_PARAMETRS, CMD_DISPLAY_ON, CMD_DISPLAY_CLEAR, CMD_ENTRY_MODE_SET};

uint8_t  int_part;
uint8_t  decimal_part;
	
uint16_t term_obj;
uint16_t volt;
uint16_t adc;
uint8_t  battery_pr;
uint8_t  sensor_found; 


void init_all(void);			  //������������� ���� �������
void display_measurement(void);   //����� ���������

static inline  void display_temp(void);
static inline  void display_volt(void);

ISR(TIMER0_OVF_vect) {
    if (timer)
        timer--;
}


//���������� �� ������
ISR(PCINT1_vect){
	if (BUTTON_PRESSED(1)){
		SLEEP_AND_POWER_OFF();
	}
}
	
	
__attribute__((naked)) int main(void){
	init_all();
	while (1){
		sensor_found = 0;									//����  = 0, ������� ��������� �� ��������� �������
		adc  = adc_measurement();							//�������� ADC
		PWM_SET(adc);										//��������� �������������
        VOLT_MEASUREMENT(adc, volt);						//��������� � �������
		term_obj =  temp_measurement();						//��������� �����������
	    decimal_part = term_obj % 50;						//������� �����  ��������� 
		int_part	 = term_obj / 50 - 273;					//����� ����� ��������� � �������� ������� 
		
		display_measurement();								//����� ��������� 
		//uint8_t battery_pr = ADC_to_battery_percent(adc);  // ��������� � ���������                           
	}
		
}


void init_all(void){
	POWER_INIT();			
	POWER_ON();
	SLEEP_MODE();
	INTERRUPT_INIT();
	BUTTONS_INIT();
	PWM_INIT();
	ADC_INIT();
	TWI_Init();
	LCD_INIT();	
	sei();
}


//����� �������� ����������� 
static inline void display_temp(void){
	LCD_SET_POSITION(0,0); 
	LCD_send_data('t');
	LCD_send_data('=');
	
	//������� ����
	// ����������� > 0
	if (int_part > 0){
		LCD_SET_POSITION(2,0); 
		LCD_send_data('+');
	}
	//����������� < 0
	if (int_part < 0){
		LCD_SET_POSITION(2,0); 
		LCD_send_data('-');
	}
	//������� �����������
	LCD_SET_POSITION(3,0);
	//���� ����������� ����� 	
	if (int_part/100)
		LCD_send_data(int_part/100+'0');
	LCD_send_data(int_part%100/10+'0');
	LCD_send_data(int_part%10+'0');
	LCD_send_data('.');
	LCD_send_data(decimal_part%10+'0');

}

//����� �������� ���������� 
static inline void display_volt(void){
	LCD_SET_POSITION(0,1);
	LCD_send_data('V');
	LCD_send_data('=');
	 //��������� �������� ���������� �� PC3    
	LCD_send_data(volt/1000 + '0');      //����� ����� volt[�]
	LCD_send_data('.');        
	LCD_send_data(volt%1000/100 + '0');  //����� �������
	LCD_send_data(volt%100/10 + '0');
	LCD_send_data(volt%10 + '0');
}

//����� �������� ���������� � "%"
static inline void display_volt_pr(void){
	LCD_SET_POSITION(0,1);
	LCD_send_data('U');
	LCD_send_data('=');
	if (battery_pr > 99)                        
		LCD_send_data('1');
	LCD_send_data(battery_pr / 10 % 10 + '0');
	LCD_send_data(battery_pr % 10 + '0');
	LCD_send_data('%');
        _delay_ms(500);
}
 void display_measurement(void){
	

	if (timer){
		sensor_found= 1;
		display_temp();
		_delay_ms(200);       
		display_volt();
		_delay_ms(1000);

	}
	//sleep_and_power_off();
	if (!sensor_found) {
		LCD_send_cmd(CMD_DISPLAY_CLEAR);
		_delay_ms(15);
		LCD_SET_POSITION(0,0);
		LCD_putstring ((uint8_t*)"NO");
		LCD_SET_POSITION(0,1);
		LCD_putstring ((uint8_t*)"SENSOR");
		_delay_ms(15);
	}
}	















    

/*

	while(1) {
       	

		uint16_t term_obj = 0;
		uint8_t  int_part;
		uint8_t  decimal_part;
		
		TWI_Start();
		TWI_SendByte(ADDRESS_W);            
		TWI_SendByte(TERM_OBJ_ADDR);

	
		TWI_Start(); 
		TWI_SendByte(ADDRESS_R);
		uint8_t lo_obj = TWI_RecieveByte();	   // ������ ������� ���� �����������	
		uint8_t hi_obj = TWI_RecieveByte();	  // ������ ������� ���� ����������
		TWI_RecieveLastByte();
		TWI_Stop();
		
		

		_delay_ms(200);        
		
       
		
		term_obj 	 = ((hi_obj<<8) | lo_obj); //������ ������� ���� � ������� ���� ������� 
		decimal_part = term_obj % 50;			//������� �����  ��������� 
		int_part	 = term_obj / 50 - 273;		//����� ����� ��������� � �������� ������� 
		
		
			
         
        
		ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
        while (~ADCSRA & (1<<ADIF));            //���� �� ���������� ��������� (�� ������ ����)
         
        volt = ADCL;                             //������� ���� �������� � ���
        volt |= (ADCH<<8);   
                   //������� ���� �������� � ���
        // ��������� �������������
        if (volt>236)
           OCR0A  = (59578 / volt) & 0xFF;
        else
            OCR0A = 255;
           
        volt *= 137;                   
        volt >>= 3;    
		
        // ����� 1
        // ���� �������
        // ���� �������
        // ���� ��������
	
    
			
			
			//������� ����������
			
		if(!first_measurement){		//�� ������� ��������� ������� ��������� 
			
			LCD_gotoXY(0,0); 
			LCD_send_data('t');
			LCD_send_data('=');
			
			//������� ����
			// ����������� > 0
			if (int_part > 0){
				LCD_gotoXY(2,0); 
				LCD_send_data('+');
			}
			//����������� < 0
			if (int_part < 0){
				LCD_gotoXY(2,0); 
				LCD_send_data('-');
			}
			//������� �����������
			LCD_gotoXY(3,0);
			//���� ����������� ����� 	
			if (int_part/100)
				LCD_send_data(int_part/100+'0');
			LCD_send_data(int_part%100/10+'0');
			LCD_send_data(int_part%10+'0');
			LCD_send_data('.');
			LCD_send_data(decimal_part%10+'0');
			
			_delay_ms(200);       
		
			LCD_gotoXY(0,1);
			LCD_send_data('V');
			LCD_send_data('=');
			 //��������� �������� ���������� �� PC3    
			LCD_send_data(volt/1000 + '0');      //����� ����� volt[�]
			LCD_send_data('.');        
			LCD_send_data(volt%1000/100 + '0');  //����� �������
			LCD_send_data(volt%100/10 + '0');
			LCD_send_data(volt%10 + '0');
			_delay_ms(400);		
			
			
		//	_delay_ms(3000);
	
			
			
			
			
		// ������� ���������� ��� ���������, ��� ��� ���������
			
	
			power_off();
			
		asm volatile("sleep");	
		}
		
					
			
			
		else
		   first_measurement = 0;
		   
	}
		
	
	
}
//����� Power-down
inline static void sleep_and_power_off(void){
		
	ADCSRA = 0;		
	TCCR0A = 0;
	TCCR0B = 0;    // div 8
	PORTD  = 0;    // ���� ���
	PORTB  = 0;    // !!
		
    asm volatile ("nop");    
	asm volatile ("nop");  
    asm volatile ("sleep");  
	
}


*/

