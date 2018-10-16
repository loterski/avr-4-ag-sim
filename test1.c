/*
 * test1.c
 *
 *  Created on: 16 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	int8_t value = 0; // value to modify

	DDRC = 0xff; // PortC OUT to LED
	DDRB = 0x00; // PortB IN from buttons

	PORTC = 0x00; // LEDs off
	PORTB = 0xff; // buttons on pullup

	while (1) {

		for (value = -121; 120; value += 20) {
			/*		if (PINB0 == 0)
			 value = -120;
			 if (PINB1 == 0)
			 value -= 20;
			 if (PINB2 == 0)
			 value = 0;
			 if (PINB3 == 0)
			 value += 20;
			 if (PINB3 == 0)
			 value = 120;
			 */
			if (value < -120)
				value = -120;
			if (value > 120)
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
}
