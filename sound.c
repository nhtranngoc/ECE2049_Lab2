/*
 * sound.c
 *
 *  Created on: Sep 23, 2015
 *      Author: nhtranngoc
 *      		jjszemiot
 */

#include "sound.h"

// Some reasonable defaults.
volatile unsigned int currentNote = NOTE_A4;
volatile unsigned int msElapsed = 0;

// The number of milliseconds per "tick" in the music (see TICKS_PER_BEAT).
static unsigned int msPerTick = 0;

/**
 * @brief Sets the tempo in BPM (beats per minute) at which the music will play back.
 * @param bpm Beats Per Minute set in sheet music.
 */
void setTickDur(unsigned int bpm) {
	// Compute the number of ms per tick from the beats per minute.
	msPerTick = 60000 / (TICKS_PER_BEAT * bpm);
}

/**
 * @brief Plays a note for a set duration.
 * @param note One of the defined notes (frequency).
 * @param durationTick duration in terms of "tick".
 */
void play(unsigned int note, unsigned int durationTick) {
	unsigned int durationMs = 0;
	/* Compute the duration (in ms). */
	durationMs = durationTick * msPerTick;
	/* Set the current note. */
	currentNote = note;
	/* Reset the elapsed counter. */
	msElapsed = 0;

	/* Wait for the note duration to expire. */
	while (msElapsed < durationMs - DEAD_TIME_MS){
		playBuzzer(currentNote);
		int enumNote = currentNote % 5; //Turns all notes to one of five positions- depending on its frequency.
		capLEDOn(enumNote); //Turn on LED at that particular position.
		checkKeyPad(enumNote); //Award some points if hit the right keypress.
	}
	GrClearDisplay(&g_sContext);
	GrStringDrawCentered(&g_sContext, (itoa(score, scoreStr)), AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	GrFlush(&g_sContext);
	BuzzerOff();
	capLEDOff();
	P1OUT &= 0xFE;
	P8OUT &= 0xF9;

	/* Wait for the full duration to expire. */
	while (msElapsed < durationMs);
}

/**
 * @brief Converts from integer to string.
 * @param i Number to convert.
 * @param b[] String of char .
 * @return Pointer to created string.
 */
char* itoa(int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

/**
 * @brief A function to check the capacitive buttons and return appropriate numbers
 * @return -1 if no buttons are pressed, 0 for X button, 1 for Square button, 2 for Octogon button,
 * 3 for Triangle button, and 4 for Circle button
 *
 */
int checkButton(){
	switch(CapButtonRead()){
	case NONE_BUTTON:
		return -1;
	case X_BUTTON:
		return 0;
	case SQ_BUTTON:
		return 1;
	case OCT_BUTTON:
		return 2;
	case TRI_BUTTON:
		return 3;
	case CIR_BUTTON:
		return 4;
	}
	return -1;
}

/**
 *@brief Check for keypad while a note is playing.
 *@param keyPad Number from 0 to 4 that indicates buttons.
 */
static void checkKeyPad(int keyPad){
	if (keyPad == checkButton()){
		P1OUT |= 0x01;
		P8OUT |= 0x06;
		score += 10;
	}
	total += 10;
}

/**
 * @brief Turns on capacitive LEDs.
 * @param ledNum Number from 0 to 4 to indicate LEDs.
 */
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

/**
 * @brief Turns off cap LEDs.
 */
static void capLEDOff(){
	P1OUT &= ~(BIT1|BIT2|BIT3|BIT4|BIT5);
}

/**
 * @brief Rest for a bit.
 * @param durationTick Duration to rest.
 */
void rest(unsigned int durationTick) {
	unsigned int durationMs = 0;
	/* Compute the duration (in ms). */
	durationMs = durationTick * msPerTick;
	/* Reset the elapsed counter. */
	msElapsed = 0;
	/* Wait for the rest duration to expire. */
	while(msElapsed < durationMs);
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
