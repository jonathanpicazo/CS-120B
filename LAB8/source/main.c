#include <avr/io.h>


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTC = 0x00;
	
	//PORTD = 0xFF;
	//PORTB = 0xFF;
	
	volatile unsigned short my_short = 0;
	volatile unsigned char upper8 = 0; // my_char = 0xCD
	volatile unsigned char lower2 = 0;
	volatile unsigned char MAX = 0;
	ADC_init();
	
    while (1) 
    {
		my_short = ADC;
		upper2 = (char)(my_short >> 8);
		lower8 = (char)(my_short);
		
		if(my_short >= MAX/2){
			PORTB = lower8;
			PORTD = upper2;
		}
		else{
			PORTB = 0x00;
			PORTD = 0X00;
		}
    }
}