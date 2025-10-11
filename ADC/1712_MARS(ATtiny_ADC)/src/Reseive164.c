/*
 * Reseive164.c
 *
 * Created: 08.12.2017 16:04:33
 *  Author: VAL
 */ 
#include "Reseive164.h"

void Clock();
uint8_t Replacement(uint8_t number);

// This function make clock pulse on tact input in shift register.
// Shift register shifts data on rising front
//____________________________________________________
void Clock()
{	asm("nop");DATA_PORT |= (1 << CLC);
	asm("nop");DATA_PORT &=~ (1 << CLC);
}
//////////////////////////////////////////////////////

// This function sent data byte to the shift register
//____________________________________________________	
void Sent_Number(uint8_t numb)
{uint8_t buffer;
	
	for(uint8_t byte_n = 0; byte_n < 8; byte_n ++)
	{if((numb & 0b00000001) == 1)
		{	DATA_PORT |= (1 << DATA);Clock();}
		else
		{	DATA_PORT &=~ (1 << DATA);Clock();}		
	numb = numb >> 1;
}}
//////////////////////////////////////////////////////

// This function fill seven-segment display on four signs
//____________________________________________________
void Fill_Display(float value)
{
	static uint8_t WholePart, FractionalPart, FirstDigit, SecondDigit, ThirdDigit, FourthDigit, MODE = 0;
	static float ValueBuffer;	
	ValueBuffer = value;
	WholePart = value;
	FractionalPart = (ValueBuffer - WholePart)*100;
	if(ValueBuffer < 10)
	{
		MODE = 0;
		FirstDigit = WholePart%10;
		SecondDigit = FractionalPart/10;
		ThirdDigit = FractionalPart%10;
	}
	else
	{
		MODE = 1;
		FirstDigit = WholePart/10;
		SecondDigit = WholePart%10;
		ThirdDigit = FractionalPart/10;
	}
	
	// First digit ()
	if(MODE == 0){Sent_Number((Replacement(FirstDigit))|0b00000010);}
	else {Sent_Number(Replacement(FirstDigit));}
	PORTD |= (1 << First_Digit);
	_delay_ms(2);
	PORTD &=~ (1 << First_Digit);
	asm("nop");	
	// Second digit 
	if(MODE == 1) {Sent_Number((Replacement(SecondDigit))|0b00000010);}
	else {Sent_Number(Replacement(SecondDigit));}
	PORTD |= (1 << Second_Digit);
	_delay_ms(2);
	PORTD &=~ (1 << Second_Digit);
	asm("nop");
	// Third digit
	Sent_Number(Replacement(ThirdDigit));
	PORTD |= (1 << Third_Digit);
	_delay_ms(2);
	PORTD &=~ (1 << Third_Digit);
	asm("nop");
}

uint8_t Replacement(uint8_t number)
{	switch (number){	
		case 0:return 0b11110101;break;
		case 1:return 0b00010100;break;
		case 2:return 0b11011001;break;
		case 3:return 0b01011101;break;
		case 4:return 0b00111100;break;
		case 5:return 0b01101101;break;
		case 6:return 0b11101101;break;
		case 7:return 0b01010100;break;
		case 8:return 0b11111101;break;
		case 9:return 0b01111101;break;
}}