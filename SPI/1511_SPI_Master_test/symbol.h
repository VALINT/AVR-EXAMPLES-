void symbol (int sym)				// Функція виводу символа на семисегментний індикатор
{
	switch (sym)
	{
		case 0:
		PORTD = 0b00111111;			//(0)
		break;
		case 1:
		PORTD = 0b00001001;			//(1)
		break;
		case 2:
		PORTD = 0b01011110;			//(2)
		break;
		case 3:
		PORTD = 0b01011011;			//(3)
		break;
		case 4:
		PORTD = 0b01101001;			//(4)
		break;
		case 5:
		PORTD = 0b01110011;			//(5)
		break;
		case 6:
		PORTD = 0b01110111;			//(6)
		break;
		case 7:
		PORTD = 0b00011001;			//(7)
		break;
		case 8:
		PORTD = 0b01111111;			//(8)
		break;
		case 9:
		PORTD = 0b01111011;			//(9)
		break;
	}
}