/*
 * underwater.c
 *
 *  Created on: Sep 27, 2015
 *      Author: nhtranngoc
 *      		jjszemiot
 */
#include "songs.h"

void playSongUnderwater(){
	setTickDur(72*6);

	play(NOTE_D4, 4);
	play(NOTE_E4, 4);
	play(NOTE_FS4, 4);

	play(NOTE_G4, 4);
	play(NOTE_A4, 4);
	play(NOTE_AS4, 4);

	play(NOTE_B4, 2);
	play(NOTE_B4, 2);
	play(NOTE_B4, 4);

	play(NOTE_B4, 4);
	play(NOTE_B4, 8);
	play(NOTE_G4, 4);

	play(NOTE_E5, 12);

	play(NOTE_DS5, 12);

	play(NOTE_E5, 12);

	rest(2);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_B4, 2);
	play(NOTE_C5, 2);
	play(NOTE_D5, 2);

	play(NOTE_E5, 12);

	play(NOTE_DS5, 8);
	play(NOTE_F5, 4);

	play(NOTE_E5, 12);

	rest(10);
	play(NOTE_G4, 2);

	play(NOTE_D4, 12);

	play(NOTE_CS5, 12);

	play(NOTE_D5, 12);

	rest(2);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_B4, 2);
	play(NOTE_C5, 2);
	play(NOTE_CS5, 2);

	play(NOTE_D5, 12);

	play(NOTE_G4, 8);
	play(NOTE_E5, 4);

	play(NOTE_E5, 12);

	rest(10);
	play(NOTE_G4, 2);

	play(NOTE_G5, 12);

	play(NOTE_G5, 12);

	play(NOTE_G5, 12);

	play(NOTE_G5, 4);
	play(NOTE_A5, 4);
	rest(2);
	play(NOTE_G5, 2);

	play(NOTE_F5, 12);

	play(NOTE_F5, 12);

	play(NOTE_F5, 12);

	play(NOTE_F5, 4);
	play(NOTE_G5, 4);
	rest(2);
	play(NOTE_F4, 2);

	play(NOTE_C4, 1);
	play(NOTE_C5, 11);

	play(NOTE_A4, 4);
	play(NOTE_B4, 4);
	play(NOTE_F5, 4);

	play(NOTE_E5, 2);
	play(NOTE_E5, 2);
	play(NOTE_E5, 6);
	play(NOTE_B4, 2);

	play(NOTE_C5, 12);
}
