/*
 * Test2.cpp
 *
 * Created: 28.03.2018 16:41:11
 *  Author: VAL
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

int main(void)
{
	uint8_t x = 1;
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	TCCR1A = (1 << WGM10)|(1 << COM1A1)|(1 << COM1B1)|(1 << COM1C1);
	TCCR1B = (1 << CS11)|(1 << WGM12);
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;
	DDRB = 0xFF;
    while(1)
    {
		for(uint8_t i = 0; i < 127; i ++)
        {OCR1A =  OCR1A+2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1B =  OCR1B+2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1A =  OCR1A-2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1C =  OCR1C+2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1B =  OCR1B-2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1A =  OCR1A+2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1C =  OCR1C-2;
		_delay_ms(50);}
		_delay_ms(1000);
		for(uint8_t i = 0; i < 127; i ++)
		{OCR1A =  OCR1A-2;
		_delay_ms(100);}
    }
}