/*
 * test2.c
 *
 *  Created on: 22 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

#include "hd44780.h"

int main(void){
	DDRA |= (1<<PA0);
	PORTA |= (1<<PA0);

	lcd_init();

	int i = 0;
	while(1){

		lcd_clear();
		lcd_home();
		lcd_putstring("Liczydlo");
		_delay_ms(500);
		lcd_clear();
		lcd_home();
		lcd_putint(i);
		_delay_ms(500);
		i++;
	}
}
