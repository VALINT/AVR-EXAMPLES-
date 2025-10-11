#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char buf;


void initial(void);
void initial_Slave(void);

void initial(void)
{
	DDRD = 0xff;
	return;
}

void initial_Slave(void)
{
	DDRB = 0x00;
	SPCR = (1<<SPE)|(1<<SPIE);
	sei();
	return;
}

ISR(SPI_STC_vect)
{
	PORTD = SPDR;
}


int main(void)
{
	initial();
	initial_Slave();
	
    while (1) 
    {
		asm("nop");
		
    }
}

