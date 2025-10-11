#define  F_CPU 8000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RS PD0
#define RW PD1
#define SET_RS_TO_1 PORTD|=(0b00000001)
#define SET_RS_TO_0 PORTD&=(0b11111110)
#define E PD2
#define SET_E_TO_1 PORTD|=(0b00000010)	 //Встановлення Е в 1
#define SET_E_TO_0 PORTD&=(0b11111101)	 //Встановлення Е в 0
#define LCD_PORT PORTD
#define COMAND 0
#define DATA 1
 
int sec,min = 59,hour = 23,data,data1,a;
char x;
char line[15];

int numb0[6][8] = {
	{0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F},
	{0x1F,0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F},
	{0x00,0x00,0x0D,0x1F,0x1F,0x1F,0x0D,0x00},
	{0x00,0x00,0x11,0x0A,0x04,0x0A,0x11,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},			
	};


void sent_four_bits(char data)           //Функція, для передачі в РКІ чотирьох біт(використовується при чотирьохбітному режимі передачі даних)
{
	data <<=4;							 //Зсуваємо біт на 4 значення в сторону старшого(на дисплей передаються біти 7.6.5.4)
	SET_E_TO_1;							 //Е встановлюється в 1 - початок передачі тетради
	_delay_us(50);
	LCD_PORT&=(0b00001111);
	LCD_PORT|=data;
	SET_E_TO_0;							 //Е встановлюється в 0 - запис тетради в РКІ
	_delay_us(50);
}

void sent_byte(char byte,char rs)		 //Функція для передачі байту в РКІ
{
	char highbyte = 0;				
	highbyte = byte>>4;					 //Розділення байта на старшу і молодшу половину
	if (rs == COMAND)SET_RS_TO_0;		 //Вибір даних що передаватимуться (команда / дані)
		else SET_RS_TO_1;				 //РС = 0 - комнда РС = 1 - дані
	sent_four_bits(highbyte);			 //передача старшої і молодшої частини байта, послідовно
	sent_four_bits(byte);
}

void sent_char(char data)				 //Функція, що відправляє в РКІ байт даних
{
	char highbyte = 0;
	highbyte = data>>4;					 
	SET_RS_TO_1;				 
	sent_four_bits(highbyte);			 
	sent_four_bits(data);
}

void initial_LCD()						 //Функція ініціалізації РКІ
{
	_delay_ms(20);							//----------------------------------
	sent_four_bits(0b00000011);				//  Початкова ініціалізація
	_delay_ms(5);							//	за вказаним в datasheet порядком
	sent_four_bits(0b00000011);				//
	_delay_us(100);							//
	sent_four_bits(0b00000011);				//
	 _delay_ms(1);							//
	sent_four_bits(0b00000010);				//
	 _delay_ms(1);							//
	 sent_byte(0b00101100, COMAND);			//	
	 _delay_ms(1);							//
	 sent_byte(0b00001100, COMAND);			//
	 _delay_ms(1);							//
	 sent_byte(0b00000001, COMAND);			//
	 _delay_ms(1);							//
	 sent_byte(0b00000110, COMAND);			//
	 _delay_ms(1);							//------------------------
}

void clear_LCD()						//Функція очистки дисплея
{
	_delay_ms(1);
	sent_byte(0b00000001, COMAND);		//команда очистки дисплея
	_delay_ms(2);
}

void initial_microkontroller()			//функція ініціалізації мікроконтролера
{
//	Налаштування портів
//-------------------------------------------------------------------------------------------------------------------------------------
	DDRD = 0xff;	
//  Налаштування таймерів
//---------------------------------------------------------------------------------------------------------------------------------------
	ASSR = (1<<AS2);								//Переведення таймера 2 в асинхронний режим, для тактування від зовнішнього кварцу на 32,768 КГц
	TCNT2 = 0x00;
	OCR2 = 0x00;
	TCCR2 = (1<<CS21);								//Налаштування без попереднього розділення частоти для таймера 2.
	TCCR0 = (1<<CS02);								//Налаштування без попереднього розділення частоти для таймера 0.
	TIMSK = (1<<TOIE2)|(1<<TOIE0);					//Дозвіл на переривання від таймерів 2 і 0.

	sei();
}

