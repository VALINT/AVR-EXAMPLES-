/*
 * MAX7219.h
 *
 * Created: 01.04.2018 14:25:57
 *  Author: VAL
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_

#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdarg.h>

// If you will use program SPI, select SCL and MOSI PINs

#define MOSI_DDR  DDRB
#define MOSI_PORT PORTB
#define MOSI_PIN  1

#define SCL_DDR  DDRB
#define SCL_PORT PORTB
#define SCL_PIN	 2

#define CS_DDR  DDRB
#define CS_PORT PORTB
#define CS_PIN	 0

#define USING_HARD_SPI
//#define USING_PROGRAM_SPI

uint8_t init_spi(void);
uint8_t max7219_init(void);
uint8_t max7219_clear(void);
uint8_t max7219_write(uint8_t, uint8_t, ...);

#endif /* MAX7219_H_ */