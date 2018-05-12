/*
 * Reseive164.h
 *
 * Created: 08.12.2017 16:04:49
 *  Author: VAL
 */ 


#ifndef RESEIVE164_H_
#define RESEIVE164_H_


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define First_Digit 4
#define Second_Digit 2
#define Third_Digit 5
#define CLC 0
#define DATA 1
#define DATA_PORT PORTD
#define DATA_REGISTER DDRD
  
  
  
void Sent_Number(uint8_t numb);
void Fill_Display(float value);


#endif /* RESEIVE164_H_ */