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


enum States {init, lock, lock1, unlock} state;
void tick(){
    switch(state){ 
        case(init): 
            state = lock;
            break;
        case (lock):
            if ((PINA & 0x04) == 0x04) {
                state = lock1;
            }
            else {
                state = lock;
            }
            break;
        case (lock1):
            if ((PINA & 0x02) == 0x02) {
                state = unlock;
            }
            else if (!PINA) {
                state = lock1;
            }
            else {
                state = lock;
            }
            break;
        case (unlock):
            if ((PINA & 0x80) == 0x80) {
                state = lock;
            }
            else {
                state = unlock;
            }
        default:
            break;
    }
    switch (state) {
        case (init):
            break;
        case (lock):
            break;
        case(lock1):
            break;
        case (unlock):
            PORTB = 0x01;
            break;
        default:
            break;
    }
 }

int main(void) {
    state = init;
    DDRA = 0x00; PORTA = 0xFF;
    DDRB= 0xFF; PORTB = 0x00;
    while(1) {
        tick();
    }
}
