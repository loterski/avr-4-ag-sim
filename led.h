/*
 * led.h
 *
 *  Created on: 18 paź 2018
 *      Author: loterski
 */

#ifndef LED_H_
#define LED_H_

#define KATODY PORTC // katody podlaczone do portu C
#define KATODY_DIR DDRC
#define ANODY PORTD // anody podlaczone do portu D
#define ANODY_DIR DDRD

/*
  Z   S   D   J
  _   _   _   _
 |_| |_| |_| |_|
 |_| |_| |_| |_|

 */

#define JEDNOSCI (1<<PD0) // blok jednosci
#define DZIESIATKI (1<<PD1) // blok dziesiatek
#define SETKI (1<<PD2) // blok setek
#define ZNAK (1<<PD3) // blok znaku

/*
   a
f     b
   g
e     c
   d   dp

 */

#define SEG_A (1<<PC0)
#define SEG_B (1<<PC1)
#define SEG_C (1<<PC2)
#define SEG_D (1<<PC3)
#define SEG_E (1<<PC4)
#define SEG_F (1<<PC5)
#define SEG_G (1<<PC6)
#define SEG_DP (1<<PC7)

extern volatile uint8_t jednosci;
extern volatile uint8_t dziesiatki;
extern volatile uint8_t setki;
extern volatile uint8_t znak;

void inicjalizacja_wyswietlacza(void);

#endif /* LED_H_ */
