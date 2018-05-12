/*
 * _1709_Pr_VENUS_VU_Meter_.c
 *
 * Created: 08.09.2017 11:59:35
 *  Author: VAL
 */ 
#define  F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <math.h>

#define LINE 1
#define LOG 0 
#define ToVoltage 0.00488
#define Left 0
#define Right 1
#define BAR 1
#define POINT 2
#define PEAK_YES 1
#define PEAL_NO 0
#define MEASURING_LEFT {ADMUX = 0b01000101;CHANNEL = Left;}
#define MEASURING_RIGHT {ADMUX = 0b01000100;CHANNEL = Right;}

const float LogDivArr[15] PROGMEM = {1, 1.4, 1.59, 1.79, 2, 2.24, 2.5, 2.82, 3.16, 3.57, 4.55, 6.25, 10, 20, 100};
const float LinDivArr[15] PROGMEM = {1, 1.07, 1.15, 1.25, 1.36, 1.5, 1.67, 1.86, 2.12, 2.5, 2.94, 3.65, 5, 7.04, 13.16};
const uint16_t LogScale[15] PROGMEM = {10, 51, 102, 163, 225, 286, 324, 363, 409, 457, 512, 572, 644, 731, 1023};
const uint16_t LineScale[15] PROGMEM = {77, 145, 204, 280, 348, 409, 483, 550, 613, 682, 752, 819, 890, 957, 1023};	
int Scale[15] = {0};
float Vmax = 180, TestEND = 0;
uint8_t Tact = 0, Mesure = 0, iter = 0, frame = 0, CHANNEL = 0;
uint16_t RightBar = 0, LeftBar = 0, BUFFER = 0, ENDL = 0, ENDR = 0, ADCLBuf = 0, ADCRBuf = 0, LeftPeak = 0, RiPeak = 0;

void BuildScale(uint8_t Type);
void MCUInitial(void);
uint16_t BuildBar(uint16_t buff, uint8_t type);
uint16_t CheckPeak(uint16_t data, uint16_t peak);


int main(void)
{
	MCUInitial();
	BuildScale(LOG);
    while(1)
    {
		LeftBar = BuildBar((ADCLBuf), BAR);
		if(ENDL < LeftBar)
			ENDL = LeftBar;
		else if(ENDL > LeftBar)
			ENDL >>= 1;
        PORTD = ENDL;
		PORTB = 0b00000000 | ENDL >> 8;
		PORTB |= (ENDL >> 8);
		PORTB |= 0b01000000;
		Mesure = 0;
		ADCRBuf = 0;
		ADMUX &=~ (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3);
		ADMUX |= (1 << MUX2)|(1 << MUX0);
		CHANNEL = Left;
		_delay_ms(9);
		RightBar = BuildBar((ADCRBuf), BAR);
		
		if(ENDR < RightBar)
			ENDR = RightBar;
		else if(ENDR > RightBar)
			ENDR >>= 1;
		PORTD = ENDR;
		PORTB = 0b00000000 | ENDR >> 8;
		PORTB |= 0b10000000;
		Mesure = 0;
		ADCLBuf = 0;
		ADMUX &=~ (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3);
		ADMUX |= (1 << MUX2);
		CHANNEL = Right;
		_delay_ms(9);
		
    }
}

ISR(TIMER0_OVF_vect)
{
	if(CHANNEL == Left)
	{
		if(ADCW > ADCLBuf)
		ADCLBuf = ADCW;

	}	
	if(CHANNEL == Right)
	{
		if(ADCW > ADCRBuf)
		ADCRBuf = ADCW;
		
	}	
		ADCSRA |= (1 << ADSC);	
		
		// Bullshit
		//ADCLBuf += ADCW;
		//if(Mesure == 14)
		//{LeftBar = BuildBar((ADCLBuf / 14), BAR); ADCLBuf = 0; Mesure = 0;}
		//Mesure++;
}

void BuildScale(uint8_t Type)
{
	float buffer;
	for(uint8_t i = 0; i < 15; i++)
	{
		if(Type == LOG)
		{buffer = pgm_read_float_near(&(LogDivArr[i]));}
		if(Type == LINE)
		{buffer = pgm_read_float_near(&(LinDivArr[i]));}
		
		Scale[i] = Vmax/buffer;
	}
}

void MCUInitial(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x00;
	
	TCCR0 |= (1 << CS01);//|(1 << CS00);					// Prescaler 64
	TIMSK |= (1 << TOIE0);								// Enable overflow interruption
	
	ADMUX |= (1 << REFS0)|(1 << MUX2)|(1 << MUX0);		// V ref 5V (?), ADC 5
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);			//ADC Enable, Frequency division 64 
	ADCSRA |= (1 << ADFR);								//Start conversion
	
	asm("sei");											//Enable global interruptions
}

uint16_t BuildBar(uint16_t buff, uint8_t type)
{
	
	
	uint16_t Bar = 0;
	// Algorithm build bar before it`s be show 
	// 
	if(type == BAR)
	{
		for(uint8_t i = 0; i < 15; i ++)
		{
			if(buff > Scale[14-i])
			(Bar |= 0b1 << i);
			else
			break;
		}
	}
	else if(type == POINT)	
	{
		Bar = 1;
		for(uint8_t i = 0; i < 15; i ++)
		{
			if(buff > Scale[14-i])
			(Bar <<= 1);
			else
			break;
		}
	}
	return Bar;
}

uint16_t CheckPeak(uint16_t data, uint16_t peak)
{
	if(data > peak)
	{
		peak = 1;
		for(uint8_t i = 0; i < 15; i ++)
		{
			if(data > Scale[14-i])
			(peak <<= 1);
			else
			break;
		}
		return peak;
	}
/*	else if((iter > 750)&&(data < peak))
	{
		peak >>= 1;
		iter = 0;
		return peak;
	}
	iter++;*/
}