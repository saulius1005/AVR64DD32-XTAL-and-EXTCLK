/*
 * Settings.h
 *
 * Created: 2024-12-31 17:46:41
 *  Author: Saulius
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <avr/io.h>
#include <avr/cpufunc.h>

void CLOCK_XOSCHF_crystal_init();
void CLOCK_XOSCHF_clock_init();
void CLOCK_INHF_clock_init();

#endif /* SETTINGS_H_ */