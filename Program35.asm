/*
 *  Write program set to value in register R10 (and output port PB by PB per 8 LEDs). 
 *  Number of logic is higher than the value of the number read from 3 switches. 
 *  Connected to PC6-PC4 port.
 */ 

.include "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	TEMP = R17

.CSEG
.ORG	0x00
	ldi	VAR_A, 0xFF
	out	DDRB, VAR_A
	ldi	VAR_A, 0x00
	out	DDRC, VAR_A
	ldi	TEMP, 0x00
	
MAIN:	in	VAR_A, PINC
	andi	VAR_A, 0x70	; 0111 0000
	swap	VAR_A		; 0000 0111
	ldi	ZL, low(TB_LOGIC*2)
	ldi	ZH, high(TB_LOGIC*2)
	add	ZL, VAR_A
	adc	ZH, TEMP
	lpm	R10, Z
	
	out	PORTB, R10
	rjmp	MAIN
	
TB_LOGIC:	.DB 0b00000000, .DB 0b00000001,
		.DB 0b00000011,	.DB 0b00000111,
		.DB 0b00001111,	.DB 0b00011111,
		.DB 0b00111111,	.DB 0b01111111

.DSEG
.ESEG
