/*
 * Blink_LED.cpp
 *
 * Created: 12.05.2015 3:10:39
 *  Author: VAL
 */ 

//Set MCU frequency
//#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//Set port D to output
	DDRD |= 0xff;
	PORTD |= 0x00;
	
    while(1)
    {
       PORTD |= (1 << 1);
	   _delay_ms(400);
	   PORTD &=~ (1 << 1);
	   _delay_ms(400);
    }
}