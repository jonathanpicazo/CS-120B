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


enum States {init, wait, light0};
enum States state;
void tick(){
    unsigned char input = PINA;
    switch(state){ 
        case(init): 
            state = wait;
            break;
        case(wait):
            if (input) { 
                input = 0;
                state = light0; 
            }
            else if (!input) {
                state = wait;
            }
            break;
        case(light0):
            if (input) {
                input = 0;
                state = wait;
            }
            else if (!input) {
                state = light0;
            }
            break;
        default:
            break;
    }
    switch(state) { 
        case(wait):
            PORTB = 0x01;
            break;
        case(light0):
            PORTB = 0x02; 
            break;
        default:
            break;
    }
 }

int main() {
    state = init;
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00; 
    while(1) {
        tick();
    }
}
