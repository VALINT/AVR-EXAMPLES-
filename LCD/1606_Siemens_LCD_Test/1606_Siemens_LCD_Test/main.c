#define F_CPU 8000000UL

#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


#define Button_PORT PORTD
#define LCD_PORT PORTB
#define DATA 1
#define COMMAND 0
#define RESET PB2
#define D_C PB0
#define SCE PB1 
#define SentDATA PORTD |= (0x01);
#define SentCOMMAND PORTD&=(0xFE);
#define STROBEON PORTD|=(0b00000010);
#define STROBEOFF PORTD&=(0b11111101);
#define RESETHigh PORTD|=(0b00000100);
#define RESETLow PORTD&=(0b11111011);


int8_t a = 0;
char Line [17];
char Line1 [17];
static int8_t sym[5];
int adc;
int volts;
int invert;

void Initial();
void LCD_initial();
void LCD_Sent_Byte();
void LCD_Set_Cordinates();
void LCD_Reset();


void Initial(void)
{
	DDRD = 0xff;
	DDRB = 0xff;												
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);
	
	ADMUX = (1 << REFS0); //опорна напруга 5в/активний вхід АЦП5
	ADCSRA |= (1<<ADEN)  | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0)| (1<<ADSC);
	//Дозволити глобальні переривання
	sei();
}

void LCD_initial()						//Initial. LCD
{
	LCD_Reset();
	LCD_Sent_Byte(0x21,COMMAND);
	LCD_Sent_Byte(0x09,COMMAND);
	LCD_Sent_Byte(0xE0,COMMAND);
	LCD_Sent_Byte(0x15,COMMAND);
	LCD_Sent_Byte(0x06,COMMAND);
	LCD_Sent_Byte(0x22,COMMAND);			//22 - vertical addresind....20 - horysontal adresing.(for string printing)
	LCD_Sent_Byte(0x0C,COMMAND);
}

void LCD_Sent_Byte(int byte,int status)
{
	if (status == COMMAND)SentCOMMAND
	else SentDATA
	STROBEOFF
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));
	STROBEON
}

void LCD_Reset()
{
		RESETLow
		_delay_us(1);
		RESETHigh
		STROBEON
		_delay_ms(1);
}

void LCD_Set_Cordinates(int YY,int XX)
{
	LCD_Sent_Byte(0x40+YY,COMMAND);
	LCD_Sent_Byte(0x80+XX,COMMAND);
	_delay_ms(5);	
}

