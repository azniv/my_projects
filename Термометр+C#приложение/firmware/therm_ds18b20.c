#include <avr/interrupt.h>
#include "therm_ds18b20.h"

# ifdef OTHERS_FUNCTIONS
	#include "usbdrv/usbdrv.h"
	
	void other_function1(void)
	{
		usbPoll();
	}
#endif


volatile char THERM_DQ = 0;

uint8_t therm_reset(void)
{
	uint8_t i;
	//Pull line low and wait for 480uS
	ds_cbi(THERM_PORT,THERM_DQ);
	ds_sbi(THERM_DDR,THERM_DQ);
		other_function1();
	_delay_us(480);
		other_function1();
	//Release line and wait for 60uS
	ds_cbi(THERM_DDR,THERM_DQ);
	_delay_us(60);
	//Store line value and wait until the completion of 480uS period
	i=(THERM_PIN & (1<<THERM_DQ));
	_delay_us(420);
		other_function1();
	//Return the value read from the presence pulse (0=OK, 1=WRONG)
	return i;
}

void therm_write_bit(uint8_t bit)
{
	//Pull line low for 1uS
	ds_cbi(THERM_PORT,THERM_DQ);
	ds_sbi(THERM_DDR,THERM_DQ);
	_delay_us(1);
	//If we want to write 1, release the line (if not will keep low)
	if(bit) ds_cbi(THERM_DDR,THERM_DQ);
	//Wait for 60uS and release the line
	_delay_us(60);
	ds_cbi(THERM_DDR,THERM_DQ);
}

uint8_t therm_read_bit(void)
{
	uint8_t bit=0;
	//Pull line low for 1uS
	ds_cbi(THERM_PORT,THERM_DQ);
	ds_sbi(THERM_DDR,THERM_DQ);
	_delay_us(1);
	//Release line and wait for 14uS
	ds_cbi(THERM_DDR,THERM_DQ);
	_delay_us(14);
	//Read line value
	if(THERM_PIN&(1<<THERM_DQ)) bit=1;
	//Wait for 45uS to end and return read value
	_delay_us(45);
	return bit;
}

uint8_t therm_read_byte(void)
{
	uint8_t i=8, n=0;
	while(i--)
	{
		//Shift one position right and store read value	
		n>>=1;
		n|=(therm_read_bit()<<7);
			other_function1();
	}
	return n;
}

void therm_write_byte(uint8_t byte)
{
	uint8_t i=8;
	while(i--)
	{
		//Write actual bit and shift one position right to make the next bit ready
		therm_write_bit(byte&1);
		byte>>=1;
			other_function1();
	}
}

