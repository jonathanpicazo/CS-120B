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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


// enum States {init, wait, increment, decrement, reset} state;
// void tick() {
//     unsigned char input = PINA;
//     switch(state) {
//         case init:
//             LCD_WriteData(0 + '0');
//             state = wait;
//             break;
//         case wait:
//             if ((input & 0x01) == 0x01) {
//                 state = increment;
//             }
//             else if ((input & 0x02) == 0x02) {
//                 state = decrement;
//             }
//             else if ((input & 0x03) == 0x03) {
//                 state = reset;
//             }
//             break;
//         case increment:
//             break;
//         case decrement:
//             break;
//         case reset:
//             break;
//     }
//     switch(state) {
//         case init:
//             LCD_WriteData(0 + '0');
//             break;
//         case wait:
//             break;
//         case increment:
//             if (PORTC < 0x09) {
//                 ++PORTC;
//             }
//             break;
//         case decrement:
//             break;
//         case reset:
//             PORTC = 0;
//             break;
//     }
// }

int main(void) {
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    LCD_init();
    LCD_DisplayString(1, "Hello World");
    while(1) {
        continue;
    }
}
