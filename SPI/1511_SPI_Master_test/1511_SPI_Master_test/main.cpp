#define F_CPU 8000000UL

#include <avr/io.h>
#include "symbol.h"
#include <util/delay.h>
#include <avr/interrupt.h>

//Оголошення прототипів
void initial(void);
void initial_master(void);
int press_button_please(int);
unsigned char send_out_the_signal(char data);

//Оголошення змінних
int digit,
B_C1,B_C2,B_C3, 
B_P,
B_P_N,
d,R,G,B;

//Функція ініціалізації Master SPI
void initial_master(void)
{
	DDRB = 0xff;													// Налаштовуємо порт Б на вихід (для налаштування SPI )
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR1)|(1 << SPR0);			// Вмикаємо SPI, Налаштовуємо даний пристрій, як головний, частота передачі Ф/128
	return;
}
//Функція ініціалізації периферії мікроконтролера
void initial(void)
{
	DDRC = 0b00110000;	//Налаштовуємо порт C на вхід
	PORTC = 0x00;
	DDRD = 0xff;
	PORTD = 0x00;
	
	TCCR0 = (1<<CS01);					//Налаштування розділення нa 64 частоти для таймера 0.
	TIMSK = (1<<TOIE0);					//Дозвіл на переривання від таймерів 2 і 0.
	
	sei();
		return;											
}
//Функція передачі даних
unsigned char send_out_the_signal(int data)
{
	//початок передачі
	SPDR = data;
	//очікуємо завершення передачі
	while(!(SPSR & (1<<SPIF))) ;									//Перевіряємо стан 
	return SPDR; //повертаємо, прийнятий байт
}



int press_button_please(int button) //Функція обробки кнопок
{
	switch(button)
	{
		case 0:
		B_P = 0;
		B_C1 = 0;
		B_C2 = 0;
		B_C3 = 0;
		break;
		
		case 1:
		B_C1++;
		if (B_C1 == 100)
		{
			if(B_C1 == 130)
			{B_C1 = 125;}
			B_C2 = 0;
			B_C3 = 0;
			R++;
			if (R > 1)
			{R = 0;}
		}
		break;

		case 2:
		B_C2++;
		if (B_C2 == 100)
		{
			if(B_C2 == 130)
			{B_C2 = 125;}
			B_C1 = 0;
			B_C3 = 0;
			G++;
			if (G > 1)
			{G = 0;}
		}
		break;
		
		case 3:
		B_C3++;
		if (B_C3 == 100)
		{
			if(B_C3 == 130)
			{B_C3 = 125;}
			B_C1 = 0;
			B_C2 = 0;
			B++;
			if (B > 1)
			{B = 0;}
		}
		break;	
	}

}

ISR (TIMER0_OVF_vect)             //Функція обробки переривання таймера0(для динамічної індикації і опитування кнопок)
{
	//Виведення інформації на семисегментні індикатори
	PORTB = 0x00;
	digit++;
	
	if (digit == 3)
	{digit = 0;}
	
    switch(digit)
	{
		case 0:
		symbol(R);
		PORTB |= 0b10000000;
		break;
		
		
		case 1:
		symbol(G);
		PORTB |= 0b01000000;
		break;
		
		
		case 2:
		symbol(B);
		PORTB |= 0b00000001;
		break;
	}

//Опитування кнопок
	
	if(PINC & (1 << PC0))
	{
		if (B_P == 0)
		{
			B_P = 1;
		}
		B_P_N = 1;
		if (B_P == 1)
		{
			press_button_please(1);
		}
	}
	if(PINC & (1 << PC1))
	{
		if (B_P == 0)
		{
			B_P = 2;
		}
		B_P_N = 1;
		if (B_P == 2)
		{
			press_button_please(2);
		}
	}
	if(PINC & (1 << PC2))
	{
		if (B_P == 0)
		{
			B_P = 3;
		}
		B_P_N = 1;
		if (B_P == 3)
		{
			press_button_please(3);
		}
	}
	if (B_P_N == 1)
	{
		B_P_N = 0;
	} 
	else
	{
		press_button_please(0);
	}
	
	d = 0b11111111;
	if (R == 1)
	{
		d &= 0b11111111;
	}
	else
	{
		d &= 0b11111110;
	}
	if (G == 1)
	{
		d &= 0b11111111;
	}
	else
	{
		d &= 0b11111101;
	}
	if (B == 1)
	{
		d &= 0b11111111;
	}
	else
	{
		d &= 0b11111011;
	}
	
	send_out_the_signal(d); 
}

int main(void)
{
	initial();
	initial_master();
    while (1) 
    {
		
		/*
		d = R + B + G;
		send_out_the_signal(d); */
    }
}

