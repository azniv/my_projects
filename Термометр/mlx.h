
#ifndef	_MLX_H
#define _MLX_H 1

#include  <avr/io.h>
#include  <util/delay.h>
#include  "twi.h"

#define DEVICE_ADDR       0x5A
#define ADDRESS_W	      (DEVICE_ADDR<<1)	
#define ADDRESS_R     	  ((DEVICE_ADDR<<1)|1)
#define TERM_DEV_ADDR	  0x06
#define TERM_OBJ_ADDR	  0x07


uint16_t temp_measurement(void);
#endif	/* mlx.h */