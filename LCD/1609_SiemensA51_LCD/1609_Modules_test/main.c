#define F_CPU 8000000UL


#include <math.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SiemensA55LCD.h"

char a [20]; 


void MCU_Init()														//Initialization MCU
{
	DDRD = 0xff;													//Set PORTD on output
	DDRB = 0xff;													//Set PORTB on output
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);						//setting SPI
	
	asm("sei");														//SREG = (1 << I), global interrapt is enable
}


int main(void)
{
	MCU_Init();
	LCD_Init();
	LCD_SCL();
	
	sprintf(a,"ÊÐÎÊÎÄÈËÇÀËÓÏÀÑÛÐ");
	LCD_Set_Cordinates(3,0);
	for(int part = 0; part < 20; part ++)
	{	
		LCD_print(a[part]);
	}
	while(1)
	{
		
	}
}


