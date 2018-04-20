;
; program12.asm
;
; Created: 2/22/2018 10:34:51 AM
; Author : 5735512083
;


.INCLUDE "m328Pdef.inc"

.DEF	VAR_A = R16
.DEF	VAR_B = R17
.DEF	VAR_C = R18
.DEF	TEMP = R19

.CSEG
.ORG	0x00
		ldi	VAR_A,-10
		ldi	VAR_B,100

		cp		VAR_A,VAR_B
		brlt	LESS	; a<b
		breq	EQUAL	; a=b
		rjmp	MORE	; a>b

LESS:	ldi		VAR_C,-1
		rjmp	ENDIF

EQUAL:	ldi		VAR_C,0
		rjmp	ENDIF

MORE:	ldi		VAR_C,1

ENDIF:	muls	VAR_B,VAR_C
		mov		VAR_A,R0

END:	rjmp	END

.DSEG
.ESEG