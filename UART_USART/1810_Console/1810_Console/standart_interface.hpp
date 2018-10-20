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
 *------------------------------------------------------------------------------------------------------- 
 *	This module consist program realization of communication interfaces.
 *	Using hardware interfaces (need for easy programing if you need using interface)
 *-------------------------------------------------------------------------------------------------------
 *	History:
 *		-	18-Sep-2018
 *
 *-------------------------------------------------------------------------------------------------------
 *	Features:
 *		-	Using hardware I2C interface (protocol) 
 *
 *-------------------------------------------------------------------------------------------------------
 */

#ifndef STANDART_INTERFACE_H_
#define STANDART_INTERFACE_H_

#include <avr/io.h>
#include <stdint.h>


#define F_CPU 8000000UL
#define BAUD 9600L // Скорость обмена данными
#define UBRRL_value (F_CPU/(BAUD*16))-1

/*-------------------------------------------------------------------------------------------------------
 *	UART/USART HARDWARE part
 *-------------------------------------------------------------------------------------------------------
 */
//Procedures and functions needed for this interface work. 

void uart_init(void);

void uart_write_char(char data);

void uart_send_array(char* data);

/*-------------------------------------------------------------------------------------------------------
 *	I2C HARDWARE part
 *-------------------------------------------------------------------------------------------------------
 */
//Procedures and functions needed for this interface work. 

void i2c_init(void);

void i2c_start_operation(void);

void i2c_stop_operation(void);

void i2c_send_byte(uint8_t byte);

void i2c_send_data(uint8_t data, uint8_t addres);

void i2c_send_array(uint8_t &arr_start, uint8_t lenght);

uint8_t i2c_reseive_byte(void);

uint8_t i2c_reseive_last_byte(void);

#endif /* STANDART_INTERFACE_H_ */