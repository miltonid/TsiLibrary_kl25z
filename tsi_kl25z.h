/*
 * tsi_kl25z.h
 *
 *  Created on: Jul 11, 2015
 *      Author: Milton Sierra Solano
 *
 *      This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 */

#include "fsl_device_registers.h"

#ifndef __TSI_KL25Z_H
#define __TSI_KL25Z_H



#define TSI_THRESHOLD_SAMPLING      (100u)

/*! @brief Device instance number */
#define TSI_INSTANCE                0

void TSI0_IRQHandler(void); //Function for tsi interrupt

/** \fn initHwConfigTSI()
 *  \brief Init the TSI setinghs for FRDM-KL25Z
 *  \param void
 *  \return void
 */ 
void initHwConfigTSI(void);

/** \fn averageMeasurement(samples)
 *  \brief Perform n samples and return the avg of ch9 and ch10
 *  \param uint8_t
 *  \return uint32_t
 */
uint32_t averageMeasurement(uint8_t samples);

#endif /* SOURCES_TSI_KL25Z_H_ */
