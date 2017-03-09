/*
 *  AVR Microcontroller ATmega328P
 *  Keypad.asm
 *
 *  Created: 3/2/2017 12:21:02 PM
 *  Author: Antwickler
 */ 

.include "m328Pdef.inc"

.DEF	TMP = R16
.DEF	READ_V = R17
.DEF	VAR_A = R18
.DEF	DISTANCE = R19

.MACRO	COMPARE_AND_BRANCH_IF_KEYPRESSED
		    ldi		TMP, 0xff
		    cp		R0, TMP
		    brne	KEYPRESSED
.ENDMACRO

.CSEG
.ORG	0x00
		  rjmp	RESET

RESET:	ldi		TMP, 0xFF
		    out		DDRB, TMP
		    ldi		TMP, 0xFF
		    out		PORTB, TMP

		    ldi		TMP, 0x78
		    out		DDRC, TMP

READ_KEYPAD:	ldi		TMP, 0b01110111
				      ldi		DISTANCE, 0
				      call	SCAN_KEYPAD
				      COMPARE_AND_BRANCH_IF_KEYPRESSED

				      ldi		TMP, 0b01101111
				      ldi		DISTANCE, 5
				      call	SCAN_KEYPAD
				      COMPARE_AND_BRANCH_IF_KEYPRESSED

				      ldi		TMP, 0b01011111
				      ldi		DISTANCE, 10
				      call	SCAN_KEYPAD
				      COMPARE_AND_BRANCH_IF_KEYPRESSED

				      ldi		TMP, 0b00111111
				      ldi		DISTANCE, 15
				      call	SCAN_KEYPAD
				      COMPARE_AND_BRANCH_IF_KEYPRESSED

				      rjmp	READ_KEYPAD

KEYPRESSED:		call	DISP_7SEG
				      rjmp	READ_KEYPAD

DISP_7SEG:		push	ZL
				      push	ZH
				      push	R0
				      ldi		ZL,low(TB_7SEGMENT*2)
				      ldi		ZH,high(TB_7SEGMENT*2)

				      ldi		TMP, 0x0F
				      and		VAR_A, TMP
				      add		ZL, VAR_A
				      ldi		TMP, 0x00
				      adc		ZH, TMP
				      lpm
				      com		r0
				      ldi		TMP, 0xFF
				      out		DDRB, TMP
				      out		PORTB, r0
				      pop		r0
				      pop		ZH
				      pop		ZL
				      ret

SCAN_KEYPAD:	ldi		ZL, low(KEYPAD_TABLE*2)
				      ldi		ZH, high(KEYPAD_TABLE*2)

				      out		PORTC, TMP
				      in		READ_V, PINC
				      ldi		TMP, 0b00000111
				      and		READ_V, TMP
				      add		READ_V, DISTANCE
				      subi	READ_V, 3
				      ldi		TMP, 0x00
				      add		ZL, READ_V
				      adc		ZH, TMP
				      lpm
				      mov		VAR_A, R0
				      ret
		
KEYPAD_TABLE:	.DB 0x01, 0xFF, 0x02, 0x03, 0xFF, 0x04, 0xFF, 0x05, 0x06, 0xFF
				      .DB 0x07, 0xFF, 0x08, 0x09, 0xFF, 0x0A, 0xFF, 0x00, 0x0B, 0xFF

TB_7SEGMENT:	.db 0b00111111, 0b00000110
				      .db 0b01011011, 0b01001111
				      .db 0b01100110, 0b01101101
				      .db 0b01111101, 0b00000111
				      .db 0b01111111, 0b01101111
				      .db 0b01110111, 0b01111100
				      .db 0b00111001, 0b01011110
				      .db 0b01111001, 0b01110001

