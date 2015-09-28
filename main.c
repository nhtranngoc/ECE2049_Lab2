#include <msp430.h>
#include <stdint.h>
#include "inc\hw_memmap.h"
#include "driverlibHeaders.h"
#include "CTS_Layer.h"
#include "prelab.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "sound.h"
#include "songs/songs.h"
/* Peripherals.c and .h are where the functions that implement
 * the LEDs and cap touch buttons are implemented. It is useful
 * to organize your code by putting like functions together in
 * files. You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"
//#include "prelab.h"

int msCount=0;
int secLeft=3;
int sec=0;
int leap=0;
int score=0;
char scoreStr[10];

//Enumerate gameState as a type.
enum gameState {
	WELCOME,
	MENU,
	GAME_INIT,
	CHECK_BUTTON,
	GAME_END,
	WIN,
	LOSE
};

// Function prototypes for this file
void swDelay(char numLoops);
void countdown(int sec);
void initInterrupt();
void configLED();
void flashLEDs(int secLeft);
char* itoa(int i, char b[]);

enum gameState state=WELCOME;

//extern volatile unsigned int ms_elapsed = 0;


void main(void){
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    configLED();
    configTouchPadLEDs();
    configDisplay();
    configCapButtons();
    configButtons();
    setTickDur(72);

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
				    while(buttonRead()){
				    if(buttonRead() == 1){ //When button is pressed
				    	int currentSec = sec; //Grab the current snapshot of sec and store it in a variable
				    	int secPassed=0;
				    	while(secPassed <= 3){
				    		secPassed= sec - currentSec;
				    		countdown(3-secPassed);
				    	} //Extremely convoluted way to countdown without slowing down timer interrupt function. There must be a better way!
				    	GrClearDisplay(&g_sContext);
				    	GrFlush(&g_sContext);
			    		state=GAME_INIT;
			    		break;
				    }
				    }
				    break;

				case GAME_INIT:
					//turn off LEDs
					P1OUT &= 0xFE;
					P8OUT &= 0xF9;
					playSongTotoro();
//					playSongUnderwate r();
//				    GrFlush(&g_sContext);
					state=GAME_END;
					break;

				case GAME_END:
					GrStringDrawCentered(&g_sContext, "Your score is: ", AUTO_STRING_LENGTH, 51, 8, TRANSPARENT_TEXT);
				    GrStringDrawCentered(&g_sContext, (itoa(score, scoreStr)), AUTO_STRING_LENGTH, 51, 28, TRANSPARENT_TEXT);
//				    writeHumiliation(int score);
				    GrStringDrawCentered(&g_sContext, "Press S1 to restart", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
				    GrFlush(&g_sContext);
				    while(buttonRead()){
				    	if(buttonRead() == 1){ //When button is pressed
				    		state=WELCOME;
				    		}
				    	break;
				    }
					break;

			}
	 }
}

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

void countdown(int sec){
	//THIS IS NOT THE RIGHT WAY TO DO IT. (Oh well).
	GrClearDisplay(&g_sContext);
	switch(sec){
	case(3):
		GrStringDrawCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
		flashLEDs(3);
		break;
	case(2):
		GrStringDrawCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
		flashLEDs(2);
		break;
	case(1):
		GrStringDrawCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
		flashLEDs(1);
		break;
	case(0):
		GrStringDrawCentered(&g_sContext, "GO!", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
		flashLEDs(0);
		break;
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
		case 1:
			P1OUT |= 0x01;
			break;
		case 2:
			P8OUT |= 0x02;
			break;
		case 3:
			P8OUT |= 0x04;
			break;
		case 0:
			P1OUT |= 0x01;
			P8OUT |= 0x06;
			break;
	}
}

/**
 * @brief Initializing timer interrupt, setting the ticks at 32, which means the timer would
 * be called every 0.001 seconds
 */
void initInterrupt(){
	TA2CTL= TASSEL_1 + ID_1 + MC_1; //General settings: Use ACLK, Divider =1, UP mode
	TA2CCR0=32; //32 ACLK tics = ~.001 sec (one millisecond)
	TA2CCTL0 = CCIE; //TA2CCR0 interrupt enabled

	_BIS_SR(GIE); // Global Interrupt enable
}

/*
 * @brief Timer interrupt function
 * Every 0.001 sec, msCount would would be increased by 1.
 */
#pragma vector= TIMER2_A0_VECTOR //Timer interrupt
__interrupt void Timer_A2_ISR(void){
	if (leap < 141){
		msCount++;
		leap++;
	} else {
		msCount+=2;
		leap=0;
	}

	if(msCount % 500 == 0){ //@TODO: Figure out why 1000 doesn't give exact time.
		sec++;
	}

	ms_elapsed++;

	//if()
}

