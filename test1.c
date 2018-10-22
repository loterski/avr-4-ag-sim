/*
 * test1.c
 *
 *  Created on: 16 paź 2018
 *      Author: loterski


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "led.h"

#define KEY_MIN (1<<PB4)
#define KEY_DOWN (1<<PB3)
#define KEY_ZERO (1<<PB2)
#define KEY_UP (1<<PB1)
#define KEY_MAX (1<<PB0)

int main(void) {

	int16_t value = 0; // wartosc do obslugi
	int16_t vposr1 = 0; // wartosc pomocnicza
	int16_t vposr2 = 0; // wartosc pomocnicza

//	DDRC = 0xff; // PortC OUT to LED
	DDRB = 0x00; // PortB IN from buttons

//	PORTC = 0x00; // LEDs on
	PORTB = 0xff; // buttons on pullup

	inicjalizacja_wyswietlacza();

	sei();

	while (1) {

		if (!(PINB & KEY_MIN))
			value = -999;
		if (!(PINB & KEY_DOWN)) {
			value -= 1;
			if (value < -999)
				value = -999;
		}
		if (!(PINB & KEY_ZERO))
			value = 0;
		if (!(PINB & KEY_UP)) {
			value += 1;
			if (value > 999)
				value = 999;
		}
		if (!(PINB & KEY_MAX))
			value = 999;

		if (value < 0) znak=1; else znak=0;

		jednosci = abs(value) % 10;
		vposr1 = (abs(value) - jednosci) / 10;
		dziesiatki = vposr1 % 10;
		vposr2 = (vposr1 - dziesiatki) / 10;
		setki = vposr2 % 10;

		if (value < 0) znak=1; else znak=0;

		_delay_ms(200);

	}
}
*/

