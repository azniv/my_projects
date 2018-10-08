#include "mlx.h"


//хранение значения температуры
uint16_t term_obj = 0;

//измерение температуры
uint16_t temp_measurement(void){
	
		TWI_Start();
		TWI_SendByte(ADDRESS_W);            
		TWI_SendByte(TERM_OBJ_ADDR);

		TWI_Start(); 
		TWI_SendByte(ADDRESS_R);
		uint8_t lo_obj = TWI_RecieveByte();	   // читаем старший байт температуры	
		uint8_t hi_obj = TWI_RecieveByte();	  // читаем младший байт температур
		TWI_RecieveLastByte();
		TWI_Stop();
		
		       
		term_obj 	 = ((hi_obj<<8) | lo_obj); //меняем младший байт и старший байт местами 
		return    term_obj;
}
