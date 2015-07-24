/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * [File Name]     main.c
 * [Platform]      FRDM-KL25Z
 * [Project]       myProject
 * [Version]       1.00
 * [Author]        milton
 * [Date]          06/30/2015
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 */

//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------

#include <stdio.h>
//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------
#include "main.h"
#include "tsi_kl25z.h"
//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

int main(void)
{
	//uint16_t measureResult[BOARD_TSI_ELECTRODE_CNT];
	//uint8_t tsiChn[BOARD_TSI_ELECTRODE_CNT];
	uint32_t avgUntouch = 0; /*! Average TSI value of untouched state */
	uint32_t avgMeasure;
	//tsi_status_t result;



	// Configure board specific pin muxing
	hardware_init();

	// Initialize the OS abstraction layer
	OSA_Init();

	// Init LED1 & turn off it.
	LED1_EN;
	LED1_OFF;

	// Initialize UART terminal
	dbg_uart_init();

	// Initialize TSI
	initHwConfigTSI();

	// Calculates average value afer 100 times measurement.
	avgUntouch = averageMeasurement(TSI_THRESHOLD_SAMPLING);

	// Print a note
	PRINTF("\r\nTouching for turning led on \r\n");
    for (;;)                                         // Forever loop
    {

		// Calculates average measurement.
		avgMeasure = averageMeasurement(1);

		// Check if it's the touched state.
		// Add 10 to remove noise
		if (avgMeasure > avgUntouch + 10) {
			LED1_ON;
		} else {
			LED1_OFF;
		}
		// Measures each 100ms.
		OSA_TimeDelay(100u);

    }
    return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
