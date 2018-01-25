/*
 *  AVR Microcontroller ATmega328P
 *  Keypad.asm
 *
 *  Created: 3/2/2017 12:21:02 PM
 *  Author: Antwickler
 */ 

.include "m328Pdef.inc"

.DEF  VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_C = R18
.DEF	VAR_D = R19
.DEF	VAR_E = R20
.DEF	VAR_F = R21
.DEF	VAR_G = R22
.DEF	VAR_H = R23

.CSEG
.ORG	0x00
	rjmp	RESET

RESET:	
