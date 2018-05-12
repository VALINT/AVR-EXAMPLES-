#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define RW PD0
#define E PD1
#define D4 PD4
#define D5 PD5
#define D6 PD6
#define D7 PD7
#define LCD_E_SET PORTD |= 0b00000001;
#define LCD_E_CLR PORTD &= 0b11111110;
#define LCD_RS_SET PORTD |= 0b00000010;
#define LCD_RS_CLR PORTD &= 0b11111101;
#define LCD_data 1
#define LCD_comand 0
#define LCD_Port PORTD

void LCD_fourbite(char data);
void LCD_Write(char data,int flag);

void lcd_gotoxy(char col, char row)
{
	char adr;
	adr=0x40*row+col;
	adr|=0x80;
	LCD_Write(adr, LCD_comand);
}

void LCD_Init()
{
	_delay_ms(30);
	LCD_fourbite(0b00000011);
	_delay_ms(4);
	LCD_fourbite(0b00000011);
	_delay_us(100);
	LCD_fourbite(0b00000011);
	_delay_ms(1);
	LCD_fourbite(0b00000010);
	_delay_ms(1);
	LCD_Write(0x28,LCD_comand);
	_delay_ms(1);
	LCD_Write(0x0C,LCD_comand);
	_delay_ms(1);
	LCD_Write(0x06,LCD_comand);
	_delay_ms(1);	
}


void LCD_fourbite(char data)
{
	data <<=4;
	LCD_E_SET;
	_delay_us(50);
	LCD_Port &= 0x0F;
	LCD_Port |= data;
	LCD_E_CLR;
	_delay_us(50);
}


void LCD_Write(char data,int flag)
{
	char high_data = 0;
	high_data = data >> 4;
	if(flag == LCD_comand) {LCD_RS_CLR;}
	else                   LCD_RS_SET;
	LCD_fourbite(high_data);
	LCD_fourbite(data); 
	
}

void MCU_Init()
{
	DDRD = 0xff;
	_delay_ms(50);
	LCD_Init();
}



int main(void)
{
	MCU_Init();
	LCD_Init();
	lcd_gotoxy(0,0);
    while(1)
    {
         LCD_Write(65,LCD_data);
    }
}