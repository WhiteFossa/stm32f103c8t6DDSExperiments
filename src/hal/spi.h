/*
 * spi.h
 *
 *  Created on: 2 мая 2018 г.
 *      Author: fossa
 */

#ifndef HAL_SPI_H_
#define HAL_SPI_H_

// Hardware SPI

#include "common.h"

// Pins defines
// CS - PA4
#define CS_PIN		GPIO_ODR_ODR4

// Initialize SPI1
void HalSPI1Init(void);

// On or off pin. 0x00 - off, any other = on
void HalSPI1ChangeCSState(uint8_t state);

// Sends 16 bit of data, MSB first
void HalSPI1SendData(uint16_t data);


#endif /* HAL_SPI_H_ */
