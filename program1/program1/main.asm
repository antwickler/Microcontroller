;
; program1.asm
;
; Created: 2/22/2018 9:25:52 AM
; Author : 5735512083
;


.include "m328Pdef.inc"
.def	VAR_I = R16
.def	VAR_J = R17
.def	VAR_K = R18

.cseg
.org	0x00
	ldi VAR_I,3
	ldi VAR_J,12
	ldi VAR_K,20
	mov VAR_I,VAR_J
	add VAR_I,VAR_K
	inc VAR_K
	mov VAR_J,VAR_K
	subi VAR_J,5

	ldi	XL,low(pointerI)
	ldi XL,high(pointerI)

	st	X+,VAR_I
	st	X+,VAR_J
	st	X+,VAR_K

END:	rjmp END

.dseg
.org	0x100
pointerI:	.byte 1
pointerJ:	.byte 1
pointerK:	.byte 1

.eseg
