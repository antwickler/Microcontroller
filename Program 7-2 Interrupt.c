#include<avr/io.h>
#include<avr/interupt.h>

unsigned char LOOKUPTB[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 
							0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
unsigned char switch;

int main(void) {
	DDRB = 0x00;
	DDRC = 0xFF;
	sei();
	PCICR = 0x01;
	PCMSK0 = 0x0F;
	switchtodisplay();

	while(1) {
		;
	}
}

ISR(INT0_vect) {
	switch = PINB;
	switch &= 0x0F;
	PORTC = ~(LOOKUPTB[switch]);
}

switchtodisplay {
	switch = PINB;
	switch &= 0x0F;
	PORTC = ~(LOOKUPTB[switch]);
}