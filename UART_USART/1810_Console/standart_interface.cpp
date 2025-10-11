/*------------------------------------------------------------------------------------------------------
 * Standard interface module
 *______________________________________________________________________________________________________
 *  __    __ __ __     __   _____	 _____ _____   __    __  _  ____    __    ____  _____ 
 *  \ \  / //  \\ \    \_\ / ___/	/ ___/|_   _| /  \  |  \| ||  _ \  /  \  | |\ \|_   _|
 *   \ \/ //    \\ \___ |/ \___ \	\___ \  | |  /    \ | |\  || |_|| /    \ | |/ /  | |  
 *    \__//__/\__\\____\   /____/	/____/  |_| /__/\__\|_| \_||____//__/\__\|_|\_\  |_| 
 *					 _  __  _  _____  ____  ____  ____    _    ____  ____ 
 *					| ||  \| ||_   _|| ___|| |\ \| ___|  / \  /  __\| ___|
 *					| || |\  |  | |  | ___|| |/ /| ___| / _ \ | |__ | ___|
 *					|_||_| \_|  |_|  |____||_|\_\|_|   /_/ \_\\____/|____|
 *_______________________________________________________________________________________________________
 *
 * Created: 18-Sep-2018 23:05:14
 *  Author: VAL
 *///------------------------------------------------------------------------------------------------------ 

#include "standart_interface.hpp"

//---------------------------------------------------------------------------------------------------------
//UART part

void uart_init(void)
{
	//UBRR0H = UBRRL_value;                        /* defined in setbaud.h */
	UBRR0L = UBRRL_value;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
	/* Enable USART transmitter/receiver */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
}

void uart_write_char(char data)
{
	while(! (UCSR0A & (1 << UDRE0))){}

	UDR0 = data;
}

void uart_send_array(char* data)
{
	uint8_t i = 0;
	
	while(*(data+i) != '\0')
	{
		uart_write_char(*(data+i));
		i++;
	}
}

//---------------------------------------------------------------------------------------------------------
// I2C part

void i2c_init(void)
{
	TWBR = 0xFF;
}

void i2c_start_operation(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void i2c_stop_operation(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_send_byte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
}

void i2c_send_data(uint8_t data, uint8_t addres)
{
	i2c_start_operation();
	i2c_send_byte(addres);
	i2c_send_byte(data);
	i2c_stop_operation();
}

//void i2c_send_array(uint8_t &arr_start, uint8_t lenght);

uint8_t i2c_reseive_byte(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t i2c_reseive_last_byte(void)
{	
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}
