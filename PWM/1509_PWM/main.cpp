/*
 * _1509_PWM.cpp
 *
 * Created: 01.09.2015 16:35:51
 *  Author: User
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

int pwm1 = 1,pwm2 = 1,pwm3 = 1;
double p,x = 0;


void PWM_Init(void)													//Функція ініціалізації трьох ШІМ каналів
{
	TCCR1A = (1 << WGM10)|(1 << COM1A1)|(1 << COM1B1);				//
	TCCR1B = (1 << CS11)|(1 << WGM12);								//Налаштовую Fast PWM 8bit для двох каналів таймера 1
	TCCR2 = (1 << WGM20)|(1 << WGM21)|(1 << CS20)|(1 << COM21);					//Налаштовую Fast PWM 8bit для таймера 2
	OCR1A = 0;														//Початкове значення довжини імпульсу для А каналу таймера 1
	OCR1B = 0;														//Початкове значення довжини імпульсу для Б каналу таймера 1
	OCR2 = 0;														//Початкове значення довжини імпульсу для таймера 2
	DDRB = 0xff;
}

int main(void)
{
	PWM_Init();
	DDRD = 0x00;
	PORTD = 0x00;
	
	
	while (1)
	{
		if (PIND & (1 << PD0))
		{
			OCR1A = OCR1A + 5;
			_delay_ms(200);
		}
		if (PIND & (1 << PD1))
		{
			OCR1A = OCR1A - 5;
			_delay_ms(200);
		}						
		if ( PIND & (1 << PD2))
		{
			OCR2 = OCR2 + 5;
			_delay_ms(200);
		}			
	}
		}
/*	while(1)
	{
		OCR2 = OCR2 + 2;
		if(OCR1A == 0)
		pwm1 = 1;
		if(OCR1A >= 254)
		pwm1 = 0;
		if (pwm1 == 0)
		{
			OCR1A--;
			_delay_ms(200);
		}
		if (pwm1 == 1)
		{
			OCR1A ++;
			_delay_ms(200);
		}
	}

while(1)
{
	for (int r = 0; r < 254;r++)
		{
			OCR1A++;
			_delay_ms(160);
		}
	for (int g = 0; g < 254;g++)
		{
			OCR1B++;
			_delay_ms(100);
		}
	for (int b = 0; b < 254; b++)
		{
			OCR2++;
			_delay_ms(160);
		}
		for (int r = 254; r > 0;r--)
		{
			OCR1A--;
			_delay_ms(160);
		}
		for (int g = 254; g > 0;g--)
		{
			OCR1B--;
			_delay_ms(160);
		}
		for (int b = 254; b > 0; b--)
		{
			OCR2--;
			_delay_ms(160);
		}*/
