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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char cntavail = 0;
    while (1) {
		if(PINA & 0x01) {
			cntavail++;
		} 
		if(PINA & 0x02) {
			cntavail++;
		}
		if(PINA & 0x04) {
			cntavail++;
		}
		if(PINA & 0x08) {
			cntavail++;
		}
		if (PINA & 0x10) {
			cntavail++;
		}
		if (PINA & 0x20) {
			cntavail++;
		}
		if (PINA & 0x40) {
			cntavail++;
		}
		if (PINA & 0x80) {
			cntavail++;
		}
		if(PINB & 0x01) {
			cntavail++;
		} 
		if(PINB & 0x02) {
			cntavail++;
		}
		if(PINB & 0x04) {
			cntavail++;
		}
		if(PINB & 0x08) {
			cntavail++;
		}
		if (PINB & 0x10) {
			cntavail++;
		}
		if (PINB & 0x20) {
			cntavail++;
		}
		if (PINB & 0x40) {
			cntavail++;
		}
		if (PINB & 0x80) {
			cntavail++;
		}
		PORTC = cntavail;
		cntavail = 0;
	}
    return 1;
}
