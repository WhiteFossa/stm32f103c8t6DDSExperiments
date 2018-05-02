/*
 * clock.h
 *
 *  Created on: 20 янв. 2018 г.
 *      Author: fossa
 */

#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

#include "stm32f10x.h"
#include "../helpers/stm32_macroses.h"

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !           ASSUMED 8 MHz HSE quartz and 32.768 KHz LSE quartz.             !
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

/**
 * Switches MCU from HSI to HSE clock and disables HSI after switch.
 */
void SwitchClockToHSE(void);

/**
 * Switches MCU from HSE clock to PLL clock.
 */
void SwitchClockToPLL(void);

/**
 * Clocking RTC from LSE clock.
 */
void ActivateLSEClock(void);

#endif /* HAL_CLOCK_H_ */
