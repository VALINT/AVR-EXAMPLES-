/*
 * Measuring.c
 *
 * Created: 24.12.2017 12:34:02
 *  Author: VAL
 */ 
#include "Measuring.h"


uint16_t Measure(void)
{
	uint16_t help = 0b1000000000, voltage = 0;
	for(uint8_t tact = 0; tact < 10; tact ++)
	{
		PORTB = (voltage|help)>>2;
		PORTA = voltage|help;
		_delay_us(90);
		if(PIND & (1 << 6)){help >>= 1;}
		else{voltage |= help; help >>= 1;} 
	}
	PORTB = 0;
	return voltage;
}