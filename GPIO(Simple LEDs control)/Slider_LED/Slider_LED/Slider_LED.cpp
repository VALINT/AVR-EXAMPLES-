/*
 * Slider_LED.cpp
 *
 * Created: 12.05.2015 3:43:07
 *  Author: VAL
 */ 

//Set MCU frequency
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	uint8_t counter = 0;
	
	//Set port D to output
	DDRD |= 0xff;
	PORTD |= 0x00;
	
    while(1)
    {
		counter = 1;
       for(uint8_t i = 0; i < 7; i++)
	   {
			 PORTD = counter;
			 counter <<= 1;
			 _delay_ms(300);
	   }		   
    
		 for(uint8_t i = 0; i < 7; i++)
		 {
			 PORTD = counter;
			 counter >>= 1;
			 _delay_ms(300);
		 }
	 }
	 
	/* while(1)
	 {
	
			 PORTD = counter;
			 counter ++;
			 _delay_ms(300);
		
	 }*/
}