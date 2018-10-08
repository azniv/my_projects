#ifndef	_STRUCT_H
#define _STRUCT_H 1



	struct Time 
    {
        uint8_t seconds;  //секунды
        uint8_t minutes;  //минуты
        uint8_t hours;    //часы
        uint8_t day;      //день недели
        uint8_t date;     //число
        uint8_t month;    //месяц
        uint8_t year;     //год
    };
	
	
	void ds_GetTime(struct Time* ds);
    void ds_SetTime(struct Time* ds);
    void time2str(struct Time* ds, char* s);

#endif	/*struct.h*/