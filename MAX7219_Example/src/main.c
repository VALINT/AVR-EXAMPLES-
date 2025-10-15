/*
 * _1803_Project_Saturn_PixelClock.cpp
 *
 * Created: 01.04.2018 12:33:42
 *  Author: VAL
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "MAX7219.h"

uint8_t display[8][3] = {
{0b00000000, 0b00000000, 0b00000000},
{0b01111001, 0b01010110, 0b01000100},
{0b01000101, 0b00011001, 0b01001000},
{0b01111001, 0b01010001, 0b01110000},
{0b01000101, 0b01010001, 0b01010000},
{0b01000101, 0b01010001, 0b01001000},
{0b01111001, 0b01010001, 0b01000100},
{0b00000000, 0b00000000, 0b00000000}
};

int main(void)
{
	DDRB = 0xff;

	max7219_init();
	while(1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			max7219_write(i+1, 3, display[i][0],display[i][1],display[i][2]);
		}
		
		_delay_ms(1000);
		
		for (uint8_t i = 0; i < 8; i++)
		{
			max7219_write(i+1, 3, ~display[i][0], ~display[i][1], ~display[i][2]);
		}	
		
		_delay_ms(1000);
	}	
}
