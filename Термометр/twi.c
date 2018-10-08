
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Настройка TWI
// Для датчика температуры MLX90614
// Дата крайнего редактирования 13.04.2017
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "twi.h"

// отправка команды СТАРТ
void TWI_Start(void){
	timer = ~0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ( timer && !(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
}

// отправка СТОП
void TWI_Stop(void){
	//TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	//while((TWCR & (1<<TWINT)));
	 TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWSTO);
    // wait until stop condition is executed and bus released
    while(  timer &&(TWCR & _BV(TWSTO)));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//отправка байта
void TWI_SendByte(uint8_t c){
	TWDR = c;//загрузка значения в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//начало передачи байта данных
	while (timer && !(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
}

//инициализация TWI как передатчика
void TWI_Init (void){
	TWBR=32;         //скорость передачи
	//_delay_ms(7); 	 //задержка необходима для инизиализации

}

//отправка SLA_W + байт данных
void TWI_SendPocket (uint8_t value,uint8_t adres_rw){
	TWI_Start(); // генерируем условие СТАРТ
	TWI_SendByte(adres_rw); //оправляем адрес устройства+бит запись
	TWI_SendByte(value);//отправляем байт данных
	TWI_Stop();//генерируем условие СТОП
}

//добавляем функции чтения по TWI
//чтение байта
uint8_t TWI_RecieveByte(void){
	uint8_t dat;//переменная хранения значения
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (timer && !(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	dat = TWDR;//читаем регистр данных
	return dat;
}

//чтение последнего байта
uint8_t TWI_RecieveLastByte(void){
	uint8_t dat;//переменная хранения значения	
	TWCR = (1<<TWINT)|(1<<TWEN);//чтение последнего байта
	while ( timer && !(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	dat = TWDR;//читаем регистр данных	
	return dat;
}	


