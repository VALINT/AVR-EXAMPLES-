/*
 * MAX7219.cpp
 *
 * Created: 01.04.2018 14:25:38
 *  Author: VAL
 */ 

#include "MAX7219.h"

#define CS_HIGH		CS_PORT |=  (1 << CS_PIN)
#define CS_LOW		CS_PORT &= ~(1 << CS_PIN)
#define CLK_HIGH	SCL_PORT |= (1<<SCL_PIN)
#define CLK_LOW		SCL_PORT &= ~(1<<SCL_PIN)
#define DATA_HIGH	MOSI_PORT |= (1<<MOSI_PIN)
#define DATA_LOW	MOSI_PORT &= ~(1<<MOSI_PIN)

uint8_t Sent_Byte(uint8_t byte);


uint8_t Init_SPI()
{
	#ifdef USING_HARD_SPI
		DDRB	|= 0xff;
		CS_DDR  |= (1 << CS_PIN);
		SPCR	|= (1 << SPE)|(1 << MSTR)|(1 << SPR1);
	#endif
	#ifdef USING_PROGRAM_SPI
		CS_DDR  |= (1 << CS_PIN);
		SCL_DDR |= (1 << SCL_PIN);
		MOSI_DDR|= (1 << MOSI_PIN);
	#endif
	
	CS_HIGH;
	
	return 0;
}

uint8_t Sent_Byte(uint8_t byte)
{
	asm("nop");
	#ifdef USING_HARD_SPI
		SPDR = byte;
		while(!(SPSR & (1<<SPIF)));
	#endif
	#ifdef USING_PROGRAM_SPI
		for (uint8_t i = 0; i < 8; i++, byte <<= 1)
		{
			CLK_LOW;
			if (byte & 0x80)
			DATA_HIGH;
			else
			DATA_LOW;
			asm("nop");
			CLK_HIGH;
		}
	#endif
	return 0;
}

uint8_t MAX7219_Write(uint8_t Addres, uint8_t Data)
{
	CS_LOW;
	Sent_Byte(Addres);
	Sent_Byte(Data);
	CS_HIGH;
	
	return 0;
}

uint8_t MAX7219_Write(uint8_t Addres, uint8_t Data1, uint8_t Data2)
{
	CS_LOW;
	Sent_Byte(Addres);
	Sent_Byte(Data1);
	Sent_Byte(Addres);
	Sent_Byte(Data2);
	CS_HIGH;
	
	return 0;
}

uint8_t MAX7219_Write(uint8_t Addres, uint8_t Data1, uint8_t Data2, uint8_t Data3)
{
	CS_LOW;
	Sent_Byte(Addres);
	Sent_Byte(Data1);
	Sent_Byte(Addres);
	Sent_Byte(Data2);
	Sent_Byte(Addres);
	Sent_Byte(Data3);
	CS_HIGH;
	
	return 0;
}

uint8_t MAX7219_Write(uint8_t Addres, uint8_t Data1, uint8_t Data2, uint8_t Data3, uint8_t Data4)
{
	CS_LOW;
	Sent_Byte(Addres);
	Sent_Byte(Data1);
	Sent_Byte(Addres);
	Sent_Byte(Data2);
	Sent_Byte(Addres);
	Sent_Byte(Data3);
	Sent_Byte(Addres);
	Sent_Byte(Data4);
	CS_HIGH;
	
	return 0;
}

uint8_t MAX7219_Init(void)
{
	Init_SPI();
	// Decode mode: none
	MAX7219_Write(0x09, 0);
	// Intensity: 3 (0-15)
	MAX7219_Write(0x0A, 1);
	// Scan limit: All "digits" (rows) on
	MAX7219_Write(0x0B, 7);
	// Shutdown register: Display on
	MAX7219_Write(0x0C, 1);
	// Display test: off
	MAX7219_Write(0x0F, 0);
	
	MAX7219_Clear();
	
	return 0;
}

uint8_t MAX7219_Clear(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		MAX7219_Write(i+1, 0);
	}
	
	return 0;
}