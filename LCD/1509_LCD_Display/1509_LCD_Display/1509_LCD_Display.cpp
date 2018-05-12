#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
 
// ��������� ���. "1" �� ����� E 
#define LCD_E_SET    PORTD|=0x02
/* ��������� ���. "0" �� ����� E */
#define LCD_E_CLR    PORTD&=0xFD
/* ��������� ���. "1" �� ����� RS */
#define LCD_RS_SET   PORTD|=0x01
/* ��������� ���. "0" �� ����� RS */
#define LCD_RS_CLR   PORTD&=0xFE
 
/* ������, ����������� �������, ���
���������� ������� */
#define LCD_COMMAND  0
/* ������, ����������� �������, ���
���������� ������ */
#define LCD_DATA     1
 
#define lcd_putc(x)  lcd_putbyte(x, LCD_DATA)
 
 int adc,out;
 
 void initialization ()
 {
	 //����������� ���
	 ADMUX = (1 << REFS0); //������ ������� 5�/�������� ���� ���0
	 ADCSRA |= (1<<ADEN)  | (1<<ADIE) | (1<<ADPS0)| (1<<ADSC);
	 //��������� �������� �����������
	sei();
	 
 }
 
 
/* ������������� ������,
������������ � ��� */
void init_port()
{
	PORTB=0x00;
	DDRB=0x00;
    PORTD=0x00;
    DDRD=0xFF;
}
 
/* ������� �������� ������� � ��� */
void lcd_putnibble(char t)
{
    t<<=4;
    LCD_E_SET;
    _delay_us(50);
    PORTD&=0x0F;
    PORTD|=t;
    LCD_E_CLR;
    _delay_us(50);
}
 
/* ������� �������� ����� � ���.
char c - ��� ����
char rs - ����������, ����������� ��� ����������:
     rs = 0 - ������� (��������������� ����� RS)
	 rs = 1 - ������ (������������ ����� RS) */
void lcd_putbyte(char c, char rs)
{
    char highc=0;
    highc=c>>4;
	if (rs==LCD_COMMAND) LCD_RS_CLR;
	else                 LCD_RS_SET;
    lcd_putnibble(highc);
    lcd_putnibble(c);
}
 
void lcd_putchar(char c)
{
    char highc=0;
    highc=c>>4;
	LCD_RS_SET;
    lcd_putnibble(highc);
    lcd_putnibble(c);
}
 
/* ������� ������������� ������ ���
� 4-������ ������, ��� ������� */
void lcd_init()
{
    _delay_ms(15);
    lcd_putnibble(0b00000011);
    _delay_ms(4);
    lcd_putnibble(0b00000011);
    _delay_us(100);
    lcd_putnibble(0b00000011);
	 _delay_ms(1);
    lcd_putnibble(0b00000010);
	_delay_ms(1);
    lcd_putbyte(0x28, LCD_COMMAND);
    _delay_ms(1);
    lcd_putbyte(0x0C, LCD_COMMAND);
    _delay_ms(1);
    lcd_putbyte(0x06, LCD_COMMAND);
    _delay_ms(1);
}
 
/* ������� ������� ������� � ��������
������� � ��������� �������*/
void lcd_clear()
{
    lcd_putbyte(0x01, LCD_COMMAND);
    _delay_us(1500);
}
 
/* ������� ����������� ������� � �������� �������
col - ����� ���������� �� �������������� ��� (�� 0 �� 15)
row - ����� ������ (0 ��� 1) */
void lcd_gotoxy(char col, char row)
{
  char adr;
  adr=0x40*row+col;
  adr|=0x80;
  lcd_putbyte(adr, LCD_COMMAND);
}
 
void lcd_putstring (char stroka[])
{  char i;
   for(i=0;stroka[i]!='\0';i++)
   lcd_putchar(stroka[i]);
}	
 
ISR (ADC_vect)   //������ ����������� ���
{
	adc = ADCW;
}
 
 
int main(void)
{
	lcd_init();
	initialization();
	
	
	while (1)
	{
		lcd_clear();
		_delay_ms(5);
		if(adc > 5){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 15){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 30){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 45){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 60){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 75){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 90){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		if(adc > 105){
			lcd_gotoxy(0,0);
			lcd_putchar(255);
		_delay_ms(2);}
		ADCSRA |= (1 << ADSC);
	}
	
}