void sent_coordinats(int coloum,int line) //функція виставлення координат курсора
{
	int adres;
	adres = 0x40*line+coloum;
	adres |= 0x80;
	sent_byte(adres, COMAND);
	
}

void sent_line(char line[])
{
	for(int i = 0;i <= 15; i++)
	{
		sent_char(line[i]);
	}
}

void print (int numb, int coordinat)
{
	switch (numb)
	{
		case 0:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(0);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(255);
		sent_char(1);
		sent_char(255);
		break;
		
		case 1:
		sent_coordinats(coordinat,0);
		sent_char(5);
		sent_char(255);
		sent_char(5);
		sent_coordinats(coordinat,1);
		sent_char(5);
		sent_char(255);
		sent_char(5);
		break;
		
		case 2:
		sent_coordinats(coordinat,0);
		sent_char(0);
		sent_char(0);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(255);
		sent_char(2);
		sent_char(2);
		break;
		
		case 3:
		sent_coordinats(coordinat,0);
		sent_char(2);
		sent_char(2);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(1);
		sent_char(1);
		sent_char(255);
		break;
		
		case 4:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(1);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(5);
		sent_char(5);
		sent_char(255);
		break;
		
		case 5:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(2);
		sent_char(2);
		sent_coordinats(coordinat,1);
		sent_char(1);
		sent_char(1);
		sent_char(255);
		break;
		
		case 6:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(2);
		sent_char(2);
		sent_coordinats(coordinat,1);
		sent_char(255);
		sent_char(1);
		sent_char(255);
		break;
		
		case 7:
		sent_coordinats(coordinat,0);
		sent_char(0);
		sent_char(0);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(5);
		sent_char(5);
		sent_char(255);
		break;
		
		case 8:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(2);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(255);
		sent_char(1);
		sent_char(255);
		break;
		
		case 9:
		sent_coordinats(coordinat,0);
		sent_char(255);
		sent_char(2);
		sent_char(255);
		sent_coordinats(coordinat,1);
		sent_char(1);
		sent_char(1);
		sent_char(255);
		break;
		
		case 10:
		sent_coordinats(coordinat,0);
		sent_char(5);
		sent_char(5);
		sent_char(5);
		sent_coordinats(coordinat,1);
		sent_char(5);
		sent_char(5);
		sent_char(5);
		break;
	}
}

ISR (TIMER2_OVF_vect)				//Обробник переривання таймера 2.
{
	x++;
	if(x > 15)
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
}

ISR (TIMER0_OVF_vect)
{
	if (a == 0)
	{
		a++;
		initial_LCD();
		_delay_ms(1);
		sent_byte(0x40,COMAND);
		for (int i=0; i < 6; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				data = numb0[i][j];
				sent_byte(data,DATA);
			}
		}
	}
	
	int hour_high,hour_low,min_high,min_low;
	
	hour_high = hour/10;
	hour_low = hour%10;
	min_high = min/10;
	min_low = min%10;

	if(hour_high > 0)
	print(hour_high,0);
	else print(10,0);
	print(hour_low,4);
	
	print(min_high,8);
	print(min_low,12);
	
	sent_coordinats(16,0);
	sprintf(line,"%d",(sec));
	sent_line(line);
	
	if (x == 8)
	{
		sent_coordinats(7,0);
		sent_char(4);
		sent_coordinats(7,1);
		sent_char(4);
	}
	if (x == 0)
	{
		sent_coordinats(7,0);
		sent_char(5);
		sent_coordinats(7,1);
		sent_char(5);		
	}
}

int main(void)
{
	initial_microkontroller();
    _delay_ms(100);
	initial_LCD();
	_delay_ms(100);
	clear_LCD();
	_delay_ms(100);
	sent_byte(0x40,COMAND);
	for (int i=0; i < 6; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			data = numb0[i][j];
			sent_byte(data,DATA);
		}
	}
	
	
	while(1)
	{
	}
}
	
