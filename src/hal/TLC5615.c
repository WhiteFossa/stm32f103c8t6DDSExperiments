/*
 * dac.c
 *
 *  Created on: 9 мая 2018 г.
 *      Author: fossa
 */

#include "dac.h"

void HalDAC1Init(void)
{
	HalSPI1Init();

	HalDAC1Set(0x0000);
}

void HalDAC1Set(uint16_t value)
{
	uint16_t dataToSend = (value & 0b1111111111000000); // 10 upper bits
	dataToSend = dataToSend >> 4; // 4 upper dummy bits

	HalSPI1SendData(dataToSend);
}


