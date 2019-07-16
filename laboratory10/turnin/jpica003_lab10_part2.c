/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

  void TimerOn() {
	  TCCR1B = 0x0B;
	  OCR1A = 125;
	  TIMSK1 = 0x02; 
	  TCNT1 = 0;
	  _avr_timer_cntcurr = _avr_timer_M;
	  SREG |= 0x80;
  }

  void TimerOff() {
	  TCCR1B = 0x00;
  }

  void TimerISR() {
	  TimerFlag = 1;
  }

  ISR(TIMER1_COMPA_vect) {
	  _avr_timer_cntcurr--;
	  if (_avr_timer_cntcurr == 0) {
		  TimerISR();
		  _avr_timer_cntcurr = _avr_timer_M;
	  }
  }

  void TimerSet(unsigned long M) {
	  _avr_timer_M = M;
	  _avr_timer_cntcurr = _avr_timer_M;
  }

unsigned char trans_one = 0;
unsigned char trans_two = 0;
unsigned char output = 0;

enum States_one {first_start, light1, light2, light3} state_triple;
void tick_threelights() {
	switch (state_triple) {
		case first_start:
		state_triple = light1;
		break;
		
		case light1:
		state_triple = light2;
		break;
		
		case light2:
		state_triple = light3;
		break;
		
		case light3:
		state_triple = light1;
		break;
		
		default:
		break;
	}
	
	switch (state_triple) {
		case first_start:
		break;
		case light1:
		trans_one = 0x01;
		break;
		
		case light2:
		trans_one = 0x02;
		break;
		
		case light3:
		trans_one = 0x04;
		break;
	}
}

enum states_two {init, on, off} blinker;
void tick_solo() {
	switch (blinker) {
		case init:
		blinker = on;
		break;
		
		case on:
		blinker = off;
		break;
		
		case off:
		blinker = on;
		break;
		
		default:
		break;
	}
	
	switch (blinker) {
		case init:
		break;
		case on:
		trans_two = 0x08;
		break;
		
		case off:
		trans_two = 0x00;
		break;
	}
}

enum states_three {puts} light_sum;
void tick_join() {
	switch(light_sum){ 
		case puts:
			break;
	}
	switch(light_sum){
		case puts:
			output = trans_one | trans_two;
			break;
	}
}



int main(void) {
	// Due to difficulties from our breadboard, 
	// we changed the output port to PORTA
	DDRA = 0xFF; PORTA = 0x00;
	unsigned long elapsed = 0;
	const unsigned long three_hundo = 300;
	unsigned long normal = 1000;

	TimerSet(three_hundo);
	TimerOn();
	state_triple = first_start;
	blinker = init;

	while(1){
		if (elapsed >= normal){
			tick_solo();
			elapsed = 0;
		}
		tick_threelights();
		tick_join();
		light_sum = puts;
		PORTA = output;
		while(!TimerFlag){}
		TimerFlag = 0;
		elapsed += three_hundo;

	}
}
