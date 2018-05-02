/*
 * spi.c
 *
 *  Created on: 2 мая 2018 г.
 *      Author: fossa
 */

#include "spi.h"

void InitSPI1(void)
{
	// Clocking up port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// CS as fullspeed output
	GPIOA->CRL &= ~(GPIO_CRL_MODE4_1 | GPIO_CRL_MODE4_0 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF4_0);
	GPIOA->CRL |= (GPIO_CRL_MODE4_1 | GPIO_CRL_MODE4_0);

	// SCLK as fullspeed output
	GPIOA->CRL &= ~(GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_CNF5_1 | GPIO_CRL_CNF5_0);
	GPIOA->CRL |= (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0);

	// MOSI as fullspeed output
	GPIOA->CRL &= ~(GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0);
	GPIOA->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0);

	// No clock, device not selected
	ChangeSPIPinState(0x00, SCLK_PIN);
	ChangeSPIPinState(0xFF, CS_PIN);
}

void ChangeSPIPinState(uint8_t state, uint32_t pin)
{
	if (state != 0x00)
	{
		GPIOA->ODR |= pin;
	}
	else
	{
		GPIOA->ODR &= ~pin;
	}
}

void SendSPIData(uint16_t data)
{
	// Selecting chip
	ChangeSPIPinState(0x00, SCLK_PIN);
	delay();
	ChangeSPIPinState(0x00, CS_PIN);
	delay();

	for (volatile int8_t bitNum = 15; bitNum >= 0; bitNum--)
	{
		// Setting bit
		uint16_t mask = 1 << bitNum;

		if ((data & mask) != 0)
		{
			ChangeSPIPinState(0xFF, MOSI_PIN);
		}
		else
		{
			ChangeSPIPinState(0x00, MOSI_PIN);
		}

		// Pulsing SCLK
		ChangeSPIPinState(0xFF, SCLK_PIN);
		delay();
		ChangeSPIPinState(0x00, SCLK_PIN);
		delay();
	}

	// Deselecting chip
	ChangeSPIPinState(0xFF, CS_PIN);
	delay();
}


