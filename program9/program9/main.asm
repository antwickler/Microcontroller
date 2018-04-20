;
; program9.asm
;
; Created: 2/22/2018 9:48:39 AM
; Author : 5735512083
;


.include "m328Pdef.inc"

.def VAR_AL = R16
.def VAR_AH = R17
.def VAR_B = R18
.def TEMP = R19

.cseg
.org	0x00
	ldi	VAR_B,220
	ldi TEMP,15
	ldi VAR_AL,low(500)
	ldi VAR_AH,high(500)

	mul	VAR_B,TEMP
	add	VAR_AL,R0
	adc	VAR_AH,R1

	ldi	XL,low(pointerA)
	ldi	XL,high(pointerA)

	st	X+,VAR_AL
	st	X+,VAR_AH
	st	X+,VAR_B

END:	rjmp	END

.dseg
.org	0x100
pointerA:	.byte 2
pointerB:	.byte 1

.eseg