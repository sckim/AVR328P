;
; asmBlink.asm
;
; Created: 2024-09-25 오전 2:12:45
; Author : Soochan Kim
;


; Replace with your application code
Setup:
		sbi DDRB, PB5 ; pinMode(PB5, HIGH)
    	sbi DDRD, PD7 ; pinMode(PD7, HIGH)
 
Loop:
    	cbi PORTB,PB5 ; digitalWrite(PB5, LOW) 
		cbi PORTD,PD7 ; digitalWrite(PD7, LOW) 
    	
		sbi PORTB,PB5 ; digitalWrite(PB5, HIGH)
		sbi PORTD,PD7 ; digitalWrite(PD7, LOW)  
    	rjmp Loop ; Jump relative back to label Loop, 2 clock cycles
