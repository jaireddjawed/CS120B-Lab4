/*	Author: lab
 *  Partner(s) Name: Jaired Jawed
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Init, S0, S1 } state;

void SM_Tick() {
	switch (state) {
		case Init:
			state = S0;
			break;
		case S0:
			// If PINA0 is pressed, switch to s1
			if (PINA == 0x01) {
				state = S1;
			} 
			else {
				state = S0;
			}
			break;
		case S1:
			// if PINA1 is pressed, switch to S0
			if (PINA == 0x01) {
				state = S0;
			}
			else {
				state = S1;
			}
			break;
		default:
			state =  Init;
			break;
	}

	switch (state) {
		case Init:
			break;
		case S0:
			PORTB = 0x01;
			break;
		case S1:
			PORTB = 0x02;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
	SM_Tick();
    }
    return 1;
}
