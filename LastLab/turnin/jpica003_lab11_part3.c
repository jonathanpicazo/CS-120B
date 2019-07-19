/*	Author: jpica003, wchan051
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "simAVRHeader.h"
#include "io.h"
#include "scheduler.h"
#include "Keypad.h"
#include "timer.h"

unsigned char keypad = 0x1F;
unsigned char temp = 0;
unsigned char temp_two = 0;
enum States {init, get_input, null} state;
int tick(state) {
	switch (state) {
		case init:
			if (keypad == 0x1F) {
				state = init;
			}
			else if (keypad != 0x1F) {
				state = get_input;
			}
			break;
		case get_input:
			if (keypad != 0x1F) {
				state = get_input;
			}
			else if (keypad == 0x1F) {
				state = null;
			}
			break;
		case null:
			state = init;
			break;
		default:
			break;
	}
	switch (state) {
		case init:
			keypad = GetKeypadKey();
			break;
		case get_input:
			keypad = GetKeypadKey();
			temp = GetKeypadKey();
			break;
		case null:
			temp_two = temp;
			break;
		default:
		break;
	}	
	return state;
}

int main(void) {
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned long int tick_period = 50;
	static task display_task;
	task *tasks[] = { &display_task };
	const unsigned short taskSize = sizeof(tasks)/sizeof(task*);
	display_task.state = -1;
	display_task.period = tick_period;
	display_task.elapsedTime = tick_period;
	display_task.TickFct = &tick;
	TimerSet(50);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();
	LCD_Cursor(1);
	unsigned char temp_number = 0;
	while(1) { 	
		unsigned short count = 0;
		while (count < taskSize) {
			if ( tasks[count]->elapsedTime == tasks[count]->period ) {
				tasks[count]->state = tasks[count]->TickFct(tasks[count]->state);
				tasks[count]->elapsedTime = 0;
			}
			tasks[count]->elapsedTime += 1;
			++count;
		}
		switch (temp) {
			LCD_ClearScreen();
			// Int
			case '\0': PORTB = 0x1F; break;
			case '1': PORTB = 0x01; temp_number = 1; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '2': PORTB = 0x02; temp_number = 2; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '3': PORTB = 0x03; temp_number = 3; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '4': PORTB = 0x04; temp_number = 4; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '5': PORTB = 0x05; temp_number = 5; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '6': PORTB = 0x06; temp_number = 6; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '7': PORTB = 0x07; temp_number = 7; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '8': PORTB = 0x08; temp_number = 8; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '9': PORTB = 0x09; temp_number = 9; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			case '0': PORTB = 0x00; temp_number = 0; LCD_Cursor(1); LCD_WriteData(temp_number + '0'); break;
			// Char
			case 'A': PORTB = 0x0A; temp_number = 65; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			case 'B': PORTB = 0x0B; temp_number = 66; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			case 'C': PORTB = 0x0C; temp_number = 67; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			case 'D': PORTB = 0x0D; temp_number = 68; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			case '*': PORTB = 0x0E; temp_number = 42; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			case '#': PORTB = 0x0F; temp_number = 35; LCD_Cursor(1); LCD_WriteData(temp_number); break;
			default: PORTB = 0x1B; break;
			while (!TimerFlag);
			TimerFlag = 0;
		}
	}
}
