#ifndef	_CONFIG_H
#define _CONFIG_H 1    
	
	//������ �3
	#define BUTTON_CONF  (~PIND&(1<<2))
	//������ �2
	#define BUTTON_DEC	 (~PIND&(1<<1))
	//������ �1
	#define BUTTON_INC	 (~PIND&(1<<0))
	
	//�������
	#define SND_PIN		 (1<<0)	
	//������� ����������
	#define ALARM_CHECK	 (read_DS(0x0F) & 0b1)	

	//������� ��� ��������� ������� 
	#define MAX_CONF_MODE  6

	
	// 127 = 1 �������
	#define COUNTER_FOR_BUTTONS           127

	// ������� ��� ��������������� ������ 
	//    �� ������ ��������������(8 ���)
	#define COUNTER_FOR_AUTOMATIC_OFF     1016
	
	//����� ��� ��������������� ���������� ���������� 16�
	#define COUNTER_FOR_SOUND             1016
#endif	/* config.h */
	