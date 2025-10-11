/*
 * _1712_Pr_MARS_ATtiny_ADC.c
 *
 * Created: 08.12.2017 15:42:11
 *  Author: VAL
 */ 


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "Reseive164.h"
#include "Measuring.h"

int main(void)
{
	
	DDRD |= (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)|(1 << 5);
	DDRB |= 0xFF;
	DDRA |= (1 << 0)|(1 << 1);
	uint8_t multiplier = 3;
	if(PIND & (1 << 3)) multiplier = 10;
	
	
	if(PINA & ((0 << 1)&&(1 << 0)))multiplier = 2;
	if(PINA & ((0 << 1)&&(0 << 0)))multiplier = 1;
	float a = 0; 
    while(1)
    {
		for(uint8_t i = 0; i < 10; i++)
		{
			a = Measure()*0.004895*multiplier;
			Fill_Display(a);  
			 _delay_ms(10);
		}
		a = a + 0.1;	  
    }
}