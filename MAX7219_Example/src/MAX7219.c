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

static uint8_t send_byte(uint8_t byte);

/**
 * @brief This function initializes SPI
 * 
 * @return 0
 */
uint8_t init_spi(void)
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

/**
 * @brief This function send byte via SPI
 * 
 * @param byte (input byte that should be sent)
 * @return 0
 */
uint8_t send_byte(uint8_t byte)
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

/** 
 * @brief This function send data byte (or bytes) to appropriate address.
 * 
 * @param addres 
 * @param len 
 * @param ... 
 * @return 0 
 */
uint8_t max7219_write(uint8_t addres, uint8_t len, ...)
{
	va_list data_args;
	va_start(data_args, len);

	CS_LOW;
	for(uint8_t i = 0; i < len; i += 1)
	{
		uint8_t data = va_arg(data_args, int);
		send_byte(addres);
		send_byte(data);
	}
	CS_HIGH;
	
	va_end(data_args);
	return 0;
}

uint8_t max7219_init(void)
{
	init_spi();
	// Decode mode: none
	max7219_write(0x09, 1, 0);
	// Intensity: 3 (0-15)
	max7219_write(0x0A, 1, 1);
	// Scan limit: All "digits" (rows) on
	max7219_write(0x0B, 1, 7);
	// Shutdown register: Display on
	max7219_write(0x0C, 1, 1);
	// Display test: off
	max7219_write(0x0F, 1, 0);
	
	max7219_clear();
	
	return 0;
}

uint8_t max7219_clear(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		max7219_write(i+1, 1, 0);
	}
	
	return 0;
}