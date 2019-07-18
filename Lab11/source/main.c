/*	Author: wchan051
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 11  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
//#include "simAVRHeader.h"
#include "Keypad.h"
#include "io.h"
#include <stdio.h>
#include "scheduler.h"
#include "timer.h"


//#include "bit.h"
//#include "io.c"



const unsigned long tasksPeriod = 500;
const unsigned long tasksPeriodGCD = 250;
const unsigned char tasksNum = 1;

unsigned char size = 37;
unsigned char screenSize = 31;
unsigned char myString[] = "CS120B is Legend... wait for it DARY!";
enum SM_scroll {SM_start, SM_advance, SM_clear} mySM;
	
task myTask;

int myTick (int state) {
	unsigned char window = 16;
	unsigned char stringIndex = 0;
	static unsigned char currentStart = 0;
	switch(state) {
		case SM_start:
			state = SM_advance;
			break;
		case SM_advance:
			if (currentStart + window - 1 < size) {
				state = SM_advance;
			} else {
				state = SM_clear;
			}
			break;
		case SM_clear:
			state = SM_advance;
			break;
		default:
			state = SM_start;
			break;
	}
	switch(state) {
		case SM_advance:
			stringIndex = currentStart;
			unsigned char p = 0;
			while(p < window) {
				LCD_Cursor(p + 1);
				if (stringIndex >= size) {
					LCD_WriteData(' ');
				} else {
					LCD_WriteData(myString[stringIndex]);
				}
				stringIndex++;
				p++;
			}
			currentStart++;
			break;
		case SM_clear:
			currentStart = 0;
			LCD_ClearScreen();
			break;
	}
	return state;
}


int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	 LCD_init();
	 
	myTask.state = SM_start;
	myTask.period = tasksPeriod;
	myTask.elapsedTime = 0;
	myTask.TickFct = &myTick;

	TimerSet(tasksPeriodGCD);
	TimerOn();
    while (1) 
    {
		while(!TimerFlag) {
			
		}
		
		//if (myTask.elapsedTime >= myTask.period) {
			myTask.state = myTask.TickFct(myTask.state);
			//myTask.elapsedTime = 0;
		//}
		//myTask.elapsedTime += tasksPeriodGCD;
		
		TimerFlag = 0;
    }
}
