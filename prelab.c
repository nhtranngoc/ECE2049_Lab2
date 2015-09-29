/*
 * prelab.c
 *
 *  Created on: Sep 15, 2015
 *      Author: nhtranngoc
 */
#include "prelab.h"

void configButtons(){
	P1SEL &= ~BIT7; //Switch 1 selected as IO
	P2SEL &= ~BIT2; //Switch 2 selected as IO

	P1DIR &= ~BIT7;
	P2DIR &= ~BIT2;

	P1REN |= BIT7;
	P2REN |= BIT2;

	P1OUT |= BIT7;
	P2OUT |= BIT2;
}

void configLED(){
	P1SEL &= ~BIT0;
	P8SEL &= ~(BIT2 | BIT1);

	P1DIR |= BIT0;
	P8DIR |= (BIT2 | BIT1);
}

int buttonRead(){
	if (!(P1IN & 0x80)) return 1;
	else if (!(P2IN & 0x04)) return 2;
	else if ((!(P1IN & 0x80)) && (!(P2IN & 0x04))) return 3;
	return 0;
}

void LEDWrite(char state){
	switch (state){
	case 0x00:
		P1OUT |= BIT0;
		break;
	case 0x01:
		P8OUT |= BIT1;
		break;
	case 0x02:
		P8OUT |= BIT2;
		break;
	default:
		P1OUT= 0x00;
		P8OUT= 0x00;
	}
}
