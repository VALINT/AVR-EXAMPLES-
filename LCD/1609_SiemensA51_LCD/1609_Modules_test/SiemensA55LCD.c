#include "SiemensA55LCD.h"


#define SentDATA LCD_PORT |= (1<<D_C);					//Pin DATA/COMMAND set in 1, sent DATA
#define SentCOMMAND LCD_PORT&=~(1<<D_C);				//Pin DATA/COMMAND set in 0, sent COMMAND
#define STROBEON LCD_PORT|=(1<<SCE);					//PIN STROBE set in 1, end of transmitting
#define STROBEOFF LCD_PORT&=~(1<<SCE);					//Pin STROBE set in 0, start of transmitting
#define RESETHigh LCD_PORT|=(1<<RESET);					//Pin RESET set in 1, work mode 
#define RESETLow LCD_PORT&=~(1<<RESET);					//Pin RESET set in 0, mode of reset


const unsigned int Symbols[256][5] PROGMEM =			//table of ASCII symbols(need correction)
														//Write data on flash use "pgmspase.h" library
{
	{0x00,0x00,0x00,0x00,0x00},	//0
	{0x00,0x00,0x00,0x00,0x00},	//1
	{0x00,0x00,0x00,0x00,0x00},	//2
	{0x00,0x00,0x00,0x00,0x00},	//3
	{0x00,0x00,0x00,0x00,0x00},	//4
	{0x00,0x00,0x00,0x00,0x00},	//5
	{0x00,0x00,0x00,0x00,0x00},	//6
	{0x00,0x00,0x00,0x00,0x00},	//7
	{0x00,0x00,0x00,0x00,0x00},	//8
	{0x00,0x00,0x00,0x00,0x00},	//9
	{0x00,0x00,0x00,0x00,0x00},	//10
	{0x00,0x00,0x00,0x00,0x00},	//11
	{0x00,0x00,0x00,0x00,0x00},	//12
	{0x00,0x00,0x00,0x00,0x00},	//13
	{0x00,0x00,0x00,0x00,0x00},	//14
	{0x00,0x00,0x00,0x00,0x00},	//15
	{0x00,0x00,0x00,0x00,0x00},	//16
	{0x00,0x00,0x00,0x00,0x00},	//17
	{0x00,0x00,0x00,0x00,0x00},	//18
	{0x00,0x00,0x00,0x00,0x00},	//19
	{0x00,0x00,0x00,0x00,0x00},	//20
	{0x00,0x00,0x00,0x00,0x00},	//21
	{0x00,0x00,0x00,0x00,0x00},	//22
	{0x00,0x00,0x00,0x00,0x00},	//23
	{0x00,0x00,0x00,0x00,0x00},	//24
	{0x00,0x00,0x00,0x00,0x00},	//25
	{0x00,0x00,0x00,0x00,0x00},	//26
	{0x00,0x00,0x00,0x00,0x00},	//27
	{0x00,0x00,0x00,0x00,0x00},	//28
	{0x00,0x00,0x00,0x00,0x00},	//29
	{0x00,0x00,0x00,0x00,0x00},	//30
	{0x00,0x00,0x00,0x00,0x00},	//31
	{0x00,0x00,0x00,0x00,0x00},	//32//SPASE
	{0x00,0x00,0x5f,0x00,0x00},	//33//!
	{0x00,0x07,0x00,0x07,0x00},	//34//"
	{0x14,0x7f,0x14,0x7f,0x14},	//35//#
	{0x24,0x2a,0x7f,0x2a,0x12},	//36//$
	{0x23,0x13,0x08,0x64,0x62},	//37//%
	{0x36,0x49,0x55,0x22,0x50},	//38//&
	{0x00,0x05,0x03,0x00,0x00},	//39//'
	{0x00,0x1c,0x22,0x41,0x00},	//40//(
	{0x00,0x41,0x22,0x1c,0x00},	//41//)
	{0x14,0x08,0x3e,0x08,0x14},	//42//*
	{0x08,0x08,0x3e,0x08,0x08},	//43//+
	{0x00,0x50,0x30,0x00,0x00},	//44//,
	{0x08,0x08,0x08,0x08,0x08},	//45//-
	{0x00,0x60,0x60,0x00,0x00},	//46//.
	{0x20,0x10,0x08,0x04,0x02},	//47///
	{0x3E,0x41,0x41,0x41,0x3E},	//48//0
	{0x00,0x04,0x02,0x7F,0x00},	//49//1
	{0x42,0x61,0x51,0x49,0x46},	//50//2
	{0x22,0x41,0x41,0x49,0x36},	//51//3
	{0x18,0x14,0x12,0x11,0x7F},	//52//4
	{0x47,0x45,0x45,0x45,0x39},	//53//5
	{0x7E,0x49,0x49,0x49,0x32},	//54//6
	{0x01,0x01,0x61,0x19,0x07},	//55//7
	{0x36,0x49,0x49,0x49,0x36},	//56//8
	{0x26,0x49,0x49,0x49,0x3E},	//57//9
	{0x00,0x36,0x36,0x00,0x00},	//58//:
	{0x00,0x56,0x36,0x00,0x00},	//59//;
	{0x08,0x14,0x22,0x41,0x00},	//60//<
	{0x14,0x14,0x14,0x14,0x14},	//61//=
	{0x00,0x41,0x22,0x14,0x08},	//62//>
	{0x02,0x01,0x51,0x09,0x06},	//63//?
	{0x32,0x49,0x79,0x41,0x3e},	//64//@
	{0x7C,0x12,0x11,0x12,0x7C},	//65//A
	{0x7F,0x49,0x49,0x4E,0x30},	//66//B
	{0x3E,0x41,0x41,0x41,0x22},	//67//C
	{0x7F,0x41,0x41,0x22,0x1C},	//68//D
	{0x7F,0x49,0x49,0x49,0x41},	//69//E
	{0x7F,0x09,0x09,0x09,0x01},	//70//F
	{0x3E,0x41,0x51,0x51,0x32},	//71//G
	{0x7F,0x08,0x08,0x08,0x7F},	//72//H
	{0x00,0x41,0x7F,0x41,0x00},	//73//I
	{0x20,0x40,0x41,0x3F,0x01},	//74//J
	{0x7F,0x08,0x14,0x22,0x41},	//75//K
	{0x7F,0x40,0x40,0x40,0x40},	//76//L
	{0x7F,0x02,0x04,0x02,0x7F},	//77//M
	{0x7F,0x04,0x08,0x10,0x7F},	//78//N
	{0x3E,0x41,0x41,0x41,0x3E},	//79//O
	{0x7E,0x11,0x11,0x11,0x0E},	//80//P
	{0x3E,0x41,0x51,0x61,0x7E},	//81//Q
	{0x7E,0x11,0x11,0x21,0x4E},	//82//R
	{0x26,0x49,0x49,0x49,0x32},	//83//S
	{0x01,0x01,0x7F,0x01,0x01},	//84//T
	{0x3F,0x40,0x40,0x40,0x3F},	//85//U
	{0x0F,0x30,0x40,0x30,0x0F},	//86//V
	{0x3F,0x40,0x30,0x40,0x3F},	//87//W
	{0x63,0x14,0x08,0x14,0x63},	//88//X
	{0x03,0x04,0x78,0x04,0x03},	//89//Y
	{0x61,0x51,0x49,0x45,0x43},	//90//Z
	{0x00,0x7f,0x41,0x41,0x00},	//91//[
	{0x02,0x04,0x08,0x10,0x20},	//92//\//
	{0x00,0x41,0x41,0x7f,0x00},	//93//]
	{0x04,0x02,0x01,0x02,0x04},	//94//^
	{0x40,0x40,0x40,0x40,0x40},	//95//_
	{0x00,0x01,0x02,0x04,0x00},	//96//'
	{0x24,0x54,0x54,0x38,0x40},	//97//a
	{0x3F,0x44,0x44,0x44,0x38},	//98//b
	{0x38,0x44,0x44,0x44,0x20},	//99//c
	{0x38,0x44,0x44,0x44,0x7F},	//100//d
	{0x38,0x54,0x54,0x54,0x58},	//101//e
	{0x08,0x7E,0x09,0x01,0x02},	//102//f
	{0x4C,0x94,0x94,0x94,0x7C},	//103//g
	{0x7F,0x08,0x08,0x08,0x70},	//104//h
	{0x00,0x00,0x7D,0x00,0x00},	//105//i
	{0x40,0x80,0x7D,0x00,0x00},	//106//j
	{0x7F,0x10,0x28,0x44,0x00},	//107//k
	{0x00,0x00,0x7F,0x00,0x00},	//108//l
	{0x7C,0x04,0x78,0x04,0x78},	//109//m
	{0x7C,0x04,0x04,0x78,0x00},	//110//n
	{0x38,0x44,0x44,0x44,0x38},	//111//o
	{0x00,0xFC,0x24,0x24,0x18},	//112//p
	{0x00,0x18,0x24,0x24,0xFC}, //113//q
	{0x7C,0x08,0x04,0x04,0x08},	//114//r
	{0x20,0x54,0x54,0x54,0x08},	//115//s
	{0x08,0x3F,0x48,0x40,0x20},	//116//t
	{0x3C,0x40,0x40,0x40,0x3C}, //117//u
	{0x0C,0x30,0x40,0x30,0x0C},	//118//v
	{0x3C,0x40,0x30,0x40,0x3C},	//119//w
	{0x44,0x28,0x10,0x28,0x44},	//120//x
	{0x00,0x4C,0x90,0x90,0x7C},	//121//y
	{0x44,0x64,0x54,0x4C,0x00},	//122//z
	{0x00,0x00,0x00,0x00,0x00},	//123
	{0x00,0x00,0x00,0x00,0x00},	//124
	{0x00,0x00,0x00,0x00,0x00},	//125
	{0x00,0x00,0x00,0x00,0x00},	//126
	{0x00,0x00,0x00,0x00,0x00},	//127
	{0x00,0x00,0x00,0x00,0x00},	//128
	{0x00,0x00,0x00,0x00,0x00},	//129
	{0x00,0x00,0x00,0x00,0x00},	//130
	{0x00,0x00,0x00,0x00,0x00},	//131
	{0x00,0x00,0x00,0x00,0x00},	//132
	{0x00,0x00,0x00,0x00,0x00},	//133
	{0x00,0x00,0x00,0x00,0x00},	//134
	{0x00,0x00,0x00,0x00,0x00},	//135
	{0x00,0x00,0x00,0x00,0x00},	//136
	{0x00,0x00,0x00,0x00,0x00},	//137
	{0x00,0x00,0x00,0x00,0x00},	//138
	{0x00,0x00,0x00,0x00,0x00},	//139
	{0x00,0x00,0x00,0x00,0x00},	//140
	{0x00,0x00,0x00,0x00,0x00},	//141
	{0x00,0x00,0x00,0x00,0x00},	//142
	{0x00,0x00,0x00,0x00,0x00},	//143
	{0x00,0x00,0x00,0x00,0x00},	//144
	{0x00,0x00,0x00,0x00,0x00},	//145
	{0x00,0x00,0x00,0x00,0x00},	//146
	{0x00,0x00,0x00,0x00,0x00},	//147
	{0x00,0x00,0x00,0x00,0x00},	//148
	{0x00,0x00,0x00,0x00,0x00},	//149
	{0x00,0x00,0x00,0x00,0x00},	//150
	{0x00,0x00,0x00,0x00,0x00},	//151
	{0x00,0x00,0x00,0x00,0x00},	//152
	{0x00,0x00,0x00,0x00,0x00},	//153
	{0x00,0x00,0x00,0x00,0x00},	//154
	{0x00,0x00,0x00,0x00,0x00},	//155
	{0x00,0x00,0x00,0x00,0x00},	//156
	{0x00,0x00,0x00,0x00,0x00},	//157
	{0x00,0x00,0x00,0x00,0x00},	//158
	{0x00,0x00,0x00,0x00,0x00},	//159
	{0x00,0x00,0x00,0x00,0x00},	//160
	{0x00,0x00,0x00,0x00,0x00},	//161	
	{0x00,0x00,0x00,0x00,0x00},	//162
	{0x00,0x00,0x00,0x00,0x00},	//163
	{0x00,0x00,0x00,0x00,0x00},	//164
	{0x00,0x00,0x00,0x00,0x00},	//165
	{0x00,0x00,0x00,0x00,0x00},	//166
	{0x00,0x00,0x00,0x00,0x00},	//167
	{0x00,0x00,0x00,0x00,0x00},	//168
	{0x00,0x00,0x00,0x00,0x00},	//169
	{0x00,0x00,0x00,0x00,0x00},	//170
	{0x00,0x00,0x00,0x00,0x00},	//171
	{0x00,0x00,0x00,0x00,0x00},	//172
	{0x00,0x00,0x00,0x00,0x00},	//173
	{0x00,0x00,0x00,0x00,0x00},	//174
	{0x00,0x00,0x00,0x00,0x00},	//175
	{0x00,0x00,0x00,0x00,0x00},	//176
	{0x00,0x00,0x00,0x00,0x00},	//177
	{0x00,0x00,0x00,0x00,0x00},	//178
	{0x00,0x00,0x00,0x00,0x00},	//179
	{0x00,0x00,0x00,0x00,0x00},	//180
	{0x00,0x00,0x00,0x00,0x00},	//181
	{0x00,0x00,0x00,0x00,0x00},	//182
	{0x00,0x00,0x00,0x00,0x00},	//183
	{0x00,0x00,0x00,0x00,0x00},	//184
	{0x00,0x00,0x00,0x00,0x00},	//185
	{0x00,0x00,0x00,0x00,0x00},	//186
	{0x00,0x00,0x00,0x00,0x00},	//187
	{0x00,0x00,0x00,0x00,0x00},	//188
	{0x00,0x00,0x00,0x00,0x00},	//189
	{0x00,0x00,0x00,0x00,0x00},	//190
	{0x00,0x00,0x00,0x00,0x00},	//191
	{0x7C,0x12,0x11,0x12,0x7C},	//192//A
	{0x7F,0x45,0x45,0x45,0x39},	//193//�
	{0x7F,0x49,0x49,0x4E,0x30},	//194//B
	{0x7F,0x01,0x01,0x01,0x01},	//195//�
//	{0x7E,0x02,0x02,0x02,0x01},	//195//�
	{0x60,0x3E,0x21,0x3F,0x60},	//196//�
	{0x7F,0x49,0x49,0x49,0x41},	//197//E
//	{0x41,0x49,0x49,0x2A,0x1C}, //66//�
//	{0x1C,0x2A,0x49,0x49,0x41},	//67//�
	{0x63,0x14,0x7F,0x14,0x63},	//198//�
	{0x22,0x41,0x49,0x49,0x36},	//199//�
	{0x7F,0x20,0x10,0x08,0x7F},	//200//�
	{0x7C,0x21,0x12,0x09,0x7C},	//201//�
	{0x7F,0x08,0x14,0x22,0x41},	//202//K
//	{0x7F,0x48,0x30,0x00,0x7F},	//72//�
//	{0x00,0x45,0x7C,0x45,0x00},	//73//�
	{0x40,0x3E,0x01,0x01,0x7F},	//203//�
	{0x7F,0x02,0x04,0x02,0x7F},	//204//M
	{0x7F,0x08,0x08,0x08,0x7F},	//205//H
	{0x3E,0x41,0x41,0x41,0x3E},	//206//O
	{0x7F,0x01,0x01,0x01,0x7F},	//207//�
	{0x7E,0x11,0x11,0x11,0x0E},	//208//P
	{0x3E,0x41,0x41,0x41,0x22},	//209//C
	{0x01,0x01,0x7F,0x01,0x01},	//210//T
	{0x07,0x48,0x48,0x48,0x3F},	//211//�
	{0x06,0x09,0x7F,0x09,0x06},	//212//�
	{0x63,0x14,0x08,0x14,0x63},	//213//X
	{0x7F,0x40,0x40,0x40,0xff},	//214//�
	{0x07,0x08,0x08,0x08,0x7F},	//215//�
	{0x7F,0x40,0x7F,0x40,0x7F},	//216//�
	{0x7F,0x40,0x7F,0x40,0xfF},	//217//�
	{0x01,0x7f,0x48,0x48,0x30},	//218//�
	{0x7F,0x48,0x30,0x00,0x7F},	//219//�
	{0x00,0x7f,0x48,0x48,0x30},	//220//�
	{0x41,0x49,0x49,0x2A,0x1C}, //221//�
	{0x7F,0x08,0x3E,0x41,0x3E},	//222//�
	{0x46,0x29,0x19,0x09,0x7F},	//223//�
		
	{0x7c,0x14,0x14,0x14,0x08},	//224//�
	{0x08,0x14,0x14,0x18,0x7c},	//225//�
	{0x7c,0x08,0x04,0x04,0x08},	//226//�
	{0x48,0x54,0x54,0x54,0x20},	//227//�
	{0x04,0x3f,0x44,0x40,0x20},	//228//�
	{0x3c,0x40,0x40,0x20,0x7c},	//229//�
	{0x1c,0x20,0x40,0x20,0x1c},	//230//�
	{0x3c,0x40,0x30,0x40,0x3c},	//231//�
	{0x44,0x28,0x10,0x28,0x44},	//232//�
	{0x0c,0x50,0x50,0x50,0x3c},	//233//�
	{0x44,0x64,0x54,0x4c,0x44},	//234//�
	{0x00,0x08,0x36,0x41,0x00},	//235//�
	{0x00,0x00,0x7f,0x00,0x00},	//236//�
	{0x00,0x41,0x36,0x08,0x00},	//237//�
	{0x10,0x08,0x08,0x10,0x08},	//238//�
	{0x78,0x46,0x41,0x46,0x78},	//239//�
	{0x7c,0x14,0x14,0x14,0x08},	//240//�
	{0x08,0x14,0x14,0x18,0x7c},	//241//�
	{0x7c,0x08,0x04,0x04,0x08},	//242//�
	{0x48,0x54,0x54,0x54,0x20},	//243//�
	{0x04,0x3f,0x44,0x40,0x20},	//244//�
	{0x3c,0x40,0x40,0x20,0x7c},	//245//�
	{0x1c,0x20,0x40,0x20,0x1c},	//246//�
	{0x3c,0x40,0x30,0x40,0x3c},	//247//�
	{0x44,0x28,0x10,0x28,0x44},	//248//�
	{0x0c,0x50,0x50,0x50,0x3c},	//249//�
	{0x44,0x64,0x54,0x4c,0x44},	//250//�
	{0x00,0x08,0x36,0x41,0x00},	//251//�
	{0x00,0x00,0x7f,0x00,0x00},	//252//�
	{0x00,0x41,0x36,0x08,0x00},	//253//�
	{0x10,0x08,0x08,0x10,0x08},	//254//�
	{0x78,0x46,0x41,0x46,0x78},	//255//�
};		//
																

