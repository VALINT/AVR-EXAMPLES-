/*
 * Buttons.cpp
 *
 * Created: 12.05.2018 3:33:37
 *  Author: VAL
 */ 

//Set MCU frequency
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	uint8_t counter = 1;
	
	//Set port D to output
	DDRD = 0xff;
	PORTD = 0x00;
	
	//Set port C to input
	DDRC = 0x00;
	PORTD = 0x00;
	
    while(1)
    {
		if(PINC &(1 << PC0))
			if(counter == 128) counter = 1;
			else counter <<= 1;
		
		if(PINC &(1 << PC1))
			if(counter == 1) counter = 128;
			else counter >>= 1;
		
		(counter == 0) ? counter = 1:counter = counter; 
		_delay_ms(300);
		
		PORTD = counter;
     
	 }
	 
	/* while(1)
	 {
	
			 if(PINC &(1 << PC0)) counter++;
			 
			 if(PINC &(1 << PC1)) counter--;
			 
			 PORTD = counter;
			 
			 _delay_ms(300);
		
	 }*/
}