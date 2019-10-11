//-------------------------------------------------------------------------------------------------------------------------*
//  Actual version: 0.3B
//
//  
//	Author: VAL
//	Created: 27 Sep 2019
//_________________________________________________________________________________________________________________________*
//	
//	Story of versions:
//_________________________________________________________________________________________________________________________*
//
//	V.0.1 (Beta):
//		-Plays only one track whose name hardcoded in flash memory.
//		-Exist problems with playing speed.
//
//	V.0.2 (Beta)
//		-Device still plays only one track whose name hardcoded in flash memory.
//		-Playing speed is 32Ks. but I know how to regulate it. 
//
//	v.0.3 (Beta)
//		-Device plays track by track sequently. 
//		-Playing speed for each track reads from RIFF header
//		-Still plays only 8bit mono
//		-Exist problems with track duration definition and player 
//		    automatically switch some tracks on next. 
//_________________________________________________________________________________________________________________________*
//
//	Additional materials:
//_________________________________________________________________________________________________________________________*
//
//	Petit FatFs - R0.02a from ChaN
//-------------------------------------------------------------------------------------------------------------------------*
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "standart_interface.h"
#include "diskio.h"
#include "pff.h"

/* выводы микроконтроллера */

#define LED_PORT   PORTD
#define LED_DIR    DDRD
#define LED_PIN    4
#define BUTTON_PIN 2

#define PWM_PORT   PORTB
#define PWM_DIR    DDRB
#define PWM_PIN    1

/* буфер */

#define BUF_SIZE    512UL
#define HALF_BUF   ((BUF_SIZE)/2)
#define _USE_DIR

typedef struct wav_data
{
	uint16_t size;
	uint8_t chan;
	uint16_t sampleRate;
	uint8_t timerCoef;
} WAV;
uint8_t isBegin(uint8_t *buffer)
{
	return (uint8_t)(((*(buffer) == 'R') && (*(buffer+1) == 'I') && (*(buffer+2) == 'F') && (*(buffer+3) == 'F')));
}

void setSize(uint8_t *buffer, WAV *obj)
{
	uint32_t temp = ((uint32_t)(*(buffer+7))|(((uint32_t)*(buffer+6))<<8)|(((uint32_t)*(buffer+5))<<16)|(((uint32_t)*(buffer+4))<<24));
	obj->size = (uint16_t)(temp>>9);
}

void decSize(WAV *obj)
{
	obj->size--;
}

void setFormat(uint8_t *buffer, WAV *obj)
{
	obj->chan = *(buffer+22);
	obj->sampleRate = (((uint16_t)(*(buffer + 25)))<<8) | *(buffer+24);
	obj->timerCoef = (uint8_t)(2000000/obj->sampleRate);
}

uint8_t buf[BUF_SIZE];

/*переменные для доступа к SD*/

FATFS fs;
DIR dir;
FILINFO fno;
WORD s1;
FRESULT res;

volatile uint16_t sell = 0;
char name0[13];


ISR(TIMER0_OVF_vect)
{
	OCR1A = buf[sell];
	LED_PORT = (1<<LED_PIN);
	
	if(sell == 511)
		sell = 0;
	else 
		sell ++;
}

ISR(TIMER2_COMP_vect)
{
	TCNT2 = 0;
	OCR1A = buf[sell];
	LED_PORT = (1<<LED_PIN);
	
	if(sell == 510)
	sell = 0;
	else
	sell ++;
}

int isWAV(char *string);

int main( void )
{
	uint16_t sells = 0;
	WAV player;
  /*настройка шим выхода*/
	PWM_DIR |= (1<<PWM_PIN);
	PWM_PORT &= ~(1<<PWM_PIN);
  
  /*статусный светодиод*/
	LED_DIR |= (1<<LED_PIN);
	LED_PORT &= ~(1<<LED_PIN);
	
  
  uart_init();
  /*монтируем диск, открываем файл и заполняем весь буфер*/
	res = pf_mount(&fs);
	uart_write_char('1');
	if (res == FR_OK)
	{
		
blet_blet:
		uart_write_char('2');
		res = pf_opendir(&dir,"");
			if(res == FR_OK)
			{
blet:			
				uart_write_char('3');	
				res = pf_readdir(&dir,&fno);
				if(res == FR_OK)
				{
					for(uint8_t i = 0; i < 13; i++)
					{
						name0[i] = fno.fname[i];
					}	
				}
				int temp = isWAV(&name0);
				if(temp == 0)
					goto blet;
				else if(temp == -1)
					goto blet_blet;		
						
			}		
			uart_write_char('4');
			res = pf_open(name0);    
			if (res == FR_OK)
			{
				uart_write_char('5');
				res = pf_read(buf, BUF_SIZE, &s1);
				if(isBegin(&buf))
					uart_write_char('6');
					setSize(&buf, &player);
					setFormat(&buf, &player);
					uart_write_char(player.sampleRate>>8);
					uart_write_char(player.sampleRate);					
			}
		}
		if (res == FR_OK && player.size != 0){
		uart_write_char('7');
		TCCR2 |= (1 << CS21);
		TIMSK |= (1 << OCF2);
		OCR2 = player.timerCoef;
		TCCR1A |= (1 << COM1A1)|(1 << WGM10);
		TCCR1B |= (1 << WGM12)|(1 << CS10);
	  
		asm("sei");
	}
	else
	{
  /*в противном случае зацикливаемся
    и мигаем светодиодом */
		while(1)
		{
			LED_PORT ^= (1<<LED_PIN);
			_delay_ms(300);
		}
	}
		
	if(isBegin(&buf))
	{
		setSize(&buf, &player);
		setFormat(&buf, &player);
	}
	while(1)
	{
	if(sell == 510){
		pf_read(buf, BUF_SIZE, &s1);
		decSize(&player);
	}		
		if(!(PIND & (1 << BUTTON_PIN)))
		{
			asm("cli");
			_delay_ms(1000);
			goto blet;	
		}
		if(player.size == 0)
		{
			asm("cli");
			_delay_ms(2500);
			goto blet;			
		}			
	}
	return 0;
}

int isWAV(char *string)
{
	for(uint8_t i = 0; i < 13; i++)
	{
		if(*(string+i) == '\0')
		{
			if(i == 0)
				return -1;
			return 0;
		}			
		else if(((*(string+i) == '.') && (*(string+i+1) == 'W') && (*(string+i+2) == 'A') && (*(string+i+3) == 'V'))||
				((*(string+i) == '.') && (*(string+i+1) == 'w') && (*(string+i+2) == 'a') && (*(string+i+3) == 'v')))
			return 1;	
	}
}
