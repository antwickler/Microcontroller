;
; program17.asm
;
; Created: 2/22/2018 11:17:27 AM
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
		ldi	VAR_B,0xFF	; 255
		ldi	VAR_A,30

FOR:	cpi	VAR_A,10
		brsh	LOOP
		rjmp	ENDLOOP

LOOP:	lsl		VAR_A	; a = a*2
		add		VAR_B,VAR_A
		brcc	ENDIF	; C = 0
		clr		VAR_A	; C = 1

ENDIF:	dec		VAR_A
		rjmp	FOR

ENDLOOP:	inc		VAR_A

END:	rjmp	END

.DSEG
;.ORG	0x10A
;pointerA:	.byte 1
;pointerB:	.byte 1
;pointerC:	.byte 2

.ESEG