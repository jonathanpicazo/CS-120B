/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	LCD_init();
	LCD_DisplayString(1, "Wayland is gay");
	while(1) {continue;}
}
