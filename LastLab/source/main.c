/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.h"
#include "bit.h"
#include "scheduler.h"
#include "timer.h"

char* str = "CS120B is Legend... wait for it DARY! ";
unsigned char count = 0;
unsigned char output[16];
int j;
enum states {init} state;
int tick_funct(state) {
	j = 0;
	while (j < 16) {
		output[j] = str[(count+j) % 38];
		++j;
	}
	count = (count + 1) % 38;
	LCD_DisplayString(1, output);
	return state;
}

int main(void) {
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned long int GCD = 20;
	unsigned long int SMTick1_period = 20;
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short taskSize = sizeof(tasks)/sizeof(task*);
	task1.state = -1;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &tick_funct;
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	unsigned short i;
	while(1) {
		i = 0;
		while (i < taskSize) {
			if ( tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
			++i;
		}
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
