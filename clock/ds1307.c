#include "ds1307.h"
#include "TWI.h"
#include "struct.h"



//��������� ����� ������� 
//#define  DEBUG




/////////////////////////////////////////////////////
// ������� ������������� �����  
/////////////////////////////////////////////////////
void init_DS(void){
	
    DDRD  &= ~((1<<0)&(1<<1)&(1<<2)&(1<<3));  // ������ 
    PORTD |= (1<<0)|(1<<1)|(1<<2)|(1<<3);	
	
	
    DDRC  |= (1<<3)|(1<<0); 		//������� 
	
	write_DS(0x0E, 0); 				//  ��������� INT/SQW		
	
	// ���������� �� INT/SQW
    EIMSK = (1<<INT1);
    EICRA = (1<<ISC11)|(1<<ISC10);
    
	// ������ T0
    TIMSK0 = (1<<TOIE0);  
    TCCR0B = (1<<CS02);//|(1<<CS00); //������������ 1024
  
	// ���������� �� ������ 
    PCICR  |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT16)|(1<<PCINT17)|(1<<PCINT18);
	
		
	#ifdef DEBUG
		//������ ��������� ��� ������ ������� 
		struct Time write_ds_Time;
		write_ds_Time.seconds = 0x00;
		write_ds_Time.minutes = 0x29;
		write_ds_Time.hours   = 0x12;
		write_ds_Time.year    = 0x16;
		write_ds_Time.date    = 0x02;
		write_ds_Time.month   = 0x05;
		
		ds_SetTime(&write_ds_Time);
	#endif	    
	
	sei();

}

/////////////////////////////////////////////////////
// ������� ������ ������ �������� 
/////////////////////////////////////////////////////
void write_DS(uint8_t reg, uint8_t time){ //�������� ��� ���������: ����� ��������, � �������� ����� ���������� � ������������ ����������z{
	TWI_Start();
	TWI_SendByte(ADDRESS_W);   //��������� ����� ����������+��� ������
    TWI_SendByte(reg);        //����� �������� 
	//�������� ���������� ��� ������ � ���� ��������
	TWI_SendByte(time);
	TWI_Stop();				//��������� ��������� ����
}

/////////////////////////////////////////////////////
// ������� ������ ������ �������� 
/////////////////////////////////////////////////////
uint8_t read_DS(uint8_t reg){ //�������� ����� ��������{
    uint8_t time;
	TWI_Start();		 
    TWI_SendByte(ADDRESS_W);  
    TWI_SendByte(reg);  
    TWI_Start();
	TWI_SendByte(ADDRESS_R);   
	TWI_ReadByte();
	time = TWDR;
    return time;
}
////////////////////////////////////////////////////
//������� ������ ��� ��������
////////////////////////////////////////////////////
void ds_GetTime(struct Time* ds){
	uint8_t* p = (uint8_t*)ds;
	
	for(uint8_t i=0;i<7;i++)
	    *p++=read_DS(SECONDS_REG+i);
}


////////////////////////////////////////////////////
//������� ���������� ��� �������� (������� � ����)
////////////////////////////////////////////////////
void ds_SetTime(struct Time* ds){
	uint8_t* p = (uint8_t*)ds;
	
	for(uint8_t i=0;i<7;i++)
	    write_DS(SECONDS_REG+i, *p++);
}

////////////////////////////////////////////////////
// ��������������� �������� � ������ ��� ������ �� ����� 
////////////////////////////////////////////////////
void time2str(struct Time* ds, uint8_t* s) {
	uint8_t* p = (uint8_t*)ds;

	for(uint8_t i=0;i<7;i++) {
		s[3*i]   = (*p>>4)+'0';
		s[3*i+1] = (*p&0x0F)+'0';
		p++;
	}
	uint8_t x;
	
	// ������ ������� ���� ��� �������� ������ � ������ 
	// ��� �������� ����� 
    INTERCHANGE_BYTES(s[0], s[6], x);
	INTERCHANGE_BYTES(s[1], s[7], x);
}