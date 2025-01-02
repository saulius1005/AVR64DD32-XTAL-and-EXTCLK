/*
 * CLK.c
 *
 * Created: 2024-12-31 17:45:52
 *  Author: Saulius
 */ 

#include "Settings.h"

void CLOCK_XOSCHF_crystal_init()
{
    /* Enable crystal oscillator with frequency range 16 MHz and 1K cycles start-up time */
    ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_RUNSTDBY_bm
        | CLKCTRL_CSUTHF_1K_gc // 256, 1K, 4K
        | CLKCTRL_FRQRANGE_16M_gc //8, 16, 24, 32Mhz
        | CLKCTRL_SELHF_XTAL_gc //selected as crystal
        | CLKCTRL_ENABLE_bm);

    /* Confirm crystal oscillator start-up */
    while (!(CLKCTRL.MCLKSTATUS & CLKCTRL_EXTS_bm))
    {};

    /* Clear Main Clock Prescaler */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, 0x00);

    /* Set the main clock to use XOSCHF as source */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc | CLKCTRL_CLKOUT_bm); //comment | CLKCTRL_CLKOUT_bm if no need clock output on PA4

    /* Wait for system oscillator change to complete */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {};
    /* Configuration complete; main clock is now running at 16 MHz */
}

void CLOCK_XOSCHF_clock_init()
{
    /* Enable external (32 MHz) clock input */
    ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_SELHF_EXTCLOCK_gc | CLKCTRL_FRQRANGE_32M_gc | CLKCTRL_ENABLE_bm);//selected as clock // 8, 16, 24, 32Mhz

    /* Set Main Clock Prescaler*/
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm);

    /* Set the main clock to use external clock as source */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc | CLKCTRL_CLKOUT_bm);//comment | CLKCTRL_CLKOUT_bm if no need clock output on PA4

    /* Wait for system oscillator change to complete */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
	{};
    /* Configuration complete; main clock is now running at 32 MHz / 2 = 16 MHz */
}

void CLOCK_INHF_clock_init(){
    /* Enable internal (16 MHz) clock input */
	ccp_write_io((uint8_t *) &CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc); //1, 2, 3, 4, 8, 12, 16, 20 or 24Mhz

    /* Set Main Clock Prescaler*/
    //ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm); // uncomment if need clock prescaller

    /* Set the main clock to use internal clock as source */
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSCHF_gc | CLKCTRL_CLKOUT_bm); //comment | CLKCTRL_CLKOUT_bm if no need clock output on PA4

    /* Wait for system oscillator change to complete */
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {};
}