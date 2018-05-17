#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define  TURN_ALL_LED_OFF 0xFF
#define  INTERVAL_time 65528

unsigned char TABLE7SEG[] = {
	0b00111111, 0b00000110, // 0 & 1
	0b01011011, 0b01001111, // 2 & 3
	0b01100110, 0b01101101, // 4 & 5
	0b01111101, 0b00000111, // 6 & 7
	0b01111111, 0b01101111, // 8 & 9
	0b01110111, 0b01111100, // A & b
	0b00111001, 0b01011110, // C & D
	0b01111001, 0b01110001, // E & F 
	0b01110110, 0b01001000, // H & =
	0b00000000, 0b01010000, // off & r 
	0b00111000, 0b01011100, // L & o
	0b01110100				// h
};

unsigned char DIVISOR, QUOTIENT, DECODED, alphabet = 10, state = 0, next = 0, input;
unsigned char digit1, digit2, digit3, digit4, digit5; // Digits 7-segment
unsigned short ACCUMULATED;
unsigned long NUMBERS, TEMP_a, TEMP_b, TEMP_h, TEMP_l; // Input value
unsigned long area = 0, volume = 0; // Output value
unsigned short sw = 0, mode;

ISR(TIMER1_OVF_vect){
	TCNT1 = INTERVAL_time;
}

ISR(PCINT2_vect){
   	sw = PIND;  
   	mode = sw & 0x03;

   	if(mode == 0){ // Choose mode
		state = 0;	
    }
    else if(mode == 1){ // Find trapezoid area mode
		state = 1;
		input = 0;
    }
    else if(mode == 2){ // Find trapezoidal volume mode
		state = 1;
		input = 1;
    }
}

