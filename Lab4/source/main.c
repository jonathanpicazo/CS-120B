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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {init, start, increment, decrement} state;
void tick(){
    switch(state){ 
        case init:
            state = start; 
            break;
        case start:
            if (PINA == 0x01) {
                state = increment;
            }
            else if (PINA == 0x02) {
                state = decrement;
            }
            else if (PINA == 0x03) {
                state = init;
            }
            else {
                state = start;
            }
            break;
        case increment:
            if (PINA == 0x01 && (PORTC < 0x0A)) { 
                state = increment; 
            }
            else if (PINA == 0x02 && (PORTC >= 0x00)){
                state = decrement;
            }
            else if (PINA == 0x03) {
                state = init;
            }
            else {
                state = init;
            }
            break;
        case decrement:
            if (PINA == 0x01 && (PORTC < 10)) { 
                state = increment; 
            }
            else if (PINA == 0x02 && (PORTC >= 0)){
                state = decrement;
            }
            else if (PINA == 0x03) {
                state = init;
            }
            else {
                state = init;
            }
            break;
        default:
            break;
    }
    switch(state) {
        case (init):
            break; 
        case (start):
            PORTC = 0x07;
            break; 
        case (increment):
            ++PORTC;
            break;
        case (decrement) :
            --PORTC;
            break;
        default:
            break;
    }
 }

int main() {
    state = start;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00; 
    while(1) {
        tick();
    }
}
