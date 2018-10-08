//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Настройка АЦП
// Для датчика температуры MLX90614
// Дата крайнего редактирования 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	_ADC_H
#define _ADC_H 1
	#include  <avr/io.h>
	#include  "power.h"

	#define MIN_BATTERY_ADC 226
	#define MAX_BATTERY_ADC 260
		//для делителя напряжения 
	#define ADC_INIT()  {															\
							(ADMUX  = (1<<REFS1)|(1<<REFS0)|(1<<MUX1)|(1<<MUX0));	\
						    (ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));	\
					    } 
						
	 #define PWM_SET(X) do{                                           			    \
                            uint8_t __pwm_temp = (24 + ((X)&0xFF));     			\
                            OCR0A = (__pwm_temp & (1<<7))?0:__pwm_temp; 			\
						  } while (0)
                        
	#define VOLT_MEASUREMENT(X,Y) do {												\
							(Y) = ((X)*137)>>3; 									\
						  } while (0)
                                    
    
	
	/*
	#define ADC_TO_BATTERY_PERCENT(X,Y) do {										\
							if ((X)<= MIN_BATTERY_ADC) return 0;						\
							(X) -=	MIN_BATTERY_ADC;
							
							
							}
									*/
	
	
	
	


							
	uint16_t adc_measurement(void);
	uint8_t  ADC_to_battery_percent(uint16_t adc);	
	// uint16_t volt_measurement(uint16_t adc);
#endif	/* ADC.h */