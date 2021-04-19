/*	Author: jtang073
 *  Partner(s) Name: 
 *	Lab Section: 027
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, Begin, Init, BeforeAdd, Add, BeforeSub, Sub, Reset } state;

void Tick() {
	switch (state) {
		case Start:
			state = Begin;
			break;
		case Begin:
			state = Init;
			break;
		case Init:
			if (PINA == 0x03) {
				state = Reset;
			}
			else if (PINA == 0x01) {
				state = BeforeAdd;
			}
			else if (PINA == 0x02) {
				state = BeforeSub;		
			}
			else {
				state = Init;
			}
			break;
		case BeforeAdd:
			// have use BeforeAdd so the Add state isn't counted twice
			// (PINA = 0x01 inside of Add will cause a duplicate)
			state = Add;
			break;
		case BeforeSub:
			// same reason as BeforeAdd
			state = Sub;
			break;
		case Add:
			if (PINA == 0x03) {
				state = Reset;
			}
			else if (PINA == 0x01) {
				state = Add;
			}
			else if (PINA == 0x02) {
				state = Sub;
			}
			else {
				state = Init;
			}
			break;
		case Sub:
			if (PINA == 0x03) {
				state = Reset;
			}
			else if (PINA == 0x01) {
				state = Add;
			}
			else if (PINA == 0x02) {
				state = Sub;
			}
			else {
				state = Init;
			}
			break;
		case Reset:
			if (PINA == 0x03) {
				state = Reset;
			}
			else if (PINA == 0x01) {
				state = Add;
			}
			else if (PINA == 0x02) {
				state = Sub;
			}
			else {
				state = Init;
			}
			break;
		default:
			state = Start;
			break;
	}

	switch (state) {
		case Start:
		case Begin:
			PORTC = 0x07;
			break;
		case Add:
			if (PORTC < 0x09) {
				PORTC = PORTC + 1;
			}
			break;
		case Sub:
			if (PORTC > 0x00) {
				PORTC = PORTC - 1;
			}
			break;
		case Reset:
			PORTC = 0x00;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    while (1) {
	Tick();
    }
    return 1;
}
