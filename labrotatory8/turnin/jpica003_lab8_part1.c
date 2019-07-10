#include <avr/io.h>
#include <avr/interrupt.h>



void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTC = 0x00;

	
	volatile unsigned short my_short = 0;
	volatile unsigned char lower8 = 0; // my_char = 0xCD
	volatile unsigned char upper2 = 0;
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
