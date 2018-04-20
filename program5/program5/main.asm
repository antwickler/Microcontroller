;
; program5.asm
;
; Created: 2/22/2018 10:30:01 AM
; Author : 5735512083
;


.INCLUDE "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_C = R18

.CSEG
.ORG	0x0000
	ldi	VAR_B,2
	ldi	VAR_C,4
	ldi	ZL,low(TempA)
	ldi	ZH,high(TempA)

	mul	VAR_B,VAR_C	; a*b
	mov 	VAR_A,R0
	st	Z+,VAR_A
	st	Z+,VAR_B
	st	Z+,VAR_C

END:	rjmp	END

.DSEG
.ORG	0x0100
TempA: .byte 1
TempB: .byte 1
TempC: .byte 1

.ESEG
