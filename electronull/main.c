
/********************************************************************************************************
 * 	ELECTRONULL																							*
 * 	����������� - ������������� ����������, ������������  ��� ������� ����������� ����������� ������ �� *
 * �������� �����������. ������� �� ������� �����������  � ����� ���������. �������� � ���� ��������   	*
 * ������ ������ �����������. 																		   	*
 * 	������ ����������� ������������ �� ���� 2 �������������.											*
 *  ���� ��������� ����������� ����� ��������������� �����������.										* 
 *	������ ���������� �� ���� ���������������� ATMEGA16 												*
 *******************************************************************************************************/
 

#include  <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define MS 500

#define SEG_A  0
#define SEG_B  1
#define SEG_C  2
#define SEG_D  3
#define SEG_E  4
#define SEG_F  5
#define SEG_G  6
#define SEG_1  7



#define FIRST_TON 1900U
#define SECOND_TON 1700U


#define COMMON_ANODE          // �������������� �������� � ����� ������ ��� � ����� ����������0

#ifdef COMMON_ANODE
  #define NUM_0 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G)))
  #define NUM_1 (uint8_t)(~((0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_2 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_3 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_4 (uint8_t)(~((0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_5 (uint8_t)(~((1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_6 (uint8_t)(~((1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_7 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_8 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_9 (uint8_t)(~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_10 (uint8_t)(~((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G)))
  #define NUM_11 (uint8_t)(~((1<<SEG_1)|(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_12 (uint8_t)(~((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))	
  #define NUM_13 (uint8_t)(~((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_14 (uint8_t)(~((1<<SEG_1)|(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_15 (uint8_t)(~((1<<SEG_1)|(1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
#else
  #define NUM_0 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G)))
  #define NUM_1 (uint8_t)(((0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_2 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_3 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_4 (uint8_t)(((0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_5 (uint8_t)(((1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_6 (uint8_t)(((1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_7 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_8 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_9 (uint8_t)(((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
   #define NUM_10 (uint8_t)(((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G)))
  #define NUM_11 (uint8_t)(((1<<SEG_1)|(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)))
  #define NUM_12 (uint8_t)(((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))	
  #define NUM_13 (uint8_t)(((1<<SEG_1)|(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G)))
  #define NUM_14 (uint8_t)(((1<<SEG_1)|(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
  #define NUM_15 (uint8_t)(((1<<SEG_1)|(1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)))
#endif

   
   
   
volatile uint8_t tracking_pressing  = 0;    //��������� �������. ���������� ��� �� ������
volatile uint8_t pressed_zero  = 0; 
const uint8_t numbers[] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_10,NUM_11,NUM_12,NUM_13,NUM_14,NUM_15};


// 60 ������������ ������� - ��� ~2 �������
#define MAX_TIMER_COUNT 60u

uint8_t timer_count = MAX_TIMER_COUNT;

/**********************************************************
 * ����� - ����������� ���������					      *	
 *********************************************************/
inline void reset(void){			
   tracking_pressing = 0;
  // pressed_zero  = 0;
   PORTC = 0xFF;
   PORTD |= ~(1<<0);
   	
}                

/**********************************************************
 *������ "�����"									      *
 *********************************************************/
ISR(INT0_vect){																	
	reset();
}

/**********************************************************
* �������� ��� ������ MAX_TIMER_COUNT                     *
*                 �� ����� ~2 �������  					  *
 *********************************************************/
ISR(TIMER0_OVF_vect) {
    if (!timer_count) {
        timer_count = MAX_TIMER_COUNT;
	    reset();
		
    }
    else {
        timer_count--;
    }
	
}

/**********************************************************
 * �������������										  *
 *********************************************************/
inline void initialization(void) {
	MCUCR = (1<<ISC01);   /// �� ���������� ������ 
	
	GICR  = (1<<INT0);    
    TCCR0 = (1<<CS00)|(1<<CS02);

	DDRC  = 0xFF;	
	PORTC = 0xFF;		          
    
	/// �������������   
    PORTA = 0xFF;                        /// ����� �� 0-7
    PORTB = 0xFF;	                     /// ����� �� 8-15
	
	DDRD  = (1<<0);                     ///������� 

    PORTD = (1<<1)|(1<<2);             /// ������������� ���������    PD1 - ��������� 
										///	                 		   PD2 - ������ "�����"

}

/**********************************************************
 * �������� ���������									  *
 *********************************************************/
inline static void self_test(void){
	for (uint8_t i = 0; i < 8; i++){
		PORTC &=~(1<<i);
		_delay_ms(MS);
	}		
	_delay_ms(MS);						
}

 

/**********************************************************
 * ��������� 											  *
 *********************************************************/
inline static void autoreset_check(void){ 
    if (~PIND&(1<<1)){
        timer_count = MAX_TIMER_COUNT;        
	    TIMSK |= (1<<TOIE0);
	}
	else {
        TIMSK &=~(1<<TOIE0);
    }
}




/**********************************************************
 * ������������� ������                                   *
 * ��������������� ��� ������ ������� ������              *
 *********************************************************/

inline static void tonality(int sound){
	for (uint8_t j = 0; j<150; j++){
		PORTD ^= (1<<0);
		_delay_us(sound);
	}
	_delay_ms(200);

}
inline static void zero_track(void){
	
	
		tonality(FIRST_TON);
		tonality(SECOND_TON);
		tonality(FIRST_TON);
		_delay_ms(500);
	
}



/**********************************************************
 *  ��������� 											  *
 *********************************************************/  
inline static void indication(void){
	
	if (!tracking_pressing) { 
	 
		///���  ������ ����� �� 1-7 ������������� ����� PA0-PA1
		uint8_t state = ((uint8_t)(~PINA));
				for ( uint8_t i = 0; i < 8; i++) {
	  
					if (state & (1<<i)) {
						
						PORTC = numbers[i];
						tracking_pressing = 1; 
						
						///��� ������ ������� ������� ������������� 
						/// ������������� �������� ������ 
						
						if (!i){
							
							zero_track();
						}
						return;
						
					}
				  
				}
				
				state = ((uint8_t)(~PINB));
				for ( uint8_t i = 0; i < 8; i++) {
					
					///���  ������ ����� �� 8-15 ������������� ����� PB0-PB7
					
						if (state & (1<<i)){
							PORTC = numbers[i+8];
							
							
							tracking_pressing = 1;
							return;
						} 	
				}	
	}			
}




int main(void){
    
    initialization();
	self_test();
	sei();

	while(1){
        autoreset_check();
		indication();
 
	}	
}