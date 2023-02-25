#include <avr/io.h>
#include "led.h"

void vLEDInit(void)
{
	DDRB |= _BV(PB5);
}

void vLEDToggle(void)
{
	PORTB ^= _BV(PB5);
}
