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
 
char x,y;
char line[15];
char line1[8];
int8_t Buttery[6][8] = {					//Батарейка
	{0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},
	{0x0E,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},
	{0x0E,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},
	{0x0E,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},
	{0x0E,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},
	{0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}
};

int8_t progress_bar1[7][8] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F},
	{0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F},
	{0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F},
	{0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F},
	{0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F},
	{0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}
};

int8_t progress_bar2[4][8] = {
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18},
	{0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C},
	{0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E}
};

int8_t Wireless[3][8] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10},
	{0x00,0x00,0x00,0x00,0x00,0x18,0x04,0x14},
	{0x00,0x00,0x00,0x1C,0x02,0x19,0x05,0x15},
};

int8_t Strelochka_Up[8][8] = {
	{0x00,0x00,0x00,0x04,0x0E,0x1F,0x0E,0x0E},
	{0x00,0x00,0x04,0x0E,0x1F,0x0E,0x0E,0x00},
	{0x00,0x04,0x0E,0x1F,0x0E,0x0E,0x00,0x00},
	{0x04,0x0E,0x1F,0x0E,0x0E,0x00,0x00,0x00},
	{0x0E,0x1F,0x0E,0x0E,0x00,0x00,0x00,0x00},
	{0x1F,0x0E,0x0E,0x00,0x00,0x00,0x00,0x00},
	{0x0E,0x0E,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};

int8_t Strelochka_Down[8][8] = {
	{0x0E,0x0E,0x1F,0x0E,0x04,0x00,0x00,0x00},
	{0x00,0x0E,0x0E,0x1F,0x0E,0x04,0x00,0x00},
	{0x00,0x00,0x0E,0x0E,0x1F,0x0E,0x04,0x00},
	{0x00,0x00,0x00,0x0E,0x0E,0x1F,0x0E,0x04},
	{0x00,0x00,0x00,0x00,0x0E,0x0E,0x1F,0x0E},
	{0x00,0x00,0x00,0x00,0x00,0x0E,0x0E,0x1F},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0E},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E},
};

int8_t Degrees[8] = {0x06,0x09,0x09,0x06,0x00,0x00,0x00,0x00};



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
	DDRD = 0xff;	
}
void sent_coordinats(int coloum,int line) //функція виставлення координат курсора
{
	int adres;
	adres = 0x40*line+coloum;
	adres |= 0x80;
	sent_byte(adres, COMAND);
	
}

void sent_line(char line[],int lon)
{
	for(int i = 0;i <= lon; i++)
	{
		if (line[i] == 192)line[i] = 65;	//А
		if (line[i] == 193)line[i] = 160;	//Б
		if (line[i] == 194)line[i] = 66;	//В
		if (line[i] == 195)line[i] = 161;	//Г
		if (line[i] == 196)line[i] = 224;	//Д
		if (line[i] == 197)line[i] = 69;	//Е
		if (line[i] == 198)line[i] = 163;	//Ж
		if (line[i] == 199)line[i] = 164;	//З
		if (line[i] == 200)line[i] = 165;	//И
		if (line[i] == 178)line[i] = 73;	//І
		if (line[i] == 201)line[i] = 166;	//Й
		if (line[i] == 202)line[i] = 75;	//К
		if (line[i] == 203)line[i] = 167;	//Л
		if (line[i] == 204)line[i] = 77;	//М
		if (line[i] == 205)line[i] = 72;	//Н
		if (line[i] == 206)line[i] = 79;	//О
		if (line[i] == 207)line[i] = 168;	//П
		if (line[i] == 208)line[i] = 80;	//Р
		if (line[i] == 209)line[i] = 67;	//С
		if (line[i] == 210)line[i] = 84;	//Т
		if (line[i] == 211)line[i] = 169;	//У
		if (line[i] == 212)line[i] = 170;	//Ф
		if (line[i] == 213)line[i] = 88;	//Х
		if (line[i] == 214)line[i] = 225;	//Ц
		if (line[i] == 215)line[i] = 171;	//Ч
		if (line[i] == 220)line[i] = 98;	//ь
		if (line[i] == 218)line[i] = 226;	//Щ
		if (line[i] == 222)line[i] = 220;	//Ш
		if (line[i] == 223)line[i] = 174;	//Ы
		if (line[i] == 174)line[i] = 176;	//Ю
		if (line[i] == 219)line[i] = 177;	//Я*/
		sent_char(line[i]);
	}
}

int main(void)
{
    initial_microkontroller();
	initial_LCD();
	clear_LCD();

int8_t Symbol[8] = {0x00,0x00,0x00,0x1C,0x02,0x19,0x05,0x15};

		
	sent_byte(0x40,COMAND);			//Выбираем адрес
	for (int i = 0;i < 8;i++)		//Цикл, передающий символ в память контроллера
	{
		sent_byte(Symbol[i],DATA);
	}
	sent_coordinats(0,0);			//Выставляем положение курсора
	sent_char(0);					//Выводим символ





}

