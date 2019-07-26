/*	Author: jpica003, wchan051
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "simAVRHeader.h"
#include "Keypad.h"
#include "scheduler.h"
#include "timer.h"
#include "io.h"


int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	LCD_init();
	LCD_DisplayString(1, "Hello World");
	while(1) {
		continue;
	}
	return 0;
}
