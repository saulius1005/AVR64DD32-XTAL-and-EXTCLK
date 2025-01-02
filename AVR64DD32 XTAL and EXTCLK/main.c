/*
 * AVR64DD32 XTAL and EXTCLK.c
 *
 * Created: 2024-12-31 17:44:32
 * Author : Saulius
 */ 

#include "Settings.h"


int main(void)
{
	PORTA.DIRSET = PIN1_bm /*| PIN3_bm*/ | PIN4_bm; // PA1 for toggle output test, PA3 for unused XTALHF output test (toggles as well, only if using an internal or external clock, except for an external crystal source), PA4 - Clock out.
	//CLOCK_XOSCHF_crystal_init();
	CLOCK_XOSCHF_clock_init();
	//CLOCK_INHF_clock_init();
    while (1) 
    {
		PORTA.OUTSET = PIN4_bm;
		PORTA.OUTCLR = PIN4_bm;
		//PORTA.OUTTGL = PIN3_bm;
		PORTA.OUTTGL = PIN1_bm;
    }
}

