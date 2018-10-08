
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��������� ��� �������� ��������� 
// ���� �������� �������������� 27.11.2015
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef	_CONFIGURATION_H
#define _CONFIGURATION_H  1

// ��������� TIMER0 �� �������� 1�
#if ((F_CPU != 12000000) && (F_CPU != 16000000))
    #error F_CPU is wrong!!!!
#endif

//�������������� ��������� � ����� ������ ��� � ����� ������� 
#define COMMON_ANODE          

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
#endif

//��������� ���������� ����� ������ 
//#define INDICATOR_UPSIDE_DOWN

#define INDICATOR_UPSIDE_DOWN

#ifdef INDICATOR_UPSIDE_DOWN
    // ������������ ����� ����� �������� ����������  
    #define DIG_HI 2
    #define DIG_MD 1
    #define DIG_LO 0
    // ����������� ����� ����� ����������� ��������� 
    #define SEG_A  1
    #define SEG_B  0
    #define SEG_C  6
    #define SEG_D  7
    #define SEG_E  5
    #define SEG_F  3
    #define SEG_G  4
    #define SEG_DP 2

#else 
    // ������������ ����� ����� �������� ���������� 
    #define DIG_HI 0
    #define DIG_MD 1
    #define DIG_LO 2

    // ����������� ����� ����� ����������� ��������� 
    #define SEG_A  7
    #define SEG_B  5
    #define SEG_C  3
    #define SEG_D  1
    #define SEG_E  0
    #define SEG_F  6
    #define SEG_G  4
    #define SEG_DP 2
#endif


// ������ "��������"  ������ 
#define BUTTON_CTRL_IS_PRESSED  ((~PINB & 1))
// ������ "��������"  �������� 
#define BUTTON_CTRL_IS_RELEASED (  PINB & 1 )

// �������� ��� ����������� ��������� 
#define MS 5

#endif	/* configuration.h */