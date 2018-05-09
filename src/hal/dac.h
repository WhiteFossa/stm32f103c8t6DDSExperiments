/*
 * dac.h
 *
 *  Created on: 9 мая 2018 г.
 *      Author: fossa
 */

#ifndef HAL_DAC_H_
#define HAL_DAC_H_

// Our TLC5615 work over SPI, so..
#include "spi.h"

/**
 * Call it to initialize DAC1 and set it to lowest possible output value.
 */
void HalDAC1Init(void);

/**
 * Call it to set DAC value. If actual DAC have less than 16 bit precision, then most significant bytes will be used.
 */
void HalDAC1Set(uint16_t value);

#endif /* HAL_DAC_H_ */
