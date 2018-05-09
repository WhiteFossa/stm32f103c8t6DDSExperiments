/*
 * common.h
 *
 *  Created on: 9 мая 2018 г.
 *      Author: fossa
 */

#ifndef HAL_COMMON_H_
#define HAL_COMMON_H_

#include "stm32f10x.h"
#include "../helpers/stm32_macroses.h"

// HAL common routines

/**
 * Calling this function generating error signal (for example lighting a LED) and halts MCU.
 */
void HalFatalError(void);

#endif /* HAL_COMMON_H_ */
