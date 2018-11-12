#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

void WDT_off(void) {
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1 << WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
	sei();
}

void WDT_Prescaler_Change(void) {
	// Turn off global interrupt
	cli();

	wdt_reset();

	/* Start timed sequence */
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	/* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
	WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP0);

	// Turn on global interrupt
	sei();
}

int main(void) {
	//WDT_Prescaler_Change();

	DDRB |= _BV(5);
	PORTB |= 0b00000000;
	wdt_enable(WDTO_4S);

	while (1) {
		PORTB ^= _BV(5);
		_delay_ms(500);
		PORTB ^= _BV(5);

		_delay_ms(3000);
		wdt_reset();
		PORTB ^= _BV(5);
		_delay_ms(100);
		PORTB ^= _BV(5);
		_delay_ms(100);
	}
}

ISR(WDT_vect) {
	PORTB ^= _BV(5);
}

