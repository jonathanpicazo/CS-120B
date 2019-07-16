/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 6:  Exercise 2
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
  unsigned char input = 0x00;
  unsigned char temp = 0x00;
  enum States{init, light1, wait1, light2, wait2, light3, wait3}state;
  void TimerOn() {
	  TCCR1B = 0x0B;
	  OCR1A = 125;
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
  void tick(){
	switch (state){
		case init:
			state = light1;
			break;
		case light1:
			if (input){
				state = wait1;
			}
			else{
				state = light2;
			}
			break;
		case wait1:
			if (input){
				state = light1;
			}
			else{
				state = wait1;
			}
			break;
		case light2:
			if (input){
				state = wait2;
			}
			else{
				state = light3;
			}
			break;
		case wait2:
			if (input){
				state = light2;
			}
			else {
				state = wait2;
			}
			break;
		case light3:
			if (input){
				state = wait3;
			}
			else{
				state = light1;
			}
			break;
		case wait3:
			if(input){
				state = light3;
			}
			else{
				state = wait3;
			}
			break;
	}
	switch (state){
		case init:
			break;
		case light1:
			temp = 0x01;
			break;
		case wait1:
			temp = 0x01;
			break;
		case light2:
			temp = 0x02;
			break;
		case wait2:
			temp = 0x02;
			break;
		case light3:
			temp = 0x04;
			break;
		case wait3:
			temp = 0x04;
			break;

	}
  }
  

  int main() {
	  DDRB = 0xFF; PORTB = 0x00;
	  DDRA = 0x00; PORTA = 0xFF;
	  TimerSet(25);
	  TimerOn();
	  state = init;

	  while(1) {
	  	input = ~PINA & 0x08;
	  	tick();
	  	while (!TimerFlag);
	  	TimerFlag = 0;
	  	PORTB = temp;  
	  }
	  return 0;
}
