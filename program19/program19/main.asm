;
; program19.asm
;
; Created: 2/22/2018 10:44:46 AM
; Author : 5735512083
;


.INCLUDE "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_I = R18
.DEF	TEMP = R19

.CSEG
.ORG	0x00
		ldi	VAR_A,15
		ldi	VAR_B,1
		ldi	VAR_I,0
		ldi	TEMP,3

WHILE:	cp		VAR_B,VAR_A
		brlt	LOOP
		rjmp	ENDLOOP

LOOP:	muls	VAR_B,TEMP
		mov		VAR_B,R0
		inc		VAR_I
		rjmp	WHILE

ENDLOOP:	

END:	rjmp	END

.DSEG

.ESEG