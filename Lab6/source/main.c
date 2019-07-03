/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo
 *	Lab Section:
 *	Assignment: Lab 4:  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main() {
    DDRB = 0xFF; PORTB = 0x00;
    while(1) {
		PORTB = PORTB & 0x01;
    }
    return -1;
}
