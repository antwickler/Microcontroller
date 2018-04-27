#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char TEXT[20] = {"Hello World"};
unsigned char i;

int main(void)
{
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRROL = 103;

	TEXT[11]= 13;
	TEXT[12]= 10;

	for(i=0;i<13;i++){
		USART_Transmit(TEXT[i]);}
	while(1){
	i= USART_Receive();
	i+= 2;
	USART_Transmit(i);
	}
}

#include<avr/.io.h>
#include<avr/interrupt.h>

void USART_Transmit( unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)))
	;
	UDR0 = data;
}

unsigned char USART_Receive(void){
while(!(UCSR0A & (1<<RXC0)))
;
return UDR0;
}