/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 9:  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

enum States {init, wait, state_C4, state_D4, state_E4} state;
unsigned char C4 = 0;
unsigned char D4 = 0;
unsigned char E4 = 0;
void set_PWM(double frequency) {
	static double current_frequency = -1;
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } 
		else { TCCR3B |= 0x03; }
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		else if (frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0; 
		current_frequency = frequency; 
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;

}

void tick() {
	C4 = ~PINA & 0x01;
	D4 = ~PINA & 0x02;
	E4 = ~PINA & 0x04;
	switch (state) {
		case init:
			state = wait;
			break;
		case wait:
			if (C4 && !D4 && !E4) {
					state = state_C4; 
					PWM_on();
					set_PWM(261.63);
			} 
			else if (D4 && !C4 && !E4) {
					state = state_D4; 
					PWM_on();
					set_PWM(293.66);
			} 
			else if (E4 && !C4 && !D4) {
					state = state_E4; 
					PWM_on();
					set_PWM(329.63);
			}
			else {
				state = wait;
			}
			break;
		case state_C4:
			if (C4 && !D4 && !E4) {
				state = state_C4;
			} 
			else {
				state = wait;
			}
			break;
		case state_D4:
			if (D4 && !C4 && !E4) {
				state = state_D4;
			} 
			else {
				state = wait;
			}
			break;
		case state_E4:
			if (E4 && !C4 && !D4) {
				state = state_E4;
			} 
			else {
				state = wait;
			}
			break;
		default:
			break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = init;
    while (1) {
		tick();
    }
	return 0;
}