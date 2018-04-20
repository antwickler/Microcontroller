;
; program13.asm
;
; Created: 2/22/2018 11:48:33 AM
; Author : 5735512083
;


.INCLUDE "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_CL = R18
.DEF	VAR_CH = R19
.DEF	TEMP = R20

.CSEG
.ORG	0x00
		ldi	XL,low(pointerA)
		ldi	XH,high(pointerA)
		ld	VAR_A,X+
		ld	VAR_B,X+
		ld	VAR_CL,X+
		ld	VAR_CH,X+

		ldi	TEMP,0
		cp	VAR_B,VAR_A
		brsh	TRUE	; b>=a
		rjmp	FALSE

TRUE:	add		VAR_CL,VAR_A
		adc		VAR_CH,TEMP
		rjmp	ENDIF

FALSE:	add		VAR_CL,VAR_B
		adc		VAR_CH,TEMP

ENDIF:	ldi	XL,low(pointerC)
		ldi	XH,high(pointerC)
		st	X+,VAR_CL
		st	X+,VAR_CH

END:	rjmp	END

.DSEG
.ORG	0x10A
pointerA:	.byte 1
pointerB:	.byte 1
pointerC:	.byte 2

.ESEG