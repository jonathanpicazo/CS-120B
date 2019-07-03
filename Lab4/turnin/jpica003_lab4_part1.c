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


enum States {Init, light0, light1} state;
void tick(){
    switch(state){ 
        case(Init): 
            if (PINA & 0x01) { 
                state = light0; 
            }
            break;
        case(light0):
            if (PINA & 0x01) { 
                state = light1; 
            }
            else {
                state = light0;
            }
            break;
        case(light1):
            if (PINA & 0x01) {
                state = light0; 
            }
            else {
                state = light1;
            }
            break;
        default:
            break;
    }
    switch(state) { 
        case(Init):
            PORTB = 0x01;
            break;
        case(light0):
            PORTB = 0x02; 
            break;
        case(light1):
            PORTB = 0x01;
            break; 
        default:
            break;
    }
 }

int main() {
    state = Init;
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00; 
    while(1) {
        tick();
    }
}
