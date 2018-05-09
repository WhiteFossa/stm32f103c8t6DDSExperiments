/*
 * clock.c
 *
 *  Created on: 20 янв. 2018 г.
 *      Author: fossa
 */

#include "clock.h"

void HalClockSwitchToHSE(void)
{
	// Switching HSE on
	RCC->CR |= RCC_CR_HSEON;
	while (0x00 == (RCC->CR & RCC_CR_HSERDY)); // Waiting for HSE start

	// Switching to it
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSE;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE) {}; // Waiting for switching to HSE

	// Disabling HSI
	RCC->CR &= ~RCC_CR_HSION;
}

void HalClockSwitchToPLL(void)
{
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; // PLL source is HSE
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE; // PLL source is not divided
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_PLLMULL) | RCC_CFGR_PLLMULL9; // 8 * 9 = 72 MHz
	RCC->CFGR &= ~RCC_CFGR_USBPRE; // 72 / 1.5 = 48 MHz for USB

	// AHB divider 1 = 72 MHz, 72 MHz max
	RCC->CFGR &= ~RCC_CFGR_HPRE;

	// APB2 divider 1 = 72 MHz, 72 MHz max
	RCC->CFGR &= ~RCC_CFGR_PPRE2;

	// APB1 divider 2 = 36 MHz, 36 MHz max
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_PPRE1) | RCC_CFGR_PPRE1_DIV2;

	// ADC divider 4 = 9 MHz, 14 MHz max
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_ADCPRE) | RCC_CFGR_ADCPRE_DIV4;

	// Switching PLL on
	RCC->CR |= RCC_CR_PLLON;
	while (0x00 == (RCC->CR & ~RCC_CR_PLLRDY)) {}; // Waiting for PLL lock

	// Switching to PLL
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}; // Waiting for switching to PLL
}

void HalClockActivateLSE(void)
{
	// Enabling power and backup domain interfaces clock
	RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;

	// Allowing write to backup domain
	PWR->CR |= PWR_CR_DBP;

	// Switching LSE on
	RCC->BDCR |= RCC_BDCR_LSEON;
	while (0x00 == (RCC->BDCR & RCC_BDCR_LSERDY)) {}; // Waiting for LSE startup

	// Selecting LSE as RTC clock
	RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_RTCSEL) | RCC_BDCR_RTCSEL_LSE;

	// Enabling clock
	RCC->BDCR |= RCC_BDCR_RTCEN;
}