void ASCII_Table(int symbol)
{
	switch(symbol)
	{
		case 0:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//0
		case 1:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//1
		case 2:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//2
		case 3:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//3
		case 4:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//4
		case 5:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//5
		case 6:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//6
		case 7:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//7
		case 8:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//8
		case 9:   sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//9
		case 10:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//10
		case 11:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//11
		case 12:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//12
		case 13:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//13
		case 14:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//14
		case 15:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//15
		case 16:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//16
		case 17:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//17
		case 18:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//18
		case 19:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//19
		case 20:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//20
		case 21:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//21
		case 22:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//22
		case 23:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//23
		case 24:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//24
		case 25:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//25
		case 26:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//26
		case 27:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//27
		case 28:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//28
		case 29:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//29
		case 30:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//30
		case 31:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//31
		case 32:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//32//spase
		case 33:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x5F;sym[3]=0x00;sym[4]=0x00;break;	//33//exclamination marc
		case 34:  sym[0]=0x00;sym[1]=0x06;sym[2]=0x00;sym[3]=0x06;sym[4]=0x00;break;	//34
		case 35:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//35
		case 36:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//36
		case 37:  sym[0]=0x23;sym[1]=0x13;sym[2]=0x08;sym[3]=0x64;sym[4]=0x62;break;	//37//%
		case 38:  sym[0]=0x36;sym[1]=0x49;sym[2]=0x55;sym[3]=0x22;sym[4]=0x50;break;	//38//&
		case 39:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//39
		case 40:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//40
		case 41:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//41
		case 42:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//42
		case 43:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//43
		case 44:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//44
		case 45:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//45
		case 46:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//46
		case 47:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//47
		case 48:  sym[0]=0x3E;sym[1]=0x51;sym[2]=0x49;sym[3]=0x45;sym[4]=0x3E;break;	//48//0
		case 49:  sym[0]=0x00;sym[1]=0x42;sym[2]=0x7F;sym[3]=0x40;sym[4]=0x00;break;	//49//1
		case 50:  sym[0]=0x42;sym[1]=0x61;sym[2]=0x51;sym[3]=0x49;sym[4]=0x46;break;	//50//2
		case 51:  sym[0]=0x22;sym[1]=0x41;sym[2]=0x49;sym[3]=0x49;sym[4]=0x36;break;	//51//3
		case 52:  sym[0]=0x18;sym[1]=0x14;sym[2]=0x12;sym[3]=0x7F;sym[4]=0x10;break;	//52//4
		case 53:  sym[0]=0x27;sym[1]=0x45;sym[2]=0x45;sym[3]=0x45;sym[4]=0x39;break;	//53//5
		case 54:  sym[0]=0x3E;sym[1]=0x49;sym[2]=0x49;sym[3]=0x49;sym[4]=0x32;break;	//54//6
		case 55:  sym[0]=0x61;sym[1]=0x11;sym[2]=0x09;sym[3]=0x05;sym[4]=0x03;break;	//55//7
		case 56:  sym[0]=0x36;sym[1]=0x49;sym[2]=0x49;sym[3]=0x49;sym[4]=0x36;break;	//56//8
		case 57:  sym[0]=0x26;sym[1]=0x49;sym[2]=0x49;sym[3]=0x49;sym[4]=0x3E;break;	//57//9
		case 58:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//58
		case 59:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//59
		case 60:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//60
		case 61:  sym[0]=0x14;sym[1]=0x14;sym[2]=0x14;sym[3]=0x14;sym[4]=0x14;break;	//61
		case 62:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//62
		case 63:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//63
		case 64:  sym[0]=0x32;sym[1]=0x49;sym[2]=0x59;sym[3]=0x51;sym[4]=0x3E;break;	//64//@
		case 65:  sym[0]=0x7C;sym[1]=0x12;sym[2]=0x11;sym[3]=0x12;sym[4]=0x7C;break;	//65//A
		case 66:  sym[0]=0x7F;sym[1]=0x49;sym[2]=0x49;sym[3]=0x4E;sym[4]=0x30;break;	//66//B
		case 67:  sym[0]=0x3E;sym[1]=0x41;sym[2]=0x41;sym[3]=0x41;sym[4]=0x22;break;	//67//C
		case 68:  sym[0]=0x7F;sym[1]=0x41;sym[2]=0x41;sym[3]=0x22;sym[4]=0x1C;break;	//68//D
		case 69:  sym[0]=0x7F;sym[1]=0x49;sym[2]=0x49;sym[3]=0x49;sym[4]=0x41;break;	//69//E
		case 70:  sym[0]=0x7F;sym[1]=0x09;sym[2]=0x09;sym[3]=0x09;sym[4]=0x01;break;	//70//F
		case 71:  sym[0]=0x3E;sym[1]=0x41;sym[2]=0x51;sym[3]=0x51;sym[4]=0x32;break;	//71//G
		case 72:  sym[0]=0x7F;sym[1]=0x08;sym[2]=0x08;sym[3]=0x08;sym[4]=0x7F;break;	//72//H
		case 73:  sym[0]=0x00;sym[1]=0x41;sym[2]=0x7F;sym[3]=0x41;sym[4]=0x00;break;	//73//I
		case 74:  sym[0]=0x20;sym[1]=0x40;sym[2]=0x41;sym[3]=0x3F;sym[4]=0x01;break;	//74//J
		case 75:  sym[0]=0x7F;sym[1]=0x08;sym[2]=0x14;sym[3]=0x22;sym[4]=0x41;break;	//75//K
		case 76:  sym[0]=0x7F;sym[1]=0x40;sym[2]=0x40;sym[3]=0x40;sym[4]=0x40;break;	//76//L
		case 77:  sym[0]=0x7F;sym[1]=0x02;sym[2]=0x04;sym[3]=0x02;sym[4]=0x7F;break;	//77//M
		case 78:  sym[0]=0x7F;sym[1]=0x04;sym[2]=0x08;sym[3]=0x10;sym[4]=0x7F;break;	//78//N
		case 79:  sym[0]=0x3E;sym[1]=0x41;sym[2]=0x41;sym[3]=0x41;sym[4]=0x3E;break;	//79//O
		case 80:  sym[0]=0x7E;sym[1]=0x11;sym[2]=0x11;sym[3]=0x11;sym[4]=0x0E;break;	//80//P
		case 81:  sym[0]=0x3E;sym[1]=0x41;sym[2]=0x51;sym[3]=0x61;sym[4]=0x7E;break;	//81//Q
		case 82:  sym[0]=0x7E;sym[1]=0x11;sym[2]=0x11;sym[3]=0x21;sym[4]=0x4E;break;	//82//R
		case 83:  sym[0]=0x26;sym[1]=0x49;sym[2]=0x49;sym[3]=0x49;sym[4]=0x32;break;	//83//S
		case 84:  sym[0]=0x01;sym[1]=0x01;sym[2]=0x7F;sym[3]=0x01;sym[4]=0x01;break;	//84//T
		case 85:  sym[0]=0x3F;sym[1]=0x40;sym[2]=0x40;sym[3]=0x40;sym[4]=0x3F;break;	//85//U
		case 86:  sym[0]=0x0F;sym[1]=0x30;sym[2]=0x40;sym[3]=0x30;sym[4]=0x0F;break;	//86//V
		case 87:  sym[0]=0x3F;sym[1]=0x40;sym[2]=0x30;sym[3]=0x40;sym[4]=0x3F;break;	//87//W
		case 88:  sym[0]=0x63;sym[1]=0x14;sym[2]=0x08;sym[3]=0x14;sym[4]=0x63;break;	//88//X
		case 89:  sym[0]=0x03;sym[1]=0x04;sym[2]=0x78;sym[3]=0x04;sym[4]=0x03;break;	//89//Y
		case 90:  sym[0]=0x61;sym[1]=0x51;sym[2]=0x49;sym[3]=0x45;sym[4]=0x43;break;	//90//Z
		case 91:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//91
		case 92:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//92
		case 93:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//93
		case 94:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//94
		case 95:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//95
		case 96:  sym[0]=0x00;sym[1]=0x00;sym[2]=0x00;sym[3]=0x00;sym[4]=0x00;break;	//96
		case 97:  sym[0]=0x20;sym[1]=0x54;sym[2]=0x54;sym[3]=0x54;sym[4]=0x78;break;	//97//a
		case 98:  sym[0]=0x7F;sym[1]=0x48;sym[2]=0x44;sym[3]=0x44;sym[4]=0x38;break;	//98//b
		case 99:  sym[0]=0x38;sym[1]=0x44;sym[2]=0x44;sym[3]=0x44;sym[4]=0x28;break;	//99//c
		case 100: sym[0]=0x38;sym[1]=0x44;sym[2]=0x44;sym[3]=0x48;sym[4]=0x7F;break;	//100//d
		case 101: sym[0]=0x38;sym[1]=0x54;sym[2]=0x54;sym[3]=0x54;sym[4]=0x18;break;	//101//e
		case 102: sym[0]=0x08;sym[1]=0x7E;sym[2]=0x09;sym[3]=0x01;sym[4]=0x02;break;	//102//f
		case 103: sym[0]=0x4C;sym[1]=0x94;sym[2]=0x94;sym[3]=0x94;sym[4]=0x7C;break;	//103//g
		case 104: sym[0]=0x7F;sym[1]=0x08;sym[2]=0x04;sym[3]=0x04;sym[4]=0x78;break;	//104//h
		case 105: sym[0]=0x00;sym[1]=0x44;sym[2]=0x7D;sym[3]=0x40;sym[4]=0x00;break;	//105//i
		case 106: sym[0]=0x00;sym[1]=0x40;sym[2]=0x44;sym[3]=0x3D;sym[4]=0x00;break;	//106//j
		case 107: sym[0]=0x7F;sym[1]=0x20;sym[2]=0x10;sym[3]=0x28;sym[4]=0x44;break;	//107//k
		case 108: sym[0]=0x00;sym[1]=0x41;sym[2]=0x7F;sym[3]=0x40;sym[4]=0x00;break;	//108//l
		case 109: sym[0]=0x7C;sym[1]=0x04;sym[2]=0x18;sym[3]=0x04;sym[4]=0x7C;break;	//109//m
		case 110: sym[0]=0x7C;sym[1]=0x08;sym[2]=0x04;sym[3]=0x04;sym[4]=0x78;break;	//110//n
		case 111: sym[0]=0x38;sym[1]=0x44;sym[2]=0x44;sym[3]=0x44;sym[4]=0x38;break;	//111//o
		case 112: sym[0]=0xFC;sym[1]=0x14;sym[2]=0x24;sym[3]=0x24;sym[4]=0x18;break;	//112//p
		case 113: sym[0]=0x18;sym[1]=0x24;sym[2]=0x24;sym[3]=0x14;sym[4]=0xFC;break;	//113//q
		case 114: sym[0]=0x7C;sym[1]=0x04;sym[2]=0x04;sym[3]=0x08;sym[4]=0x00;break;	//114//r
		case 115: sym[0]=0x08;sym[1]=0x54;sym[2]=0x54;sym[3]=0x54;sym[4]=0x20;break;	//115//s
		case 116: sym[0]=0x08;sym[1]=0x3F;sym[2]=0x48;sym[3]=0x40;sym[4]=0x20;break;	//116//t
		case 117: sym[0]=0x3C;sym[1]=0x40;sym[2]=0x40;sym[3]=0x20;sym[4]=0x7C;break;	//117//u
		case 118: sym[0]=0x1C;sym[1]=0x40;sym[2]=0x40;sym[3]=0x20;sym[4]=0x1C;break;	//118//v
		case 119: sym[0]=0x3C;sym[1]=0x40;sym[2]=0x30;sym[3]=0x40;sym[4]=0x3C;break;	//119//w
		case 120: sym[0]=0x44;sym[1]=0x28;sym[2]=0x10;sym[3]=0x28;sym[4]=0x44;break;	//120//x
		case 121: sym[0]=0x0C;sym[1]=0x50;sym[2]=0x50;sym[3]=0x48;sym[4]=0x3C;break;	//121//y
		case 122: sym[0]=0x44;sym[1]=0x64;sym[2]=0x54;sym[3]=0x4C;sym[4]=0x44;break;	//122//z
	}
}


