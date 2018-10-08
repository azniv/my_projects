
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ������
// ��� ������� ����������� MLX90614
// ���� �������� �������������� 19.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BUTTONS_H
#define _BUTTONS_H_1
	
	#include <avr/io.h>
	#include "common.h"
	
	#define BUTTONS_PORTNAME C
	
	// ������ ������� � ����� ��� ������
	// �����
	#define BUTTON1 0
	// ������
	#define BUTTON2 2
		
	
	#define BUTTONS_DDR           CONCAT(DDR,  BUTTONS_PORTNAME)
	#define BUTTONS_PORT          CONCAT(PORT, BUTTONS_PORTNAME)
	#define BUTTONS_PIN           CONCAT(PIN,  BUTTONS_PORTNAME)
	
	
	
    //������ ������ 
	#define BUTTON_PRESSED(x)   (~BUTTONS_PIN&(1<<(x)))
	//������ �
	#define BUTTON_RELEASED(X)  (BUTTONS_PIN&(1<<(x)))
	
	// ������������� ������: �������� � ������� ����������� �����������
	#define BUTTONS_INIT() (BUTTONS_PORT = (1<<BUTTON1)|(1<<BUTTON2))   			


#endif /*buttons.h*/