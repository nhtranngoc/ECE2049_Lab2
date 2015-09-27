/*
 * sound.c
 *
 *  Created on: Sep 23, 2015
 *      Author: nhtranngoc
 *      		jjszemiot
 */

#include "sound.h"



/* Some resonable defaults. */
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
    }
    BuzzerOff();

    /* Wait for the full duration to expire. */
    while (ms_elapsed < duration_ms);
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

//-------------------------------------------------------------------

///**
// * @brief Plays a sound when the game starts
// */
//void introSound(){
//    playBuzzer(110);
//    swDelay(1);
//    playBuzzer(150);
//    swDelay(1);
//    playBuzzer(100);
//    swDelay(1);
//    playBuzzer(140);
//    swDelay(1);
//    playBuzzer(80);
//    swDelay(1);
//    playBuzzer(50);
//    swDelay(1);
//    BuzzerOff();
//}

///**
// * @brief Plays a short sound when the player pushes a button
// */
//void clickSound(){
//	playBuzzer(30);
//	volatile unsigned int i=5000;		// volatile to prevent optimization by compiler
//   	while (i > 0) i--;
//	BuzzerOff();
//}

//What do we want this function to do?
//Tempo determined by bpm of quarter note
//Note duration dependent on relative note value and tempo of piece
//int tempoToDurSixteenth(int tempo){
//	int quarter, half, whole, eighth, sixteenth;
//	quarter = tempo;
//	half = 2*tempo;
//	whole = 4*tempo;
//	eighth = tempo/2;
//	sixteenth = tempo/4;
//}

//int keyToFreq(int key){
//	int returnFreq;
//	switch(key){
//	case 39:
//		returnFreq = 247;
//		break;
//	case 40:
//		returnFreq = 262;
//		break;
//	case 41:
//		returnFreq = 277;
//		break;
//	case 42:
//		returnFreq = 294;
//		break;
//	case 43:
//		returnFreq = 311;
//		break;
//	case 44:
//		returnFreq = 330;
//		break;
//	case 45:
//		returnFreq = 349;
//		break;
//	case 46:
//		returnFreq = 370;
//		break;
//	case 47:
//		returnFreq = 392;
//		break;
//	case 48:
//		returnFreq = 415;
//		break;
//	case 49:
//		returnFreq = 440;
//		break;
//	case 50:
//		returnFreq = 466;
//		break;
//	case 51:
//		returnFreq = 494;
//		break;
//	case 52:
//		returnFreq = 523;
//		break;
//	case 53:
//		returnFreq = 554;
//		break;
//	case 54:
//		returnFreq = 587;
//		break;
//	case 55:
//		returnFreq = 622;
//		break;
//	case 56:
//		returnFreq = 659;
//		break;
//	case 57:
//		returnFreq = 698;
//		break;
//	case 58:
//		returnFreq = 740;
//		break;
//	case 59:
//		returnFreq = 784;
//		break;
//	case 60:
//		returnFreq = 831;
//		break;
//	case 61:
//		returnFreq = 880;
//		break;
//	default:
//		returnFreq = -1;
//		break;
//	}
//	return returnFreq;
//}

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
	TB0CCR0   = freq; 					// Set the PWM period in ACLK ticks
	TB0CCTL0 &= ~CCIE;					// Disable timer interrupts

	// Configure CC register 3, which is connected to our PWM pin TB0.3
	TB0CCTL3  = OUTMOD_7;					// Set/reset mode for PWM
	TB0CCTL3 &= ~CCIE;						// Disable capture/compare interrupts
	TB0CCR3   = TB0CCR0/2; 					// Configure a 50% duty cycle
}

void playBuzzer2(){ //Using code from buzzerOn() in peripherals.c
// Initialize PWM output on P7.5, which corresponds to TB0.3
	P7SEL |= BIT5; // Select peripheral output mode for P7.5
	P7DIR |= BIT5;

	TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
	TB0CTL  &= ~TBIE; 						// Explicitly Disable timer interrupts for safety

	// Now configure the timer period, which controls the PWM period
	// Doing this with a hard coded values is NOT the best method
	// I do it here only as an example. You will fix this in Lab 2.
	TB0CCR0   = current_note; 					// Set the PWM period in ACLK ticks
	TB0CCTL0 &= ~CCIE;					// Disable timer interrupts

	// Configure CC register 3, which is connected to our PWM pin TB0.3
	TB0CCTL3  = OUTMOD_7;					// Set/reset mode for PWM
	TB0CCTL3 &= ~CCIE;						// Disable capture/compare interrupts
	TB0CCR3   = TB0CCR0/2; 					// Configure a 50% duty cycle
}

