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

enum States { Start, B0Press, B0Release, B1Press, B1Release } state;

void SM_Tick() {
	switch (state) {
		case Start:
			state = B0Press;
			break;
		case B0Press:
			if ((PINA & 0x01) == 0x01) {
				state = B0Press;
			} 
			else {
				state = B0Release;
			}
			break;
		case B0Release:
			if ((PINA & 0x01) == 0x01) {
				state = B1Press;
			}
			else {
				state = B0Release;
			}
			break;
		case B1Press:
			if ((PINA & 0x01) == 0x01) {
				state = B1Press;
			}
			else {
				state = B1Release;
			}
			break;
		case B1Release:
			if ((PINA & 0x01) == 0x00) {
				state = B0Press;
			}
			else {
				state = B1Release;
			}
			break;
		default:
			state = B0Press;
			break;
	}

	switch (state) {
		case B0Press:
			PORTB = 0x01;
			break;
		case B0Release:
			break;
		case B1Press:
			PORTB = 0x02;
			break;
		case B1Release:
			break;
		default:
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    state = Start;

    /* Insert your solution below */
    while (1) {
	SM_Tick();
    }
    return 1;
}
