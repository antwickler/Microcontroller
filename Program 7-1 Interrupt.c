#include <avr/io.h>
#include <avr/interupt.h>

unsigned char LOOKUPTB[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 
							0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
unsigned char count = 0;

int main(void) {
	DDRD = 0x00;	// input
	DDRC = 0xFF;	// output
	EICRA = 0x02;
	EIMSK = 0x01;
	sei();
	PORTC = ~(LOOKUPTB[count]);

	while(1){
		;
	}
}

ISR(INT0_vect) {
	count++;
	PORTC = ~(LOOKUPTB[count]);
}