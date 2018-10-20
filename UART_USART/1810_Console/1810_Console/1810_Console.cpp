/*
 * _1810_Console.cpp
 *
 * Created: 11.10.2018 22:28:37
 *  Author: VAL
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "standart_interface.hpp"
#include "terminal.hpp"


int main(){
	DDRB   = 0xff;
	DDRD = 0b11110000;
	char data = 32;
	
	uart_init();
	hi();
	while(1){
		data++;
		PORTD |= 0b11110000;
		if(!data) data = 32;

		PrintLn3("’оть ты и пидор но Symbol - %d %c", data, data);
		
		_delay_ms(400);
		PORTD &=~ 0b11110000;
		_delay_ms(200);
	}

	return 0;
}
