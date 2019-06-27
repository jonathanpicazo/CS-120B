/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    while (1) {
		if(PINA == 0x01 || PINA == 0x02) {
			PORTC = 0x20;
		}
		if(PINA == 0x03 || PINA == 0x04) {
			PORTC = 0x30;
		}
		if(PINA == 0x05 || PINA == 0x06) {
			PORTC = 0x38;
		}
		if(PINA == 0x07 || PINA == 0x08 || PINA == 0x09) {
			PORTC = 0x3C;
		}
		if(PINA == 0x0A || PINA == 0x0B || PINA == 0x0C) {
			PORTC = 0x3E;
		}
		if(PINA == 0x0D || PINA == 0x0E || PINA == 0x0F) {
			PORTC = 0x3F;
		}
    }
    return 1;
}
