/*
 * totoro.c
 *
 *  Created on: Sep 27, 2015
 *      Author: nhtranngoc
 *      		jjszemiot
 */


#include "songs.h"

void playSongTotoro(){
	setTickDur(125*2);

	play(NOTE_F4, 4);
	play(NOTE_E4, 4);
	play(NOTE_F4, 2);
	play(NOTE_C4, 8);
	rest(10);

	play(NOTE_F4, 4);
	play(NOTE_E4, 4);
	play(NOTE_F4, 2);
	play(NOTE_A4, 8);
	rest(10);
	play(NOTE_AS4, 4);

	play(NOTE_A4, 4);
	play(NOTE_G4, 4);
	play(NOTE_F4, 2);
	play(NOTE_AS4, 4);
	rest(2);

	play(NOTE_A4, 4);
	play(NOTE_G4, 4);
	play(NOTE_F4, 4);
	play(NOTE_F4, 6);
	play(NOTE_G4, 2);
	play(NOTE_G4, 8);
	rest(4);

	rest(4);
	play(NOTE_F4, 4);
	play(NOTE_E4, 4);
	play(NOTE_F4, 2);
	play(NOTE_C4, 8);
	rest(10);

	play(NOTE_F4, 4);
	play(NOTE_E4, 4);
	play(NOTE_F4, 2);
	play(NOTE_C5, 8);

	rest(10);
	play(NOTE_AS4, 1);
	rest(1);
	play(NOTE_AS4, 2);

	play(NOTE_AS4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 2);
	play(NOTE_G4, 2);
	play(NOTE_AS4, 8);
	rest(4);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 4);

	play(NOTE_A4, 4);
	play(NOTE_A4, 2);
	play(NOTE_G4, 2);
	play(NOTE_F4, 2);
	play(NOTE_A4, 8);
	rest(10);
	play(NOTE_D4, 4);

	play(NOTE_E4, 4);
	play(NOTE_F4, 4);
	play(NOTE_G4, 2);
	play(NOTE_D4, 4);
	play(NOTE_D4, 2);

	play(NOTE_E4, 4);
	play(NOTE_F4, 2);
	play(NOTE_G4, 1);
	rest(1);
	play(NOTE_F4, 1);
	rest(1);

	play(NOTE_C5, 24);
	rest(2);
	play(NOTE_F4, 2);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_C4, 4);

	play(NOTE_A4, 2);
	play(NOTE_F4, 2);
	rest(2);
	play(NOTE_C5, 2);
	rest(2);
	play(NOTE_AS4, 4);
	play(NOTE_G4, 1);
	rest(1);

	rest(8);
	play(NOTE_AS4, 2);
	rest(2);
	play(NOTE_G4, 2);
	play(NOTE_E4, 2);

	rest(2);
	play(NOTE_AS4, 4);
	play(NOTE_A4, 4);
	play(NOTE_F4, 1);
	rest(5);

	rest(4);
	play(NOTE_CS4, 4);
	play(NOTE_F4, 4);
	play(NOTE_AS4, 4);

	play(NOTE_A4, 4);
	play(NOTE_C5, 2);
	play(NOTE_F4, 4);
	rest(4);
	play(NOTE_A4, 2);

	play(NOTE_AS4, 2);
	play(NOTE_A4, 1);
	rest(1);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 1);
	rest(1);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 2);
	play(NOTE_F4, 2);
	play(NOTE_G4, 6);
	rest(4);
	play(NOTE_F4, 2);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_AS4, 2);

	play(NOTE_C5, 6);
	play(NOTE_A4, 2);
	play(NOTE_F4, 4);
	play(NOTE_G4, 4);
	play(NOTE_AS4, 4);
	play(NOTE_G4, 1);
	rest(9);
	play(NOTE_AS4, 4);

	play(NOTE_G4, 2);
	play(NOTE_E4, 2);
	rest(2);
	play(NOTE_AS4, 2);
	rest(2);
	play(NOTE_A4, 4);
	play(NOTE_F4, 1);
	rest(1);

	rest(8);
	play(NOTE_D4, 4);
	play(NOTE_D5, 4);

	play(NOTE_C5, 2);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_C5, 6);
	play(NOTE_F4, 1);
	rest(1);

	play(NOTE_F4, 4);
	rest(2);
	play(NOTE_A4, 2);
	play(NOTE_AS4, 2);
	play(NOTE_A4, 1);
	rest(1);
	play(NOTE_F4, 1);
	rest(1);
	play(NOTE_AS4, 2);

	play(NOTE_A4, 1);
	rest(1);
	play(NOTE_F4, 1);
	rest(1);
	play(NOTE_D5, 2);
	play(NOTE_C5, 16);
	rest(6);
	play(NOTE_C4, 1);
	rest(1);
	play(NOTE_C4, 2);

	play(NOTE_AS4, 1);
	rest(7);
	play(NOTE_A4, 2);
	play(NOTE_G4, 2);
	play(NOTE_A4, 2);
	play(NOTE_F4, 16);
}
