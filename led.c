/*
 * led.c
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "led.h"

volatile uint8_t jednosci;
volatile uint8_t dziesiatki;
volatile uint8_t setki;
volatile uint8_t znak;

const uint8_t cyfry[10] PROGMEM = { ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E
		| SEG_F), // 0
		~(SEG_B | SEG_C), // 1
		~(SEG_A | SEG_B | SEG_G | SEG_E | SEG_D), // 2
		~(SEG_A | SEG_B | SEG_G | SEG_C | SEG_D), // 3
		~(SEG_F | SEG_G | SEG_B | SEG_C), // 4
		~(SEG_A | SEG_F | SEG_G | SEG_C | SEG_D), // 5
		~(SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G), // 6
		~(SEG_A | SEG_B | SEG_C), // 7
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G), // 8
		~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G) // 9
		};

void inicjalizacja_wyswietlacza(void) {
	KATODY_DIR = 0xff; // katody jako wyjscie
	KATODY = 0xff; // pullup

	ANODY_DIR |= ZNAK | SETKI | DZIESIATKI | JEDNOSCI; // anody jako wyjscie
	ANODY |= ZNAK | SETKI | DZIESIATKI | JEDNOSCI; // pullup

	// TIMER0 do przerwania
	TCCR0 |= (1 << WGM01); // tryb CTC
	TCCR0 |= (1 << CS02) | (1 << CS00); // preskaler = 1024
	OCR0 = 38; // dodatkowy podzial przez 39 (przepelnienie)
	TIMSK |= (1 << OCIE0); // zezwolenie na przerwanie CompareMatch

}

ISR(TIMER0_COMP_vect) {
	static uint8_t blok = 1; // blok do zapalenia

	ANODY = (ANODY & 0xf0); // wygaszenie anod

	switch (blok) { // ustawienie odpowiedniego wzorca na katodach
	case 1:
		KATODY = pgm_read_byte(&cyfry[jednosci]);
		break;
	case 2:
		KATODY = pgm_read_byte(&cyfry[dziesiatki]);
		break;
	case 4:
		KATODY = pgm_read_byte(&cyfry[setki]);
		break;
	case 8:
		//KATODY = pgm_read_byte(&cyfry[znak]);
		if(znak) KATODY = ~(SEG_G);
		else KATODY = 0xff;
		break;
	}

	ANODY = (ANODY & 0xf0) | (~blok & 0x0f); // zapalenie katody dla bloku

	blok <<= 1; // przesuniecie do nastepnego bloku

	if (blok > 8)
		blok = 1;
}
