/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 9:  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

enum States {init, state_C4, state_D4, state_E4, state_F4, state_G4, state_A4, state_B4, state_C5, increment, decrement} state;
enum States_Tog {wait, toggle} toggle_switch;
unsigned char surge = 0;
unsigned char down = 0;
unsigned char up = 0;
unsigned char elec = 0;
unsigned char next = 0;
void set_PWM(double frequency) {
	static double current_frequency = -1;
	if (frequency != current_frequency) {
		if (!frequency) { 
			TCCR3B &= 0x08; 
		} 
		else { 
			TCCR3B |= 0x03; 
		}
		if (frequency < 0.954) { 
			OCR3A = 0xFFFF; 
		}
		else if (frequency > 31250) { 
			OCR3A = 0x0000; 
		}
		else { 
			OCR3A = (short)(8000000 / (128 * frequency)) - 1; 
		}
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
	down = ~PINA & 0x02;
	up = ~PINA & 0x04;
	switch (state) {
		case init:
			state = state_C4;
			break;
		case increment: 
		if (up) {
			state = increment;
		}
		else {
			++next;
			state = next;
		}
			break;
		case decrement:
			if (down) {
				state = decrement;
			}
			else {
				--next;
				state = next;
			}
			break;
		case state_C4:
			if (down) {
				state = state_C4;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_D4:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_E4:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_F4:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_G4:
			if (down) {
				next = state;
				state = decrement;
			} else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_A4:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_B4:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				next = state;
				state = increment;
			}
			break;
		case state_C5:
			if (down) {
				next = state;
				state = decrement;
			} 
			else if (up) {
				state = state_C5;
			}
			break;
		default:
			break;
	}
	switch (state) {
		case init:
			break;
		case state_C4:
			set_PWM(261.63);
			break;
		case state_D4:
			set_PWM(293.66);
			break;
		case state_E4:
			set_PWM(329.63);
			break;
		case state_F4:
			set_PWM(349.23);
			break;
		case state_G4:
			set_PWM(392.00);
			break;
		case state_A4:
			set_PWM(440.00);
			break;
		case state_B4:
			set_PWM(493.88);
			break;
		case state_C5:
			set_PWM(523.25);
			break;
	}
}

void tog() {
	elec = ~PINA & 0x01;
	switch (toggle_switch) {
		case wait: 
			if (elec) {
				toggle_switch = toggle;
			}
			break;
		case toggle:
			if (elec) {
				state = toggle_switch;
			}
			else {
				state = wait;
			}
			break;
		default:
			toggle_switch = wait;
			break;
	}
	switch (toggle_switch) {
		case wait:
			break;
		case toggle:
			if (surge) {
				surge = 0;
				PWM_off();
			} else {
				surge = 1;
				PWM_on();
			}
			break;
	}
}

int main(void) {
	DDRA = 0x00; PINA = 0xFF;
	DDRB = 0xFF; PINB = 0x00;
	state = init;
	while (1) {
		tick();
		tog();
	}
	return 0;
}