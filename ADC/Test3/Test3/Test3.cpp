/*
 * Test3.cpp
 *
 * Created: 28.03.2018 23:44:26
 *  Author: VAL
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

int main(void)
{
	uint8_t measure = 0; 
	
	// ADC
	ADMUX |= (1 << REFS0);
	ADCSRB |= (1 << MUX5);
	ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1);
	
	//Timers
	TCCR1A |= (1 << WGM10)|(1 << COM1A1)|(1 << COM1B1)|(1 << COM1C1);
	TCCR1B |= (1 << CS11)|(1 << WGM12);
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;
	
	// I/O Ports
	DDRB = 0xFF;
	
	
    while(1)
    {
		ADMUX = 64;
        ADCSRA |= (1 << ADSC);
		_delay_ms(20);
		measure = (ADCW >> 2);
		OCR1A = measure;
	
		ADMUX = 65;
		ADCSRA |= (1 << ADSC);
		_delay_ms(20);;
		measure = (ADCW >> 2);
		OCR1B = measure;
	
		ADMUX = 66;
		ADCSRA |= (1 << ADSC);
		_delay_ms(20);
		measure = (ADCW >> 2);
		OCR1C = measure;
		
	
    }
}

/*
int main(void)
{
	int buffer = 0;
	uint8_t measure = 0;
	
	// ADC
	ADMUX |= (1 << REFS0);
	ADCSRB |= (1 << MUX5);
	ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1);
	
	//Timers
	TCCR1A |= (1 << WGM10)|(1 << COM1A1);
	TCCR1B |= (1 << CS11)|(1 << WGM12);
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;
	
	// I/O Ports
	DDRB = 0xFF;
	
	
	while(1)
	{
		ADCSRA |= (1 << ADSC);
		_delay_ms(10);
		buffer = ADCW ;
		measure = buffer >> 2;
		OCR1A = measure;
		_delay_ms(50);
	}
}*/