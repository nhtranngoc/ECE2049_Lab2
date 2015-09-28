/*
 * sound.c
 *
 *  Created on: Sep 23, 2015
 *      Author: nhtranngoc
 *      		jjszemiot
 */

#include "sound.h"



/* Some reasonable defaults. */
volatile unsigned int current_note = NOTE_A4;
volatile unsigned int ms_elapsed = 0;

/* The number of milliseconds per "tick" in the music (see TICKS_PER_BEAT). */
static unsigned int ms_per_tick = 0;

void setTickDur(unsigned int bpm) {
    /* Compute the number of ms per tick from the beats per minute. */
    ms_per_tick = 60000 / (TICKS_PER_BEAT * bpm);
}

void play(unsigned int note, unsigned int duration_ticks) {
    unsigned int duration_ms = 0;

    /* Compute the duration (in ms). */
    duration_ms = duration_ticks * ms_per_tick;

    /* Set the current note. */
    current_note = note;

    /* Reset the elapsed counter. */
    ms_elapsed = 0;

    /* Wait for the note duration to expire. */
    while (ms_elapsed < duration_ms - DEAD_TIME_MS){
    	playBuzzer(current_note);
    	//@TODO define capLEDOn, checkKeyPad, score.
    	int enumNote = current_note % 5; //Turns all notes to one of five positions- depending on its frequency.
    	capLEDOn(enumNote); //Turn on LED at that particular position.
//    	score += checkKeyPad(enumNote); //Returns 0 if doesn't hit right key press- Award some points otherwise.
    }
    BuzzerOff();
	capLEDOff();

    /* Wait for the full duration to expire. */
    while (ms_elapsed < duration_ms);
}

static void capLEDOn(int ledNum){
	capLEDOff();
	switch(ledNum){
	case 0:
		P1OUT |= BIT1;
		break;
	case 1:
		P1OUT |= BIT2;
		break;
	case 2:
		P1OUT |= BIT3;
		break;
	case 3:
		P1OUT |= BIT4;
		break;
	case 4:
		P1OUT |= BIT5;
		break;
	}
}

static void capLEDOff(){
	P1OUT &= ~(BIT1|BIT2|BIT3|BIT4|BIT5);
}

void rest(unsigned int duration_ticks) {
    unsigned int duration_ms = 0;

    /* Compute the duration (in ms). */
    duration_ms = duration_ticks * ms_per_tick;

    /* Reset the elapsed counter. */
    ms_elapsed = 0;

    /* Wait for the rest duration to expire. */
    while(ms_elapsed < duration_ms);
}



/**
 * @brief Play the buzzer at a specified frequency
 * @param freq The frequency the buzzer will play at
 */
void playBuzzer(int freq){ //Using code from buzzerOn() in peripherals.c
// Initialize PWM output on P7.5, which corresponds to TB0.3
	P7SEL |= BIT5; // Select peripheral output mode for P7.5
	P7DIR |= BIT5;

	TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
	TB0CTL  &= ~TBIE; 						// Explicitly Disable timer interrupts for safety

	// Now configure the timer period, which controls the PWM period
	// Doing this with a hard coded values is NOT the best method
	// I do it here only as an example. You will fix this in Lab 2.
	TB0CCR0   = 32768/freq; 					// Set the PWM period in ACLK ticks
	TB0CCTL0 &= ~CCIE;					// Disable timer interrupts

	// Configure CC register 3, which is connected to our PWM pin TB0.3
	TB0CCTL3  = OUTMOD_7;					// Set/reset mode for PWM
	TB0CCTL3 &= ~CCIE;						// Disable capture/compare interrupts
	TB0CCR3   = TB0CCR0/2; 					// Configure a 50% duty cycle
}
