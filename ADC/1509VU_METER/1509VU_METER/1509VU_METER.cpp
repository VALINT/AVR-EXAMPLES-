#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <math.h>

int adc,out,ini;

void initialization ()
{
	//Ініціалізація АЦП
	ADMUX = (1 << REFS0); //опорна напруга 5в/активний вхід АЦП0
	ADCSRA |= (1<<ADEN)  | (1<<ADIE) | (1<<ADPS0)| (1<<ADSC);
	//Дозволити глобальні переривання
	sei();
	
	//Ініціалізація портів
	DDRD = 0xff;
	PORTD = 0x00;
	
	ini = 1;
}


ISR (ADC_vect)   //вектор переривання АЦП
{
	adc = ADCW;
}
int main(void)
{
	// Початкова ініціалізація мікроконтролера
	if(ini == 0)
	initialization();
	
 while(1)		//процедура обробки виведення  саме на світлодіодний стовпчик
    {
      PORTD = 0x00;
		if(adc > 5){
		PORTD |= (1 << PD0);
		_delay_ms(2);}
		if(adc > 15){
		PORTD |= (1 << PD1);
		_delay_ms(2);}
		if(adc > 30){
		PORTD |= (1 << PD2);
		_delay_ms(2);}
		if(adc > 45){
		PORTD |= (1 << PD3);
		_delay_ms(2);}
		if(adc > 60){
		PORTD |= (1 << PD4);
		_delay_ms(2);}
		if(adc > 75){
		PORTD |= (1 << PD5);
		_delay_ms(2);}
		if(adc > 90){
		PORTD |= (1 << PD6);
		_delay_ms(2);}
		if(adc > 105){
		PORTD |= (1 << PD7);
		_delay_ms(2);}
		ADCSRA |= (1 << ADSC);		   
    } 
   
 /*  while(1)
   {
	   out++;
	   PORTD = out;
	   _delay_ms(500);
	   if(out > 256)
	   out = 0;
   }
   */
}