ISR (ADC_vect)
{
	adc = ADCW;
}


int main(void)
{
	Initial();
	LCD_initial();
		LCD_Set_Cordinates(0,0);
		_delay_ms(10);
		for (int i = 0; i < 816 ;i++)
		{LCD_Sent_Byte(0,DATA);}
		_delay_ms(10);
		
		
		LCD_Set_Cordinates(0,0);
		_delay_ms(300);
		for (int v = 0; v < 255 ;v++)
		{LCD_Sent_Byte(v,DATA);
		_delay_ms(500);}
		_delay_ms(10);

	LCD_Set_Cordinates(3,0);
	sprintf(Line,"  ADC  = ");
	for(int8_t i = 0; i < 8 ;i++)
	{
		if ((i == 17))LCD_Set_Cordinates(4,0);
		ASCII_Table(Line[i]);
		for(int8_t j = 0; j < 5;j++)
		{
			LCD_Sent_Byte(sym[j],DATA);
		}
		LCD_Sent_Byte(0,DATA);
	}
	
	LCD_Set_Cordinates(5,0);
	sprintf(Line1,"VOLTAGE = ");
	for(int8_t i = 0; i < 10 ;i++)
	{
		if ((i == 17))LCD_Set_Cordinates(4,0);
		ASCII_Table(Line1[i]);
		for(int8_t j = 0; j < 5;j++)
		{
			LCD_Sent_Byte(sym[j],DATA);
		}
		LCD_Sent_Byte(0,DATA);
	}
	
while(1)
{
		LCD_Set_Cordinates(3,56);
		sprintf(Line,"%d",adc);
		for(int8_t i = 0; i < 4 ;i++)
		{
			if ((i == 17))LCD_Set_Cordinates(4,0);
			ASCII_Table(Line[i]);
			for(int8_t j = 0; j < 5;j++)
			{
				LCD_Sent_Byte(sym[j],DATA);
			}
			LCD_Sent_Byte(0,DATA);
		}
	
volts = adc*5;
adc = volts/1000;
			LCD_Set_Cordinates(5,55);
			sprintf_P(Line1,"%d",adc);
			for(int8_t i = 0; i < 5 ;i++)
			{
				if ((i == 17))LCD_Set_Cordinates(4,0);
				ASCII_Table(Line1[i]);
				for(int8_t j = 0; j < 5;j++)
				{
					LCD_Sent_Byte(sym[j],DATA);
				}
				LCD_Sent_Byte(0,DATA);
			}
adc = volts%1000;
		LCD_Set_Cordinates(5,65);
		sprintf_P(Line1,"%d",adc);
		for(int8_t i = 0; i < 5 ;i++)
		{
			if ((i == 17))LCD_Set_Cordinates(4,0);
			ASCII_Table(Line1[i]);
			for(int8_t j = 0; j < 5;j++)
			{
				LCD_Sent_Byte(sym[j],DATA);
			}
			LCD_Sent_Byte(0,DATA);
		}
		_delay_ms(100);
		ADCSRA |= (1<<ADSC);
		
		

			LCD_Sent_Byte(0b00001101,COMMAND);
			_delay_ms(1000);

			LCD_Sent_Byte(0b00001100,COMMAND);
			_delay_ms(1000);

}

}
