/*
 * _1507_timer_counter.cpp
 *
 * Created: 24.07.2015 13:36:04
 *  Author: User
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>


int x=1;

ISR (TIMER0_OVF_vect)					//обробник переривань по переповненню таймера.
	{
		x = x << 1;
		if (x>255)
		x=1;
		PORTD = x;
	}

int main(void)
{
	DDRD = 0xff;
	
	
	TCCR0 = (1<<CS00)|(1<<CS02);		//попереднє розділення частоти на 1024.
	TIMSK = (1<<TOIE0);					//переривання по переповненню таймера.					
    sei();								//загальний дозвіл переривань.
	
   while(1)
    {
       asm("nop");
	}	   
}