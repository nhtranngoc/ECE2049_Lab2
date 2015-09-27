#include <msp430.h>
#include <stdint.h>
#include "inc\hw_memmap.h"
#include "driverlibHeaders.h"
#include "CTS_Layer.h"
#include "prelab.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "sound.h"
/* Peripherals.c and .h are where the functions that implement
 * the LEDs and cap touch buttons are implemented. It is useful
 * to organize your code by putting like functions together in
 * files. You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"
//#include "prelab.h"

int count=0;
int secLeft=3;

//Enumerate gameState as a type.
enum gameState {
	WELCOME,
	MENU,
	GAME_INIT,
	CHECK_BUTTON,
	WIN,
	LOSE
};


// Function prototypes for this file
void swDelay(char numLoops);
void countdown(int sec);
void initInterrupt();
void configLED();
void flashLEDs(secLeft);

enum gameState state=WELCOME;

void main(void){
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    configLED();
    configTouchPadLEDs();
    configDisplay();
    configCapButtons();
    configButtons();

    int out;
    char debugOut ='A';

	 while(1){
		 if(buttonRead()== 2){
			 state=WELCOME;
		 }
			switch(state){
				case WELCOME:
					initInterrupt();
//					clrScr();
					GrFlush(&g_sContext);
				    // Intro Screen -- Write to the display screen
				    GrStringDrawCentered(&g_sContext, "GUITAR HERO", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
				    // Refresh the display now that we have finished writing to it
				    GrFlush(&g_sContext);
//				    introSound();
					state=MENU;
					break;

				case MENU:
				    GrStringDrawCentered(&g_sContext, "Press S1 to Start", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
				    GrFlush(&g_sContext);
				    // Refresh the display now that we have finished writing to it
				    //Check for keypress on s1
//				    while(buttonRead() == 0){} //Do nothing and wait. And wait.
//				    	P1OUT &= ~(buttonRead() << 1);
				    	if(buttonRead() == 1){ //When button is pressed
				    		secLeft = 3;
				    		while(secLeft >=0){
				    			countdown(secLeft);
				    			flashLEDs(secLeft);
				    		}
				    		GrClearDisplay(&g_sContext);
				    		GrFlush(&g_sContext);

//////				    		clickSound();
//				    		GrClearDisplay(&g_sContext);
//						    GrStringDrawCentered(&g_sContext, "A", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
//						    GrFlush(&g_sContext);
//////				    		countdown();
//				    		P1OUT |= (LED4+LED5+LED6+LED7+LED8);   // turn on all 5 LEDs
			    		state=GAME_INIT;
				    		break;
				    	}
//				    }
					break;

				case GAME_INIT:
					playBuzzer(NOTE_A4);
					swDelay(4);
					BuzzerOff();
//				    GrFlush(&g_sContext);
					state=WELCOME;
					break;
			}
	 }
}

void countdown(int sec){
	//THIS IS NOT THE RIGHT WAY TO DO IT.
	GrClearDisplay(&g_sContext);
	if (sec == 3) {
		GrStringDrawCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	}
	if (sec == 2) {
		GrStringDrawCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	}
	if (sec == 1) {
		GrStringDrawCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	}
	if (sec == 0) {
		GrStringDrawCentered(&g_sContext, "GO!", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	}
	GrFlush(&g_sContext);
}


void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent optimization
			                            // by compiler

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void flashLEDs(secLeft){
	//Reset LEDs
	P1OUT &= 0xFE;
	P8OUT &= 0xF9;

	switch(secLeft){
		case 3:
			P1OUT |= 0x01;
			break;
		case 2:
			P8OUT |= 0x02;
			break;
		case 1:
			P8OUT |= 0x04;
			break;
		case 0:
			P1OUT |= 0x01;
			P8OUT |= 0x06;
			break;
	}
}

/**
 * @brief Initializing timer interrupt, setting the ticks at 327, which means the timer would
 * be called every 0.01 seconds
 */
void initInterrupt(){
	TA2CTL= TASSEL_1 + ID_1 + MC_1; //General settings: Use ACLK, Divider =1, UP mode
	TA2CCR0=32; //32 ACLK tics = ~.001 sec (one millisecond)
	TA2CCTL0 = CCIE; //TA2CCR0 interrupt enabled

	_BIS_SR(GIE); // Global Interrupt enable
}

/*
 * @brief Timer interrupt function
 * Every 0.01 second, tenMillisecLeft would be decreased by 10.
 */
#pragma vector= TIMER2_A0_VECTOR //Timer interrupt to get the aliens to go down
__interrupt void Timer_A2_ISR(void){
	int millisec;
	count++;

//	if(count % )

	millisec--;

	if(millisec % 556){

	}

	if(millisec<=0){
		secLeft--;

		//@TODO: Implement leap handler.
		millisec=600;
	}


}

