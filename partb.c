/*
 * ESE350 Lab 2.c
 *
 * Created: 1/27/2023 11:15:43 AM
 * Author : katie
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile int edge = 0;
volatile int period = 0;

void Initialize()
{
	cli();
	DDRB &= ~(1<<DDB0);
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB0);


	
	//timer setup
	TCCR1B &= ~(1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	//set timer 1 to normal
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//ringing edge
	TCCR1B |= (1<<ICES1);
	
	//clear input capture 
	TIFR1 |= (1<<ICF1);
	
	//enable input capture interrupt 
	TIMSK1 |= (1<<ICIE1);	
	
	sei();
}

//interrupt for detecting rising or falling edge 
ISR(TIMER1_CAPT_vect) 
{
	if (TCCR1B & (1<<ICES1)) {
		PORTB |= (1<<PORTB5);
		TCCR1B ^= (1<<ICES1);
	} else {
		PORTB &= ~(1<<PORTB5);
		TCCR1B ^= (1<<ICES1);
	}
}

int main(void)
{
	Initialize();
    while (1);
    }
  



