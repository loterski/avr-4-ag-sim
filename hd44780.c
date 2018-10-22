/*
 * hd44780.c
 *
 *  Created on: 22 paź 2018
 *      Author: loterski
 */

#include <avr/io.h>
#include <util/delay.h>

#include "hd44780.h"

#define RS_HI 	PORT(RS_PORT) |= (1<<RS_LINE)
#define RS_LO 	PORT(RS_PORT) &= ~(1<<RS_LINE)

#if USE_RW == 1
#define RW_HI 	PORT(RW_PORT) |= (1<<RW_LINE)
#define RW_LO 	PORT(RW_PORT) &= ~(1<<RW_LINE)
#endif

#define E_HI 	PORT(E_PORT) |= (1<<E_LINE)
#define E_LO 	PORT(E_PORT) &= ~(1<<E_LINE)

static inline void _control_lines_out(void) {
	DDR(RS_PORT) |= (1 << RS_LINE);
	DDR(E_PORT) |= (1 << E_LINE);
#if USE_RW == 1
	DDR(RW_PORT) |= (1 << RW_LINE);
#endif
}

static inline void _data_lines_out(void) {
	DDR(D4_PORT) |= (1 << D4_LINE);
	DDR(D5_PORT) |= (1 << D5_LINE);
	DDR(D6_PORT) |= (1 << D6_LINE);
	DDR(D7_PORT) |= (1 << D7_LINE);
}

static inline void _data_lines_in(void) {
	DDR(D4_PORT) &= ~(1 << D4_LINE);
	DDR(D5_PORT) &= ~(1 << D5_LINE);
	DDR(D6_PORT) &= ~(1 << D6_LINE);
	DDR(D7_PORT) &= ~(1 << D7_LINE);
}

static inline void _lcd_out_nibble(uint8_t _halfbyte) {
	if (_halfbyte & (1 << 0))
		PORT(D4_PORT) |= (1 << D4_LINE);
	else
		PORT(D4_PORT) &= ~(1 << D4_LINE);
	if (_halfbyte & (1 << 1))
		PORT(D5_PORT) |= (1 << D5_LINE);
	else
		PORT(D5_PORT) &= ~(1 << D5_LINE);
	if (_halfbyte & (1 << 2))
		PORT(D6_PORT) |= (1 << D6_LINE);
	else
		PORT(D6_PORT) &= ~(1 << D6_LINE);
	if (_halfbyte & (1 << 3))
		PORT(D7_PORT) |= (1 << D7_LINE);
	else
		PORT(D7_PORT) &= ~(1 << D7_LINE);
}

void _lcd_write_byte(uint8_t _byte) {
	_data_lines_out();
#if USE_RW == 1
	RW_LO;
#endif
	E_HI;
	_lcd_out_nibble(_byte >> 4);
	E_LO;

	E_HI;
	_lcd_out_nibble(_byte);
	E_LO;

#if USE_RW == 1
	while (lcd_status() & BUSY)
		;
#else
	_delay_us(125);
#endif
}

#if USE_RW == 1
static inline uint8_t _lcd_in_nibble(void) {
	uint8_t _halfbyte = 0;
	if (PIN(D4_PORT) & (1 << D4_LINE))
		_halfbyte |= (1 << 0);
	if (PIN(D5_PORT) & (1 << D5_LINE))
		_halfbyte |= (1 << 1);
	if (PIN(D6_PORT) & (1 << D6_LINE))
		_halfbyte |= (1 << 2);
	if (PIN(D7_PORT) & (1 << D7_LINE))
		_halfbyte |= (1 << 3);
	return _halfbyte;
}

uint8_t _lcd_read_byte(void) {
	uint8_t _byte = 0;
	_data_lines_in();

	RW_HI;
	E_HI;
	_byte |= (_lcd_in_nibble() << 4);
	E_LO;

	E_HI;
	_byte |= _lcd_in_nibble();
	E_LO;

	return _byte;
}
#endif

void lcd_command(uint8_t cmd) {
	RS_LO;
	_lcd_write_byte(cmd);
}

#if USE_RW == 1
uint8_t lcd_status(void) {
	RS_LO;
	return _lcd_read_byte();
}
#endif

void lcd_write_data(uint8_t data) {
	RS_HI;
	_lcd_write_byte(data);
}

#if USE_RW == 1
uint8_t lcd_read_data(void) {
	RS_HI;
	return _lcd_read_byte();
}
#endif

void lcd_init(void) {
	_control_lines_out();
	_data_lines_out();
	_delay_ms(15);
	RS_LO;
	E_LO;
#if USE_RW == 1
	RW_LO;
#endif
	for (int i = 0; i < 3; i++) {
		E_HI;
		_lcd_out_nibble(0x03);
		E_LO;
		_delay_ms(5);
	}
	E_HI;
	_lcd_out_nibble(0x02);
	E_LO;
	_delay_ms(2);

	lcd_command(FUNCTION_SET | FONT5x7 | TWO_LINE | FOUR_BIT);
	lcd_command(DISPLAY_ONOFF | DISPLAY_OFF);
	lcd_command(CLEAR);
	lcd_command(ENTRY_MODE | EM_SHIFT_CURSOR | EM_INCREMENT);
	lcd_command(DISPLAY_ONOFF | DISPLAY_ON | CURSOR_OFF | CURSOR_NOBLINK);
}

void lcd_clear(void) {
	lcd_command(CLEAR);
	_delay_ms(2);
}

void lcd_home(void) {
	lcd_command(HOME);
	_delay_ms(2);
}

void lcd_putchar(char c) {
	lcd_write_data(c);
}

void lcd_putstring(char *s) {
	while (*s) {
		lcd_write_data(*s++);
	}

}

void lcd_putint(int value) {
	char buffer[17];
	lcd_putstring(itoa(value, buffer, 10));
}
