#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#define indicator_port PORTD
#define digita PORTB

unsigned int digit,amp,hgr,dec,uni,volt,adc,data,ini = 0;
int voltage,amparage,acpd;


int symbol(int x);

//Функція стартової ініціалізації периферії
void initial(void)
{
	//Ініціалізація таймера 0 для виведення даних на семисегментні індикатори 	
	TCCR0 = (1 << CS01)|(1 << CS00); //попереднє розділення на 128 8МГц/128/265 - переповнень за секунду
	TIMSK = (1 << TOIE0);			//увімкнемо переривання по переповненню
	
	//Ініціалізація АЦП
	
	ADMUX = (1 << REFS0); //опорна напруга 5в/активний вхід АЦП5
	ADCSRA |= (1<<ADEN)  | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0)| (1<<ADSC);
	//Дозволити глобальні переривання
	sei();
	
	//Ініціалізація портів введення/виведення
	DDRD = 0xff;
	DDRB = 0xff;
	return;
}
//Функція формування символів на семисегментному індикаторі
int sybmol(int x)
{
	switch (x)
	{
		// 0
		case 0:
			indicator_port = 0b00111111;
			break;
		// 1
		case 1:
			indicator_port = 0b00001001;
			break;
		// 2
		case 2:
			indicator_port = 0b01011110;
			break;
		// 3
		case 3:
			indicator_port = 0b01011011;
			break;
		// 4
		case 4:
			indicator_port = 0b01101001;
			break;
		// 5
		case 5:
			indicator_port = 0b01110011;
			break;
		// 6
		case 6:
			indicator_port = 0b01110111;
			break;
		// 7
		case 7:
			indicator_port = 0b00011001;
			break;
		// 8
		case 8:
			indicator_port = 0b01111111;
			break;
		// 9
		case 9:
			indicator_port = 0b01111011;
			break;
		// А
		case 10:
			indicator_port = 0b01111101;
			break;
		// В
		case 11:
			indicator_port = 0b01111111;
			break;
		// С
		case 12:
			indicator_port = 0b00110110;
			break;
		// D
		case 13:
			indicator_port = 0b00111111;
			break;
		// E
		case 14:
			indicator_port = 0b01110110;
			break;
		// F
		case 15:
			indicator_port = 0b01110100;
			break;
		// G
		// H
		// I
		// J
		// L
		// O
		// P
		// S
		// U
		// Y
		// b
		// c
		// d
		// h
		// i
		// n
		// o
		// r
		// u
		// мю
		// ета
		// minus
		// point
		// degree
		
			return(x);
	}
}
//Обробник переривань по переповненню таймера 0
//Обробник формує для виведення та виводить дані на семисегментні індикатори
ISR (TIMER0_OVF_vect)
{
		hgr = amparage/100;
		dec = (amparage%100)/10;
		uni = (amparage%100)%10;
	
	digita = 0;
	digit++; 
	
	if(digit > 5)
	digit = 0;
	
	switch(digit)
	{
		case 1:
		digita = 1;
		sybmol(hgr);
		break;
		case 2:
		digita = 2;
		sybmol(dec);
		break;
		case 3:
		sybmol(uni);
		digita = 4;
		break;
		case 5:
		sybmol(10);
		digita = 16;
		break;
	}
}

ISR (ADC_vect)
{
	data = ADCW;
}

int main(void)
{
	if(ini == 0)
	{
	ini ++;
	initial();
	}	
	while(1)
	{
		if(adc<data)
		adc = data;
	amparage = adc;
	ADCSRA |= (1<<ADSC);
	}	
}