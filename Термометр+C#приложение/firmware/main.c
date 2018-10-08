#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>   
#include <avr/pgmspace.h>
#include <stdio.h>  
#include "usbdrv/usbdrv.c"
#include "usbdrv/requests.h" 
#include "usbdrv/oddebug.h" 
#include "therm_ds18b20.h"

#define usb_init_all usbInit(); usbDeviceDisconnect(); _delay_ms(250); usbDeviceConnect();

#define sbi(reg,bit) reg |= (1<<bit)
#define cbi(reg,bit) reg &= ~(1<<bit)
#define ibi(reg,bit) reg ^= (1<<bit)

//static uchar 	  rxbuffer[128];
//static uchar      txbuffer[128]; 

volatile uchar    currentAddress;
volatile uchar    bytesRemaining;

PROGMEM char usbHidReportDescriptor[22] = {    /* дескриптор репорта USB */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x16,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

#define RQ_TYPE_read_themperature  0x05

unsigned char buffer[14] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0};


usbMsgLen_t usbFunctionSetup(uchar data[16]) {
usbRequest_t    *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR){
      
       if(rq->bRequest == CUSTOM_RQ_GET_STATUS){
           usbMsgPtr = buffer;  // указываем на структуру
            return 16; /* говорим драйверу послать 1 байт */
        }
    }else{
        /* вызовы запросов USBRQ_HID_GET_REPORT и USBRQ_HID_SET_REPORT не реализованы,
         *  поскольку мы их не вызываем. Операционная система также не будет обращаться к ним, 
         *  потому что наш дескриптор не определяет никакого значения.
         */
    }
    return 0; 



   
}

int main(void)
{
	
	usb_init_all;
    sei();
    while(1)
	{
	usbPoll();
		therm_read_temperature(buffer, 0);
		//search_ROM();
		//ibi(PORTC,4);
		
		
    usbPoll();
    }
}
