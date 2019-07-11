#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/io.h>
#include <avr/interrupt.h>

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

unsigned char tmp1;
unsigned char tmp2;

enum States1 {Start3, LED0, LED1, LED2} Three_LEDs;
void Tick_threeLEDs() {
	switch (Three_LEDs) {
		case Start3:
		Three_LEDs = LED0;
		break;
		
		case LED0:
		Three_LEDs = LED1;
		break;
		
		case LED1:
		Three_LEDs = LED2;
		break;
		
		case LED2:
		Three_LEDs = LED0;
		break;
		
		default:
		break;
	}
	
	switch (Three_LEDs) {
		case LED0:
		tmp1 = 0x01;
		break;
		
		case LED1:
		tmp1 = 0x02;
		break;
		
		case LED2:
		tmp1 = 0x04;
		break;
	}
}

enum States2 {StartBlinker, LED_ON, LED_OFF} Blinking_LED;
void Tick_Blinking() {
	switch (Blinking_LED) {
		case StartBlinker:
		Blinking_LED = LED_ON;
		break;
		
		case LED_ON:
		Blinking_LED = LED_OFF;
		break;
		
		case LED_OFF:
		Blinking_LED = LED_ON;
		break;
		
		default:
		break;
	}
	
	switch (Blinking_LED) {
		case LED_ON:
		tmp2 = 0x08;
		break;
		
		case LED_OFF:
		tmp2 = 0x00;
		break;
	}
}

enum States3 {Start_Combine, Case1, Case2, Case3} Combine_LEDs;
void Tick_Combine() {
	switch (Combine_LEDs) {
		case Start_Combine:
		Combine_LEDs = Case1;
		break;
		
		case Case1:
		Combine_LEDs = Case2;
		break;
		
		case Case2:
		Combine_LEDs = Case3;
		break;
		
		case Case3:
		Combine_LEDs = Case1;
		break;
		
		default:
		break;
	}
	
	switch (Combine_LEDs) {
		case Case1:
		PORTA = tmp1 + tmp2;
		break;
		
		case Case2:
		PORTA = tmp1 + tmp2;
		break;
		
		case Case3:
		PORTA = tmp1 + tmp2;
		break;
	}
}

void main()
{

	DDRA = 0xFF; PORTA = 0x00;
	TimerSet(1000);
	TimerOn();
	while(1)
	{
		Tick_threeLEDs();
		Tick_Blinking();
		Tick_Combine();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
