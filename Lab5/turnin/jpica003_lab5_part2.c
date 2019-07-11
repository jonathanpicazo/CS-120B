/*	Author: jpica003
 *  Partner(s) Name: Jonathan Picazo and Wayland Chang
 *	Lab Section:
 *	Assignment: Lab 5:  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {init, wait, increment, decrement, reset} state;
void tick(){
    unsigned char input = PINA;
    switch(state){ 
        case(init): 
            PORTC = 0x07;
            state = wait;
            break;
        case(wait):
            if ((input & 0x03) == 0x03) {
                state = reset;
            }
            else if ((input & 0x01) == 0x01) { 
                state = increment; 
            }
            else if ((input & 0x02) == 0x02) {
                state = decrement;
            }
            else {
                state = wait;
            }
            break;
        case(increment):
            break;
        case (decrement):
            break;
        case (reset):
            break;
        default:
            break;
    }
    switch(state) { 
        case(init):
            break;
        case (wait):
            break;
        case(increment):
            if (PORTC < 0x09) {
                PORTC = PORTC + 1;
            }
            break;
        case (decrement):
            if (PORTC > 0) {
                --PORTC;
            }
            break;
        case (reset):
            PORTC = 0x07;
        default:
            break;
    }
    state = wait;
 }

int main(void) {
    state = init;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
 
    while(1) {
        tick();
    }
}