void therm_read_temperature(unsigned char *buffer, unsigned char PIN_DS)
{
	THERM_DQ = PIN_DS;
	// Buffer length must be at least 12bytes long! ["+XXX.XXXX C"]
	uint8_t temperature[2];
	
//	uint16_t temper_16bit;
	int8_t digit;
	uint16_t decimal;
	uint8_t bit;
	uint8_t hex_sym = 0;
	unsigned char SROM[8] = {0};
	therm_reset();
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_CONVERTTEMP);
	
	//Wait until conversion is complete

	while(!therm_read_bit()) other_function1();

	//_delay_ms(800);
	//Reset, skip ROM and send command to read Scratchpad
	therm_reset();	other_function1();
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_RSCRATCHPAD);
	//Read Scratchpad (only 2 first bytes)
	temperature[0]=therm_read_byte();	other_function1();
	temperature[1]=therm_read_byte();	other_function1();
	therm_reset();	other_function1();

	
	//Store temperature integer digits and decimal digits
	digit=temperature[0]>>4;
	digit|=(temperature[1]&0x07)<<4;
	//Store decimal digits
	decimal=temperature[0]&0xf;
	decimal*=5;	
		other_function1();
	if (temperature[1]>0xFB)
	{
	digit = 127-digit;
	buffer[8] = '-';
	} 
	else if((temperature[0]==0x00)&&(temperature[1]==0x00)) buffer[0] = ' '; else buffer[0] = '+';
	
	//целая часть 
	buffer[1] = digit / 10 + '0';
	buffer[2] = digit % 10 + '0';
	//дробная часть
	buffer[3] = '.';
	buffer[4] = decimal/10 + '0';
	buffer[5] = decimal%10 + '0';
	other_function1();
	

	therm_reset();
	//Формируем команду поиск ROM
	therm_write_byte(THERM_CMD_SEARCHROM);    
	// Формируем на шине два тайм слота чтения 
	// датчики выдают первый бит совего адреса и его инвертированного значение
	
	//uint64_t SROM=0;
	other_function1();
	
    for (uint8_t j=0;j<8;j++) {
		for (uint8_t i=0;i<8;i++) {
			bit = therm_read_bit();
				  therm_read_bit();        //// ?????
			therm_write_bit(bit);
			SROM[7-j] |= (bit<<i) + '0';
			
		}
	}
		hex_sym = SROM[0] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[6] = hex_sym;
   hex_sym = SROM[0] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[7] = hex_sym;
   hex_sym = SROM[1] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[8] = hex_sym;
   hex_sym = SROM[1] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[9] = hex_sym;
   hex_sym = SROM[2] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[10] = hex_sym;
   hex_sym = SROM[2] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[11] = hex_sym;
   hex_sym = SROM[3] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[12] = hex_sym;
   hex_sym = SROM[3] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[13] = hex_sym;
   
   
	/*
	for (uint8_t j=0;j<4;j++) {
		for (uint8_t i =0; i<7;i+2){
		
			   hex_sym = SROM[j] >> 4;
			   hex_sym += (hex_sym<10)?'0':'A'-10;
			   buffer[i] = hex_sym;
			   hex_sym = SROM[j] & 0xF;
			   hex_sym += (hex_sym<10)?'0':'A'-10;
			   buffer[i+1] = hex_sym;
	   }
	}
	

   
   
   hex_sym = SROM[4] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[8] = hex_sym;
   hex_sym = SROM[4] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[9] = hex_sym;
   hex_sym = SROM[5] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[10] = hex_sym;
   hex_sym = SROM[5] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[11] = hex_sym;
   hex_sym = SROM[6] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[12] = hex_sym;
   hex_sym = SROM[6] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[13] = hex_sym;
   hex_sym = SROM[7] >> 4;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[14] = hex_sym;
   hex_sym = SROM[7] & 0xF;
   hex_sym += (hex_sym<10)?'0':'A'-10;
   buffer[15] = hex_sym;
   
	
	for (uint8_t j=0;j<8;j++) {
		
		
			   hex_sym = SROM[j] >> 4;
			   hex_sym += (hex_sym<10)?'0':'A'-10;
			   buffer[j] = hex_sym;
			   hex_sym = SROM[j] & 0xF;
			   hex_sym += (hex_sym<10)?'0':'A'-10;
			   buffer[j+1] = hex_sym;
	   
	}
	
	
	

	 hex_sym = SROM[j] >> 4;
	   hex_sym += (hex_sym<10)?'0':'A'-10;
	   buffer[6] = hex_sym;
	   hex_sym = SROM[j] & 0xF;
	   hex_sym += (hex_sym<10)?'0':'A'-10;
	   buffer[7] = hex_sym;
	   
	//Reset, skip ROM and start temperature conversion
	therm_reset();
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_CONVERTTEMP);
	
	//Wait until conversion is complete

	while(!therm_read_bit()) other_function1();

	//_delay_ms(800);
	//Reset, skip ROM and send command to read Scratchpad
	therm_reset();	other_function1();
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_RSCRATCHPAD);
	//Read Scratchpad (only 2 first bytes)
	temperature[0]=therm_read_byte();	other_function1();
	temperature[1]=therm_read_byte();	other_function1();
	therm_reset();	other_function1();

	
	//Store temperature integer digits and decimal digits
	digit=temperature[0]>>4;
	digit|=(temperature[1]&0x07)<<4;
	//Store decimal digits
	decimal=temperature[0]&0xf;
	decimal*=5;	
		other_function1();
	if (temperature[1]>0xFB)
	{
	digit = 127-digit;
	//buffer[0] = '-';
	//} 
	//else if((temperature[0]==0x00)&&(temperature[1]==0x00)) buffer[0] = ' '; else buffer[0] = '+';
	
	//целая часть 
	buffer[1] = digit / 10 + '0';
	buffer[2] = digit % 10 + '0';
	//дробная часть
	buffer[3] = '.';
	buffer[4] = decimal/10 + '0';
	buffer[5] = decimal%10 + '0';
	other_function1();*/
	
	

  //  onewire_reset();
  
	

	//_delay_ms(4000);
	other_function1();
	

}

void search_ROM(void){
	//therm_reset();
	//Формируем команду поиск ROM
	therm_write_byte(THERM_CMD_SEARCHROM);    
	// Формируем на шине два тайм слота чтения 
	// датчики выдают первый бит совего адреса и его инвертированного значение
	
	//uint64_t SROM=0;
	uint8_t bit;
	uint8_t SROM[8] = {0};
	unsigned char buffer[8] = {0,0, 0,0,0,0,0,0};
    for (uint8_t j=0;j<8;j++) {
		for (uint8_t i=0;i<8;i++) {
			bit = therm_read_bit();
				  therm_read_bit();        //// ?????
			therm_write_bit(bit);
			SROM[7-j] |= bit<<i;
			
		}
	}

  //  onewire_reset();
  
	uint8_t hex_sym = 0;
	for (uint8_t j=0;j<8;j++) {
	
	   hex_sym = SROM[j] >> 4;
	   hex_sym += (hex_sym<10)?'0':'A'-10;
	   buffer[6] = hex_sym;
	   hex_sym = SROM[j] & 0xF;
	   hex_sym += (hex_sym<10)?'0':'A'-10;
	   buffer[7] = hex_sym;
	   
	}
	_delay_ms(4000);
	
	
	
}

