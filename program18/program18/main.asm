;
; program18.asm
;
; Created: 2/22/2018 11:33:40 AM
; Author : 5735512083
;


.INCLUDE "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_CL = R18
.DEF	VAR_CH = R19
.DEF	VAR_D = R20
.DEF	VAR_E = R21

.CSEG
.ORG	0x00
		ldi	VAR_CL,1
		ldi	VAR_CH,0
		ldi	VAR_A,1
		ldi	VAR_B,2
		ldi	VAR_D,10
		ldi	VAR_E,5

LOOP:	mul		VAR_A,VAR_E
		movw	VAR_CL,R0
		sub		VAR_D,VAR_B
		cp		VAR_A,VAR_B
		brsh	LOOP

END:	rjmp	END

.DSEG

.ESEG