ISR(ADC_vect){
	if(ADCH > 9){
		ACCUMULATED += ADCH;
		DIVISOR++;
	}
	else{
		ACCUMULATED = 0;
		DIVISOR = 0;
	}
	if(DIVISOR == 10){
		QUOTIENT = ACCUMULATED/DIVISOR;
		if((QUOTIENT>9)&&(QUOTIENT<16)) DECODED = 1;
		else if((QUOTIENT>18)&&(QUOTIENT<26)) DECODED = 2;
		else if((QUOTIENT>29)&&(QUOTIENT<37)) DECODED = 3;
		else if((QUOTIENT>46)&&(QUOTIENT<53)) DECODED = 4;
		else if((QUOTIENT>74)&&(QUOTIENT<81)) DECODED = 5;
		else if((QUOTIENT>99)&&(QUOTIENT<107)) DECODED = 6;
		else if((QUOTIENT>133)&&(QUOTIENT<141)) DECODED = 7;
		else if((QUOTIENT>169)&&(QUOTIENT<177)) DECODED = 8;
		else if((QUOTIENT>192)&&(QUOTIENT<199)) DECODED = 9;
		else if((QUOTIENT>212)&&(QUOTIENT<220)) DECODED = 10;
		else if((QUOTIENT>228)&&(QUOTIENT<236)) DECODED = 0;
		else if((QUOTIENT>236)&&(QUOTIENT<244)) DECODED = 11;
		else DECODED = 15;

		if(DECODED != 11 && DECODED != 10){ // Not * & #
			NUMBERS = (NUMBERS*10) + DECODED;
		}
		else if(DECODED == 10 && next==0 && input==0){
			alphabet=11;
			TEMP_a=NUMBERS; 
			NUMBERS=0;
			next++;  
		}
		else if(DECODED == 10 && next==1 && input==0){
			alphabet=22;
			TEMP_b=NUMBERS; 
			NUMBERS=0;
			next++;    
		}
		else if(DECODED == 10 && next==2 && input==0){
			alphabet=17;
			TEMP_h=NUMBERS; 
			NUMBERS=0;
			next++;    
			state++;
		}
		else if(DECODED == 10 && next==0 && input==1){
			alphabet=11;
			TEMP_a=NUMBERS; 
			NUMBERS=0;
			next++;  
		}
		else if(DECODED == 10 && next==1 && input==1){			
			alphabet=22;
			TEMP_b=NUMBERS; 
			NUMBERS=0;
			next++;    
		}
		else if(DECODED == 10 && next==2 && input==1){
			alphabet=20;
			TEMP_h=NUMBERS; 
			NUMBERS=0;
			next++;    
		}
		else if(DECODED == 10 && next==3 && input==1){
			alphabet=17;
			TEMP_l=NUMBERS; 
			NUMBERS=0;
			next++;    
			state++;
		}
		else if(DECODED == 11){ 			
			NUMBERS=0; 
			next=0;
			alphabet=10;
			state=1;
		}
	}	

	// Choose mode
	if(state == 0){	  
		NUMBERS=0;  
	 	next=0;	 
	 	state=0;  

		PORTB = ~TABLE7SEG[12];
		PORTC = 0b00000001; // C
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		   
		PORTB = ~TABLE7SEG[16];
		PORTC = 0b00000010; // H
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
			   
		PORTB = ~TABLE7SEG[0];
		PORTC = 0b00000100; // 0
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
			
		PORTB = ~TABLE7SEG[0];
		PORTC = 0b00001000; // 0
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
			   
		PORTB = ~TABLE7SEG[5];
		PORTC = 0b00010000; // S
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
			   
		PORTB = ~TABLE7SEG[14];
		PORTC = 0b01000000; // E
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
   	}

   	else if(state == 1){
		digit1 = (NUMBERS)%10;
		digit2 = (NUMBERS/10)%10;
		digit3 = ((NUMBERS)/100)%10;
		digit4 = ((NUMBERS)/1000)%10;
		digit5 = ((NUMBERS)/10000)%10;
	   
		if(NUMBERS<10){
		    digit5=digit4=digit3=digit2=18;
		}
		else if(NUMBERS<100){
		     digit5=digit4=digit3=18;
		}
		else if(NUMBERS<1000){
		    digit5=digit4=18;
		}
		else if(NUMBERS<10000){
		    digit5=18;
		}

		PORTB = ~TABLE7SEG[alphabet];
		PORTC = 0b00000001; 
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit5];
		PORTC = 0b00000010;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit4];
		PORTC = 0b00000100;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
	     
		PORTB = ~TABLE7SEG[digit3];
		PORTC = 0b00001000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit2];
		PORTC = 0b0010000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit1];
		PORTC = 0b01000000;
		_delay_ms(5);
		PORTC = 0b00000000;		
    } 
	    
    // Find trapezoid area mode
	else if(next == 3 && state == 2 && input == 0){
		area = (0.5*(TEMP_a + TEMP_b))*TEMP_h; // Formula to find trapezoid area		        
		digit1 = (area)%10;
		digit2 = ((area)/10)%10;
		digit3 = ((area)/100)%10;
		digit4 = ((area)/1000)%10;
		digit5 = ((area)/10000)%10;
		
		if(area > 0 && area < 10){
		    digit5=digit4=digit3=digit2=18;
		}
		else if(area > 10 && area < 100){
		    digit5=digit4=digit3=18;
		}
		else if(area > 100 && area < 1000){
		    digit5=digit4=18;
		}
		else if(area > 1000 && area < 10000){
		    digit5=18;
		}
		else if(area > 99999){
		    alphabet=14; // E
		    digit5=19;   // r
		    digit4=19;   // r
		    digit3=21;   // o
		    digit2=19;   // r
		    digit1=18;   // off
		}

		PORTB = ~TABLE7SEG[alphabet];
		PORTC = 0b00000001; 
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit5];
		PORTC = 0b00000010;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit4];
		PORTC = 0b00000100;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
	     
		PORTB = ~TABLE7SEG[digit3];
		PORTC = 0b00001000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit2];
		PORTC = 0b0010000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit1];
		PORTC = 0b01000000;
		_delay_ms(5);
		PORTC = 0b00000000;
	}

	// Find trapezoidal volume mode
	else if(next == 4 && state == 2 && input == 1){ 		
	    volume = ((0.5*(TEMP_a + TEMP_b))*TEMP_h)*TEMP_l; // Formula to find trapezoidal volume	
		digit1 = (volume)%10;
		digit2 = ((volume)/10)%10;
		digit3 = ((volume)/100)%10;
		digit4 = ((volume)/1000)%10;
		digit5 = ((volume)/10000)%10;
		
		if(volume > 0 && volume < 10){
		    digit5=digit4=digit3=digit2=18;
		}
		else if(volume > 10 && volume < 100){
		    digit5=digit4=digit3=18;
		}
		else if(volume > 100 && volume < 1000){
		    digit5=digit4=18;
		}
		else if(volume > 1000 && volume < 10000){
		    digit5=18;
		}
		else if(volume > 99999){
		    alphabet=14; // E
		    digit5=19;   // r
		    digit4=19;   // r
		    digit3=21;   // o
		    digit2=19;   // r
		    digit1=18;   // off
		}

		PORTB = ~TABLE7SEG[alphabet];
		PORTC = 0b00000001;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit5];
		PORTC = 0b00000010;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit4];
		PORTC = 0b00000100;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
	     
		PORTB = ~TABLE7SEG[digit3];
		PORTC = 0b00001000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit2];
		PORTC = 0b0010000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
		
		PORTB = ~TABLE7SEG[digit1];
		PORTC = 0b01000000;
		_delay_ms(5);
		PORTC = 0b00000000;
		_delay_ms(5);
	}		      	
}

int main(void){
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB = TURN_ALL_LED_OFF;
	DDRC = 0x0F;
	
	ADMUX = 0b00100101;
	ADCSRA = 0b10101101;
	ADCSRB = 0x06;
		
	TCNT1 = INTERVAL_time;
	PCICR = 0x04;
	PCMSK2 = 0x03;
	TCCR1B = 0x05;
	TIMSK1 = 0x01;

	sei();
	
	NUMBERS = 0;
	DIVISOR = 0;

    while(1){
    	;	
    }
}