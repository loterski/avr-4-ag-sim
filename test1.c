/*
 * test1.c
 *
 *  Created on: 16 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

#define KEY_MIN (1<<PB4)
#define KEY_DOWN (1<<PB3)
#define KEY_ZERO (1<<PB2)
#define KEY_UP (1<<PB1)
#define KEY_MAX (1<<PB0)

int main(void) {

	int8_t value = 0; // value to modify

	DDRC = 0xff; // PortC OUT to LED
	DDRB = 0x00; // PortB IN from buttons

	PORTC = 0x00; // LEDs on
	PORTB = 0xff; // buttons on pullup

	while (1) {

		if (!(PINB & KEY_MIN))
			value = -120;
		if (!(PINB & KEY_DOWN)) {
			value -= 20;
			if (value < -120)
				value = -120;
		}
		if (!(PINB & KEY_ZERO))
			value = 0;
		if (!(PINB & KEY_UP)) {
			value += 20;
			if (value > 120)
				value = 120;
		}
		if (!(PINB & KEY_MAX))
			value = 120;

		switch (value) {
		case -120:
			PORTC = 64;
			break;
		case -100:
			PORTC = 96;
			break;
		case -80:
			PORTC = 32;
			break;
		case -60:
			PORTC = 48;
			break;
		case -40:
			PORTC = 16;
			break;
		case -20:
			PORTC = 24;
			break;
		case 0:
			PORTC = 8;
			break;
		case 20:
			PORTC = 12;
			break;
		case 40:
			PORTC = 4;
			break;
		case 60:
			PORTC = 6;
			break;
		case 80:
			PORTC = 2;
			break;
		case 100:
			PORTC = 3;
			break;
		case 120:
			PORTC = 1;
			break;
		}

		_delay_ms(200);

	}
}
