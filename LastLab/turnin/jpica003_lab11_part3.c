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
#include <stdio.h>
#include "io.h"
//#include "bit.h"
#include "scheduler.h"
#include "Keypad.h"
#include "timer.h"

unsigned char x = 0x1F;
unsigned char get_value;
unsigned char temp = 0;
unsigned char temp2 = 0;
enum states {init, get, off} state;
int Tick(int state)
{
	switch (state)
	{
		case init:
			if (x == 0x1F)
			{
				state = init;
			}
			else if (x != 0x1F)
			{
				state = get;
			}
			break;
		
		case get:
			if (x != 0x1F)
			{
				state = get;
			}
			else if (x == 0x1F)
			{
				state = off;
			}
			break;
		
		case off:
			state = init;
			break;
		
		default:
			state = init;
			x = 0x1F;
			break;
	}
	switch (state)
	{
		case init:
			x = GetKeypadKey();
			break;
		
		case get:
			x = GetKeypadKey();
			temp = GetKeypadKey();
			break;
		
		case off:
			temp2 = temp;
			break;
		
		default:
		break;
	}

	
	return state;
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	//unsigned long int SMTick1_calc = 50;
	unsigned long int SMTick1_period = 50;

	static task task_LCD;
	task *tasks[] = { &task_LCD };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task_LCD.state = -1;
	task_LCD.period = SMTick1_period;
	task_LCD.elapsedTime = SMTick1_period;
	task_LCD.TickFct = &Tick;
	
	TimerSet(50);
	TimerOn();
	
	
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	
	LCD_init();
	LCD_ClearScreen();
	LCD_Cursor(1);
	
	unsigned char Display_Letters = 0;
	while(1)
	{ 	
		// Scheduler code
		unsigned short counter = 0;
		while (counter < numTasks) {
			// Task is ready to tick
			if ( tasks[counter]->elapsedTime == tasks[counter]->period ) {
				// Setting next state for task
				tasks[counter]->state = tasks[counter]->TickFct(tasks[counter]->state);
				// Reset elapsed time for next tick.
				tasks[counter]->elapsedTime = 0;
			}
			tasks[counter]->elapsedTime += 1;
			++counter;
		}
		
	
		switch (temp)
		{
			LCD_ClearScreen();
			// All 5 LEDs on
			case '\0': PORTB = 0x1F; break;
			// hex equivalent
			case '1': PORTB = 0x01; Display_Letters = 1; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '2': PORTB = 0x02; Display_Letters = 2; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '3': PORTB = 0x03; Display_Letters = 3; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '4': PORTB = 0x04; Display_Letters = 4; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '5': PORTB = 0x05; Display_Letters = 5; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '6': PORTB = 0x06; Display_Letters = 6; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '7': PORTB = 0x07; Display_Letters = 7; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '8': PORTB = 0x08; Display_Letters = 8; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '9': PORTB = 0x09; Display_Letters = 9; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			case '0': PORTB = 0x00; Display_Letters = 0; LCD_Cursor(1); LCD_WriteData(Display_Letters + '0'); break;
			// . . . ***** FINISH *****
			case 'A': PORTB = 0x0A; Display_Letters = 65; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			case 'B': PORTB = 0x0B; Display_Letters = 66; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			case 'C': PORTB = 0x0C; Display_Letters = 67; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			case 'D': PORTB = 0x0D; Display_Letters = 68; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			case '*': PORTB = 0x0E; Display_Letters = 42; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			case '#': PORTB = 0x0F; Display_Letters = 35; LCD_Cursor(1); LCD_WriteData(Display_Letters); break;
			// Should never occur. Middle LED off.
			default: PORTB = 0x1B; break;
		

			while (!TimerFlag);
			TimerFlag = 0;
		}
	}
}
