/*
 * a.c
 *
 * Created: 16.02.2017 16:00:51
 * Author : C
 */ 
//#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_interface.h"

/*
uint16_t  ADC_convert(void){
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return (uint16_t)ADC;
	
}*/

int main(void)
{
	uint16_t adc_value;
	uint8_t a;
	LCD_init();
    
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(ADPS1)|(ADPS0);
	ADMUX  |=(1<<REFS1)|(1<<REFS0)|(1<<MUX1)|(1<<MUX0); //внутреннее Uоп = 1,1 В
    
    /* Replace with your application code */
    while (1) 
    {
		 ADCSRA |= (1<<ADSC);
		 while (~ADCSRA & (1<<ADIF));   

 
		adc_value = ADC; 
		//adc_value *= 137;
		adc_value >>=3;
	    LCD_gotoXY(0,0);
		LCD_send_data(adc_value/1000+'0');
		LCD_send_data((adc_value%1000)/100+'0');
		LCD_send_data((adc_value%100)/10+'0');
		LCD_send_data(adc_value%10+'0');
		
		
		_delay_ms(500);
		 
    }
}

