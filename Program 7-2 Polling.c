#include<avr/io.h>

int main(void) {
	DDRD = 0x00; //input
	DDRC = 0xFF; //output

	unsigned char LOOKUPTB[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 
								0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
	unsigned char switch, disp;

	while(1) {
		switch = PINB;
		switch &= 0x0F;
		disp = LOOKUPTB[switch];
		PORTC = ~(disp);
	}
}
