#include "mlx.h"


//�������� �������� �����������
uint16_t term_obj = 0;

//��������� �����������
uint16_t temp_measurement(void){
	
		TWI_Start();
		TWI_SendByte(ADDRESS_W);            
		TWI_SendByte(TERM_OBJ_ADDR);

		TWI_Start(); 
		TWI_SendByte(ADDRESS_R);
		uint8_t lo_obj = TWI_RecieveByte();	   // ������ ������� ���� �����������	
		uint8_t hi_obj = TWI_RecieveByte();	  // ������ ������� ���� ����������
		TWI_RecieveLastByte();
		TWI_Stop();
		
		       
		term_obj 	 = ((hi_obj<<8) | lo_obj); //������ ������� ���� � ������� ���� ������� 
		return    term_obj;
}
