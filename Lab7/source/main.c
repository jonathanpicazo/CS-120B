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
#include <io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States{Start, init, Increment, Decrements, wait} State;
unsigned char cnt;
void Tick() {
	switch(State) {


		case Start:
		State = init;
		break;


		case init:
		if (GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = init;
		}
		else if (GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = Increment;
		}
		else if (!GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = Decrements;
		}
		else if (!GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = wait;
		}
		break;



		case Increment:
		if (GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = init;
		}
		else if (GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = Increment;
		}
		else if (!GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = Decrements;
		}
		else if (!GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = wait;
		}
		break;



		case Decrements:
		if (GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = init;
		}
		else if (GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = Increment;
		}
		else if (!GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = Decrements;
		}
		else if (!GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = wait;
		}
		break;


		case wait:
		if (GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = init;
		}
		else if (GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = Increment;
		}
		else if (!GetBit(~PINA, 0) && GetBit(~PINA, 1)) {
			State = Decrements;
		}
		else if (!GetBit(~PINA, 0) && !GetBit(~PINA, 1)) {
			State = wait;
		}
		break;
	}

	switch(State) {

		case init:
		cnt = 0;
		LCD_Cursor(1);
		LCD_WriteData('0');
		break;


		case Increment:
		if (cnt == 9) {
			break;
		}
		else if (cnt < 9) {
			cnt = cnt +1;
		}
		LCD_Cursor(1);
		LCD_WriteData(cnt + '0');
		break;


		case Decrements:
		if (cnt == 0) {
			break;
		}
		else if (cnt > 0) {
			cnt = cnt - 1;
		}
		LCD_Cursor(1);
		LCD_WriteData(cnt + '0');
		break;

		case wait:
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	State = Start;

	// Initializes the LCD display
	LCD_init();
	TimerSet(1000);
	TimerOn();
	while(1)
	{
		Tick();
		while (!TimerFlag);// BufferZone 1 sec
		TimerFlag = 0;
		continue;
	}
}