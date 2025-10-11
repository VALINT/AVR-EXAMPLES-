/*
 * _1507_Timer_Counter1.cpp
 *
 * Created: 26.07.2015 21:51:39
 *  Author: User
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

int x=0,sec = 0,hour = 0,min = 0,seg = 0,PBT = 0,star = 0,
timer_hour = 0,timer_min = 0,timer_sec = 0,al_hour = 0,al_min = 0,menu = 0,alarm_c = 0,
timer = 0,T_V_M = 0;

int symbol (int sym)				// Функція виводу символа на семисегментний індикатор
{
	switch (sym)
	{
		case 0:
		PORTD = 0b00111111;			//(0)
		break;
		case 1:
		PORTD = 0b00001001;			//(1)
		break;
		case 2:
		PORTD = 0b01011110;			//(2)
		break;
		case 3:
		PORTD = 0b01011011;			//(3)
		break;
		case 4:
		PORTD = 0b01101001;			//(4)
		break;
		case 5:
		PORTD = 0b01110011;			//(5)
		break;
		case 6:
		PORTD = 0b01110111;			//(6)
		break;
		case 7:
		PORTD = 0b00011001;			//(7)
		break;
		case 8:
		PORTD = 0b01111111;			//(8)
		break;
		case 9:
		PORTD = 0b01111011;			//(9)
		break;
	}
	return(sym);
}




ISR (TIMER2_OVF_vect)				//Обробник переривання таймера 2.
{
	x++;
	if(x > 127)
	{
		x = 0;
		sec++;
	}	
	if(sec > 59)
		{
			sec = 0;
			min++;
		}		
	if(min > 59)
		{
			min=0;
			hour++;
		}		
	if(hour > 23)
			hour=0;
	if (alarm_c == 1)
	{
		if ((hour == al_hour)|(min == al_min))
		{
			alarm_c = 0;
		}
	}			
	
	if (timer == 1)
	{
		timer_sec --;
		if(timer_sec < 0)
		{
			timer_min --;
			timer_sec = 59;
		}
		if (timer_min < 0)
		{
			timer_min = 59;
			timer_hour --;
		}
		if ((timer_hour == 0)|(timer_min == 0))
			timer = 0;						
	}
	
	
	
}

ISR (TIMER0_OVF_vect)				//Обробник переривання таймера 0
{
	PORTC = 0x00;
	
	if (alarm_c == 1)
	{
		PORTB = (1 << PB0);
	}
	
	int hour_dec,hour_uni,min_dec,min_uni;
	
	
	if ((menu == 0)|(menu == 1))
	{
		if (T_V_M == 0)
		{
			hour_dec = hour/10;
			hour_uni = hour%10;
			min_dec = min/10;
			min_uni = min%10;
			
		}
		else
		{
			hour_dec = min/10;
			hour_uni = min%10;
			min_dec = sec/10;
			min_uni = sec%10;
		}		
	
	}	
	if (menu == 2)
	{
		hour_dec = al_hour/10;
		hour_uni = al_hour%10;
		min_dec = al_min/10;
		min_uni = al_min%10;
	}
	if (menu == 3)
	{
		hour_dec = timer_hour/10;
		hour_uni = timer_hour%10;
		min_dec = timer_min/10;
		min_uni = timer_min%10;
	}
	
	
	seg++;
	if(seg == 5)
	seg = 1;
	
	switch (seg)
	{
		case 1:
		symbol(hour_dec);
		PORTC = 0x08;
		break;
		
		case 2:
		symbol(hour_uni);
		PORTC = 0x04;
		break;
		
		case 3:
		symbol(min_dec);
		PORTC = 0x02;
		break;
		
		case 4:
		symbol(min_uni);
		PORTC = 0x01;
		break;
	}
}

void start (void)
{
		DDRD = 0xff;
		DDRC = 0xff;
		DDRB = 0b10001111;
		
		
		ASSR = (1<<AS2);								//Переведення таймера 2 в асинхронний режим, для тактування від зовнішнього кварцу на 32,768 МГц
		TCNT2 = 0x00;
		OCR2 = 0x00;
		TCCR2 = (1<<CS20);								//Налаштування без попереднього розділення частоти для таймера 2.
		TCCR0 = (1<<CS01)|(1<<CS00);					//Налаштування без попереднього розділення частоти для таймера 0.
		TIMSK = (1<<TOIE2)|(1<<TOIE0);					//Дозвіл на переривання від таймерів 2 і 0.
			
			
		sei();
		
		star = 1;
}

int main(void)
{
	if(star == 0)
	   start();

    while(1)						//опитування тактових кнопок
    {
		switch(menu)
		{
			case 0:
				if (PINB & (1 << PB1))
				{
					_delay_ms(1000);
					if (alarm_c == 0)
					alarm_c = 1;
					else alarm_c = 0;
				}
				if (PINB & (1 << PB2))
				{
					_delay_ms(1000);
					menu = 1;
				}					
				if (PINB & (1 << PB3))
				{
					_delay_ms(2000);
					if (T_V_M == 0)
					T_V_M = 1;
					else T_V_M = 0;
				}
				break;
			case 1:
				if (PINB & (1 << PB1))
				{
					_delay_ms(2000);
					hour ++;
				}					
				if (PINB & (1 << PB2))
				{
					_delay_ms(2000);
					menu = 2;
				}					
				if (PINB & (1 << PB3))
				{	
					_delay_ms(2000);
					min++;
				}		
				break;			
			case 2:
				if (PINB & (1 << PB1))
				{
					_delay_ms(2000);
					al_hour ++;
					if (al_hour > 23)
						al_hour = 0;
				}						
				if (PINB & (1 << PB2))
				{
					_delay_ms(2000);
					menu = 3;
				}					
				if (PINB & (1 << PB3))
				{
					_delay_ms(2000);
					al_min ++;
					if (al_min > 59)
						al_min = 0;
				}		
				break;				
			case 3:
				if (PINB & (1 << PB1))
				{
					_delay_ms(2000);
					timer_hour ++;
					if (timer_hour > 99)
						timer_hour = 0;
				}						
				if (PINB & (1 << PB2))
				{
					_delay_ms(2000);
					if ((timer_hour == 0)|(timer_min == 0))
						menu = 0;
				}		
				else {timer = 1;menu = 0;}
				if (PINB & (1 << PB3))
				{
					_delay_ms(2000);
					timer_min ++;
					if (timer_min > 59)
					timer_min = 0;	
				}				
							
						
				if (menu > 3)
				menu = 0;
				break;
		}			
						
    }
}