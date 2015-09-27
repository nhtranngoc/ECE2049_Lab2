/*
 * prelab.h
 *
 *  Created on: Sep 15, 2015
 *      Author: nhtranngoc
 */

#ifndef PRELAB_H_
#define PRELAB_H_

#include <stdio.h>
#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>

void configButtons();
void configLED();
int buttonRead();
char buttonRead_char();
void LEDWrite(char state);

#endif /* PRELAB_H_ */
