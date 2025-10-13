/*
 * Slider_LED.cpp
 *
 * Created: 12.05.2015 3:43:07
 *  Author: VAL
 */ 

// Set MCU frequency
// Uncomment if it wasn't defined anywhere
//#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define SWITCHING_TIME 50

int main(void)
{
	uint8_t counter = 0;
	
	//Set port D to output
	DDRD |= 0xff;
	// Pull whole PORTD to ground
	PORTD |= 0x00;
	
    while(1)
    {
		counter = 1;
		// Move dot left 
    	for(uint8_t i = 0; i < 7; i++)
	   	{
			PORTD = counter;
			counter <<= 1;
			_delay_ms(SWITCHING_TIME);
	   	}		   
    
		// Move dot right
		for(uint8_t i = 0; i < 7; i++)
		{
			PORTD = counter;
			counter >>= 1;
			_delay_ms(SWITCHING_TIME);
		}
	}
}