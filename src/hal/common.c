/*
 * common.c
 *
 *  Created on: 9 мая 2018 г.
 *      Author: fossa
 */

#include "common.h"

void HalFatalError(void)
{
	// Clocking up port C
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	// Lighthing led at PC13
	GPIOC->CRH &= ~(GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0 | GPIO_CRH_CNF13_1 | GPIO_CRH_CNF13_0);
	GPIOC->CRH |= (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0);
	GPIOC->ODR &= ~BV(13);

	// Halt
	while(1)
	{

	}

}

