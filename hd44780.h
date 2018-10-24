/*
 * hd44780.h
 *
 *  Created on: 22 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

#ifndef HD44780_H_
#define HD44780_H_

// helper macros

#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)

#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)

#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

// LCD connections

#define D4_PORT	C
#define D4_LINE	3
#define D5_PORT	C
#define D5_LINE	4
#define D6_PORT	C
#define D6_LINE	5
#define D7_PORT	C
#define D7_LINE	6

#define RS_PORT	C
#define RS_LINE	0
#define E_PORT	C
#define E_LINE	2
#define USE_RW 1 // set to 0 in RW is short to ground
#if USE_RW == 1
#define RW_PORT	C
#define RW_LINE	1
#endif

// LCD commands

#define CLEAR					0x01

#define HOME					0x02

#define ENTRY_MODE				0x04
#define EM_SHIFT_CURSOR			0
#define EM_SHIFT_DISPLAY		0x01
#define EM_DECREMENT			0
#define EM_INCREMENT			0x02

#define DISPLAY_ONOFF			0x08
#define DISPLAY_OFF				0
#define DISPLAY_ON				0x04
#define CURSOR_OFF				0
#define CURSOR_ON				0x02
#define CURSOR_NOBLINK			0
#define CURSOR_BLINK			0x01

#define DISPLAY_CURSOR_SHIFT	0x10
#define SHIFT_CURSOR			0
#define SHIFT_DISPLAY			0x08
#define SHIFT_LEFT				0
#define SHIFT_RIGHT				0x04

#define FUNCTION_SET			0x20
#define FONT5x7					0
#define FONT5x10				0x04
#define ONE_LINE				0
#define TWO_LINE				0x08
#define FOUR_BIT				0
#define EIGHT_BIT				0x16

#define CGRAM_SET				0x40

#define DDRAM_SET				0x80

#define BUSY					0x80

void lcd_init(void);

void lcd_clear(void);
void lcd_home(void);

//void lcd_goto(uint8_t pos);

void lcd_command(uint8_t cmd);
uint8_t lcd_status(void);

void lcd_write_data(uint8_t data);
uint8_t lcd_read_data(void);

void lcd_putchar(char c);
void lcd_putstring(char *s);

void lcd_putint(int value);

#endif /* HD44780_H_ */
