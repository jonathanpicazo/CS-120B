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
//#include "simAVRHeader.h"
#include "Keypad.h"
#include "scheduler.h"
#include "timer.h"
unsigned char output = 0x00;
enum States{keypad};
int SMTick1(int state){
	unsigned char input;
	input = GetKeypadKey();
	switch(state){
		case keypad:
			switch (input) {
				case '\0': output = 0x1F; break;
				case '1': output = 0x01; break; 
				case '2': output = 0x02; break;
				case '3': output = 0x03; break;
				case '4': output = 0x04; break;
				case '5': output = 0x05; break;
				case '6': output = 0x06; break;
				case '7': output = 0x07; break;
				case '8': output = 0x08; break;
				case '9': output = 0x09; break;
				case 'A': output = 0x0A; break;
				case 'B': output = 0x0B; break;
				case 'C': output = 0x0C; break;
				case 'D': output = 0x0D; break;
				case '*': output = 0x0E; break;
				case '0': output = 0x00; break;
				case '#': output = 0x0F; break;
				default: output = 0x1B; break;
			}
			state = keypad;
			PORTB = output;
			break;
		}
		return state;
}


int main(void) {
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned long int SMTick1_calc = 20;
	unsigned long int GCD_temp = 10;
	unsigned long int GCD = GCD_temp;
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short taskSize = sizeof(tasks)/sizeof(task*);
	task1.state = 0;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &SMTick1;
	TimerSet(GCD);
	TimerOn();
	unsigned short i; 
	while(1) {
		i = 0;
		while (i < taskSize) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
			++i;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
