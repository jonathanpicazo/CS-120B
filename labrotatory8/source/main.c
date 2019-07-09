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
	unsigned short max = 0x11F;
	unsigned char tmpB = 0x00;
	
    while (1) 
    {
		unsigned short adc_reg = ADC;
		if (adc_reg > max) {
			max = adc_reg;
		}
		if (adc_reg >= max / 2) {
			tmpB = 0x01;
		}
		else {
			tmpB = 0x00;
		}
		PORTB = tmpB;
	}
	return 1;
}
