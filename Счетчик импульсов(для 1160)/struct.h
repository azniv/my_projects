#ifndef	_STRUCT_H
#define _STRUCT_H 1



	struct Time 
    {
        uint8_t seconds;  //�������
        uint8_t minutes;  //������
        uint8_t hours;    //����
        uint8_t day;      //���� ������
        uint8_t date;     //�����
        uint8_t month;    //�����
        uint8_t year;     //���
    };
	
	
	void ds_GetTime(struct Time* ds);
    void ds_SetTime(struct Time* ds);
    void time2str(struct Time* ds, char* s);

#endif	/*struct.h*/