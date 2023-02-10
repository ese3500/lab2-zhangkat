/*
 * partc 2.0.c
 *
 * Created: 2/4/2023 4:28:48 PM
 * Author : katie
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

#include "inc/uart.h"

volatile int overflow = 0;
volatile unsigned int edge2 = 0;
volatile unsigned int milisec = 0;
volatile int print = 0;
volatile int i = 0;
char toPrint[5];
volatile int canSpace = 0;

void Initialize()
{
	cli();
	
	//setting inputs and outputs 
	DDRB &= ~(1<<DDB0);
	DDRB |= (1<<DDB5);
	
	//LEDS
	DDRB |= (1<<DDB2); //PB1 set to output pin
	PORTB &= ~(1<<PORTB2); //Drive output high to turn on LED
	
	DDRB |= (1<<DDB3); //PB2 set to output pin
	PORTB &= ~(1<<PORTB3); //Drive output high to turn on LED

	//timer setup pre-scale by 1024
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	// set timer 1 to normal
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	//rising edge
	TCCR1B |= (1<<ICES1);
	
	//clear output capture
	TIFR1 |= (1<<ICF1);
	
	//enable input capture interrupt 
	TIMSK1 |= (1<<ICIE1);	
	
	// enables interrupt and captures overflow
	TIFR1 |= (1<< TOV1);
	TIMSK1 |= (1<< TOIE1);
	
	sei();
}

//overflow interrupt 
ISR(TIMER1_OVF_vect) 
{
	overflow += 1;

}

// interrupt for rising and falling edge of button press
ISR(TIMER1_CAPT_vect) 
{
	if (PINB & (1 << PINB0)) {
		TCNT1 = 0;
		PORTB |= (1<<PORTB5);
		PORTB &= ~(1<<PORTB2);
		PORTB &= ~(1<<PORTB3);
		TCCR1B &= ~(1<<ICES1);
	} else {
		edge2 = TCNT1;
		print = 1;
		PORTB &= ~(1<<PORTB5);
		TCCR1B |= (1<<ICES1);
	}
}

int main(void)
{
    Initialize();
	UART_init(BAUD_PRESCALER); 
	
    while (1) 
    {
		//determines how long the button was left unpressed 
		volatile int unpressed = TCNT1 - edge2;
		//conversion from pulse to milliseconds (1024000/16000000) = 0.064
		milisec = (edge2 * 0.064);
		
		//check for spaces 
		if (unpressed > 0 && unpressed > 15625 && canSpace == 0) 
		{
			//stored string of dots and dashes gets printed out as the corresponding letter/num
			if (strcmp(toPrint, "01") == 0)
			{
				UART_putstring("A ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1000") == 0)
			{
				UART_putstring("B ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1010") == 0)
			{
				UART_putstring("C ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0") == 0)
			{
				UART_putstring("E ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0010") == 0)
			{
				UART_putstring("F ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0110") == 0)
			{
				UART_putstring("G ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0000") == 0)
			{
				UART_putstring("H ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "00") == 0)
			{
				UART_putstring("I ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0111") == 0)
			{
				UART_putstring("J ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "101") == 0)
			{
				UART_putstring("K ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0100") == 0)
			{
				UART_putstring("L ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "11") == 0)
			{
				UART_putstring("M ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "10") == 0)
			{
				UART_putstring("N ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "111") == 0)
			{
				UART_putstring("O ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0110") == 0)
			{
				UART_putstring("P ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1101") == 0)
			{
				UART_putstring("Q ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "010") == 0)
			{
				UART_putstring("R ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "000") == 0)
			{
				UART_putstring("S ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1") == 0)
			{
				UART_putstring("T ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "001") == 0)
			{
				UART_putstring("U ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "0001") == 0)
			{
				UART_putstring("V ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "011") == 0)
			{
				UART_putstring("W ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1001") == 0)
			{
				UART_putstring("X ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1011") == 0)
			{
				UART_putstring("Y ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "1100") == 0)
			{
				UART_putstring("Z ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "01111") == 0)
			{
				UART_putstring("1 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "00111") == 0)
			{
				UART_putstring("2 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "00011") == 0)
			{
				UART_putstring("3 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "00001") == 0)
			{
				UART_putstring("4 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "00000") == 0)
			{
				UART_putstring("5 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "10000") == 0)
			{
				UART_putstring("6 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "11000") == 0)
			{
				UART_putstring("7 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "11100") == 0)
			{
				UART_putstring("8 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "11110") == 0)
			{
				UART_putstring("9 ");
				sprintf(toPrint,"");
			} else if(strcmp(toPrint, "11111") == 0)
			{
				UART_putstring("0 ");
				sprintf(toPrint,"");
			}
			
			//reset space and the stored dot/dash string 
			canSpace = 1;
			print = 0;
			sprintf(toPrint,"");
		}
		
		//determine if the button press is a dot or dash
		if (print == 1) 
		{
			//if dot, a zero gets stored in the dot/dash string
			if (milisec > 30 && milisec < 200)
			{
				char dot[] = "0";
				strcat(toPrint, dot);
				//lights LED
				PORTB |= (1<<PORTB2);
				_delay_ms(50);
				PORTB &= ~(1<<PORTB2);
				//resets to exit if statement and enables space 
				print = 0;
				canSpace = 0;
			} else if (milisec > 200 && milisec < 400)
			{
				//if dash, a one gets stored in the dot/dash string
				char dash[] = "1";
				strcat(toPrint, dash);
				//lights LED
				PORTB |= (1<<PORTB3);
				_delay_ms(50);
				PORTB &= ~(1<<PORTB3);
				//resets to exit if statement and enables space 
				print = 0;
				canSpace = 0;
			} 
		} 
					 
		_delay_ms(100);  
		
		}		
}
