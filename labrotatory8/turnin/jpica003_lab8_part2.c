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
	ADC_init();
	
    while (1) 
    {
		unsigned short adc_reg = ~ADC;
		unsigned char fir8 = (char)adc_reg;
		PORTB = fir8;
		unsigned char last = (char)(adc_reg>>8);
		PORTD = last;
	}
	return 1;
}
