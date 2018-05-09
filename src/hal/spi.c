/*
 * spi.c
 *
 *  Created on: 2 мая 2018 г.
 *      Author: fossa
 */

#include "spi.h"

void SPI1_IRQHandler(void)
{
	// What happened?
	if ((SPI1->SR & SPI_SR_RXNE) != 0x00)
	{
		// Transfer completed
		volatile uint32_t dummy = SPI1->DR; // Dummy read to clear RXNE flag

		HalSPI1ChangeCSState(0xFF); // Deactivating CS
	}
}

void HalSPI1Init(void)
{
	// Clocking up port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// PA4 (software control, use as CS)
	GPIOA->CRL &= ~(GPIO_CRL_MODE4_1 | GPIO_CRL_MODE4_0 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF4_0);
	GPIOA->CRL |= (GPIO_CRL_MODE4_1 | GPIO_CRL_MODE4_0);

	// PA5 as SCLK
	GPIOA->CRL &= ~(GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_CNF5_1 | GPIO_CRL_CNF5_0);
	GPIOA->CRL |= (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_CNF5_1);

	// PA7 as MOSI
	GPIOA->CRL &= ~(GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0);
	GPIOA->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1);

	// Clocking SPI unit
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Clearing CRs
	SPI1->CR1 = 0;
	SPI1->CR2 = 0;

	// APC2 Clock is 72MHz
	// SCLK Max for TL5615 is 20MHz
	// Prescaler 4, SCLK = 18MHz
	SPI1->CR1 |= (SPI_CR1_BR_0);

	// 16 bit transfer
	SPI1->CR1 |= SPI_CR1_DFF;

	// Master mode
	SPI1->CR1 |= SPI_CR1_MSTR;

	// Imitaing high CS
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR1 |= SPI_CR1_SSI;

	// No transfer now
	HalSPI1ChangeCSState(0xFF);

	// Interrupt on transfer completed will be generated
	SPI1->CR2 |= SPI_CR2_RXNEIE;

	// Enabling SPI interrupt
	uint32_t prioritygroup = NVIC_GetPriorityGrouping();

	// Highest user IRQ priority (0), 1 sub-pri
	uint32_t priority = NVIC_EncodePriority(prioritygroup, 0, 1 );
	NVIC_SetPriority(SPI1_IRQn, priority);
	NVIC_EnableIRQ(SPI1_IRQn);

	// Turning SPI on
	SPI1->CR1 |= SPI_CR1_SPE;
}

void HalSPI1ChangeCSState(uint8_t state)
{
	if (state != 0x00)
	{
		GPIOA->ODR |= CS_PIN;
	}
	else
	{
		GPIOA->ODR &= ~CS_PIN;
	}
}

void HalSPI1SendData(uint16_t data)
{
	// Are we ready?
	if (0 == (SPI1->SR & SPI_SR_TXE))
	{
		// No, fatal error
		HalFatalError();
	}

	HalSPI1ChangeCSState(0x00);
	SPI1->DR = data;
}