void LCD_Init()											//Initial. LCD
{
	LCD_Reset();
	LCD_Sent_Byte(0x21,COMMAND);
	LCD_Sent_Byte(0x09,COMMAND);
	LCD_Sent_Byte(0xE0,COMMAND);
	LCD_Sent_Byte(0x15,COMMAND);
	LCD_Sent_Byte(0x06,COMMAND);
	LCD_Sent_Byte(0x20,COMMAND);
	LCD_Sent_Byte(0x0C,COMMAND);
}

void LCD_Sent_Byte(int byte,int status)					//sent 1 byte in LCD by hardware SPI 
{
	if (status == COMMAND)SentCOMMAND
	else SentDATA
	STROBEOFF
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));
	STROBEON
}

void LCD_Reset()										//Reset LCD, RAM LCD after reset, not set, need clear
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

void LCD_SCL()											//Clear LCD,fill RAM LCD by empty bytes
{
	for(int smbl = 0; smbl < 816; smbl++)
	{
		LCD_Sent_Byte(0,DATA);
	}
}

void LCD_print(int symbol)								//Print symbol on LCD, need division symbols for one is main cycle
{														//Use symbols from Flash ROM
														//Need using "pgmspase.h" library
	
	int buffer;											 
	for(int part = 0; part < 5; part++)
	{
		buffer = pgm_read_byte(&(Symbols[symbol][part]));
		LCD_Sent_Byte(buffer,DATA);
	}
	LCD_Sent_Byte(0,DATA);
}

