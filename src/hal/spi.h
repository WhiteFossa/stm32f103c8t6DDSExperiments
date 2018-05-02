/*
 * spi.h
 *
 *  Created on: 2 мая 2018 г.
 *      Author: fossa
 */

#ifndef HAL_SPI_H_
#define HAL_SPI_H_

#include "../main.h" // For delay

// Dumbest delay-based SPI implementation

// Pins defines
// CS - PA4
#define CS_PIN		GPIO_ODR_ODR4

// SCLK - PA5
#define SCLK_PIN	GPIO_ODR_ODR5

// MOSI - PA7
#define MOSI_PIN	GPIO_ODR_ODR7

// Initialize SPI1
void InitSPI1(void);

// On or off pin. 0x00 - off, any other = on
void ChangeSPIPinState(uint8_t state, uint32_t pin);

// Sends 16 bit of data, MSB first
void SendSPIData(uint16_t data);


#endif /* HAL_SPI_H_ */
