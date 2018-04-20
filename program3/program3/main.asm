;
; program3.asm
;
; Created: 2/22/2018 10:16:33 AM
; Author : 5735512083
;


.include "m328Pdef.inc"

.DEF	VAR_A = R16
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

RESET:	ldi	VAR_A, 20
	ldi	VAR_B, 32
	ldi	VAR_C, 70
	ldi	VAR_D, 3
	mov	VAR_F, VAR_C
	sub	VAR_F, VAR_D
	mov	VAR_H, VAR_A
	add	VAR_H, VAR_B
	mov	VAR_C, VAR_H
	sub	VAR_C, VAR_F
	mov	VAR_E, VAR_C
	subi	VAR_E, 10
	inc	VAR_B
	mov	VAR_G, VAR_C
	sub	VAR_D, VAR_E
	dec	VAR_A
	
END:	rjmp	END

.DSEG
.ESEG