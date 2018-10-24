/*
 * test3.c
 *
 *  Created on: 24 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

#include "hd44780.h"

uint16_t pomiar (uint8_t kanal);


int main(void){

	// podswietlenie HD44780
	DDRC |= (1<<PC7);
	PORTC |= (1<<PC7);

	lcd_init();
	lcd_putint(1025);

	ADMUX |= (1<<REFS0);

	ADCSRA |= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);

	while(1){
		lcd_clear();
		lcd_putint(pomiar(0));
		_delay_ms(200);
	}

	return 0;
}

uint16_t pomiar(uint8_t kanal){
	ADMUX = (ADMUX&0xF8)|kanal;
	ADCSRA |= (1<<ADSC);

	while(ADCSRA & (1<<ADSC));

	return ADCW;
}
