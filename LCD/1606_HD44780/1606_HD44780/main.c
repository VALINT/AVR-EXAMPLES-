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
#define SET_E_TO_1 PORTD|=(0b00000010)	 //������������ � � 1
#define SET_E_TO_0 PORTD&=(0b11111101)	 //������������ � � 0
#define LCD_PORT PORTD
#define COMAND 0
#define DATA 1
 
char x,y;
char line[15];
char line1[8];
int8_t Buttery[6][8] = {					//���������
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



void sent_four_bits(char data)           //�������, ��� �������� � �ʲ �������� ��(��������������� ��� �������������� ����� �������� �����)
{
	data <<=4;							 //������� �� �� 4 �������� � ������� ��������(�� ������� ����������� ��� 7.6.5.4)
	SET_E_TO_1;							 //� �������������� � 1 - ������� �������� �������
	_delay_us(50);
	LCD_PORT&=(0b00001111);
	LCD_PORT|=data;
	SET_E_TO_0;							 //� �������������� � 0 - ����� ������� � �ʲ
	_delay_us(50);
}

void sent_byte(char byte,char rs)		 //������� ��� �������� ����� � �ʲ
{
	char highbyte = 0;				
	highbyte = byte>>4;					 //��������� ����� �� ������ � ������� ��������
	if (rs == COMAND)SET_RS_TO_0;		 //���� ����� �� ���������������� (������� / ���)
		else SET_RS_TO_1;				 //�� = 0 - ������ �� = 1 - ���
	sent_four_bits(highbyte);			 //�������� ������ � ������� ������� �����, ���������
	sent_four_bits(byte);
}

void sent_char(char data)				 //�������, �� ��������� � �ʲ ���� �����
{
	char highbyte = 0;
	highbyte = data>>4;					 
	SET_RS_TO_1;				 
	sent_four_bits(highbyte);			 
	sent_four_bits(data);
}

void initial_LCD()						 //������� ����������� �ʲ
{
	_delay_ms(20);							//----------------------------------
	sent_four_bits(0b00000011);				//  ��������� �����������
	_delay_ms(5);							//	�� �������� � datasheet ��������
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

void clear_LCD()						//������� ������� �������
{
	_delay_ms(1);
	sent_byte(0b00000001, COMAND);		//������� ������� �������
	_delay_ms(2);
}
void initial_microkontroller()			//������� ����������� ��������������
{
	DDRD = 0xff;	
}
void sent_coordinats(int coloum,int line) //������� ����������� ��������� �������
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
		if (line[i] == 192)line[i] = 65;	//�
		if (line[i] == 193)line[i] = 160;	//�
		if (line[i] == 194)line[i] = 66;	//�
		if (line[i] == 195)line[i] = 161;	//�
		if (line[i] == 196)line[i] = 224;	//�
		if (line[i] == 197)line[i] = 69;	//�
		if (line[i] == 198)line[i] = 163;	//�
		if (line[i] == 199)line[i] = 164;	//�
		if (line[i] == 200)line[i] = 165;	//�
		if (line[i] == 178)line[i] = 73;	//�
		if (line[i] == 201)line[i] = 166;	//�
		if (line[i] == 202)line[i] = 75;	//�
		if (line[i] == 203)line[i] = 167;	//�
		if (line[i] == 204)line[i] = 77;	//�
		if (line[i] == 205)line[i] = 72;	//�
		if (line[i] == 206)line[i] = 79;	//�
		if (line[i] == 207)line[i] = 168;	//�
		if (line[i] == 208)line[i] = 80;	//�
		if (line[i] == 209)line[i] = 67;	//�
		if (line[i] == 210)line[i] = 84;	//�
		if (line[i] == 211)line[i] = 169;	//�
		if (line[i] == 212)line[i] = 170;	//�
		if (line[i] == 213)line[i] = 88;	//�
		if (line[i] == 214)line[i] = 225;	//�
		if (line[i] == 215)line[i] = 171;	//�
		if (line[i] == 220)line[i] = 98;	//�
		if (line[i] == 218)line[i] = 226;	//�
		if (line[i] == 222)line[i] = 220;	//�
		if (line[i] == 223)line[i] = 174;	//�
		if (line[i] == 174)line[i] = 176;	//�
		if (line[i] == 219)line[i] = 177;	//�*/
		sent_char(line[i]);
	}
}

int main(void)
{
    initial_microkontroller();
	initial_LCD();
	clear_LCD();

int8_t Symbol[8] = {0x00,0x00,0x00,0x1C,0x02,0x19,0x05,0x15};

		
	sent_byte(0x40,COMAND);			//�������� �����
	for (int i = 0;i < 8;i++)		//����, ���������� ������ � ������ �����������
	{
		sent_byte(Symbol[i],DATA);
	}
	sent_coordinats(0,0);			//���������� ��������� �������
	sent_char(0);					//������� ������





}

