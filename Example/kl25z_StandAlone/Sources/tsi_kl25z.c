/*
 * tsi_kl25z.c
 *
 *  Created on: Jul 9, 2015
 *      Author: Milton Sierra Solano
 *
 *      This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 */

//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------

#include "tsi_kl25z.h"
#include "main.h"

static tsi_state_t myTsiState;

// Set up the HW configuration for normal mode of TSI
static const tsi_config_t tsiHwConfig = {
		.ps = kTsiElecOscPrescaler_2div, /*! Prescaler */
		.extchrg = kTsiExtOscChargeCurrent_8uA, /*! Electrode charge current */
		.refchrg = kTsiRefOscChargeCurrent_8uA, /*! Reference charge current */
		.nscn = kTsiConsecutiveScansNumber_8time, /*! Number of scans. */
		.mode = kTsiAnalogModeSel_Capacitive, /*! TSI analog modes in a TSI instance */
		.dvolt = kTsiOscVolRails_Dv_103, .thresh = 100, /*! High byte of threshold. */
		.thresl = 200, /*! Low byte of threshold. */
};

// Set up the configuration of initialization structure
static const tsi_user_config_t tsiConfig = {
		.config = (tsi_config_t*) &tsiHwConfig,
		.pCallBackFunc = NULL,
		.usrData = 0,
};

//create the list of variable electrodes into an array
static uint8_t tsiChn[BOARD_TSI_ELECTRODE_CNT];


/*! External method declaration */
extern void TSI_DRV_IRQHandler(uint32_t instance);



void initHwConfigTSI(void){
	uint32_t i;
	tsi_status_t result; //variable for catch Tsi errors

    // Get TSI channel.
    tsiChn[0] = BOARD_TSI_ELECTRODE_1; //Channel 9 of freedom KL25Z
#if (BOARD_TSI_ELECTRODE_CNT > 1)
    tsiChn[1] = BOARD_TSI_ELECTRODE_2; //Channel 10 of freedom KL25Z
#endif
#if (BOARD_TSI_ELECTRODE_CNT > 2)
    tsiChn[2] = BOARD_TSI_ELECTRODE_3;
#endif
#if (BOARD_TSI_ELECTRODE_CNT > 3)
    tsiChn[3] = BOARD_TSI_ELECTRODE_4;
#endif

	// Driver initialization
	result = TSI_DRV_Init(TSI_INSTANCE, &myTsiState, &tsiConfig);
	if (result != kStatus_TSI_Success) {
		PRINTF("\r\nThe initialization of TSI driver failed ");
	}

	// Enable electrodes for normal mode
	for (i = 0; i < BOARD_TSI_ELECTRODE_CNT; i++) {
		result = TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiChn[i], true);
		if (result != kStatus_TSI_Success) {
			PRINTF("\r\nThe initialization of TSI channel %d failed \r\n",
					tsiChn[i]);
		}
	}
}


uint32_t averageMeasurement(uint8_t samples){
	uint16_t measureResult[BOARD_TSI_ELECTRODE_CNT];
	tsi_status_t result; //variable for catch Tsi errors
	uint32_t i, j;
	uint32_t avg = 0;
	uint32_t sum = 0;


	// Measures average value of untouched state.
	result = TSI_DRV_MeasureBlocking(TSI_INSTANCE);
	if (result != kStatus_TSI_Success) {
		PRINTF("\r\nThe measure of TSI failed. ");
	}

	// Measures average value in untouched mode.
	for (i = 0; i < samples; i++) {
		for (j = 0; j < BOARD_TSI_ELECTRODE_CNT; j++) {
			result = TSI_DRV_GetCounter(TSI_INSTANCE, tsiChn[j],
					&measureResult[j]);
			if (result != kStatus_TSI_Success) {
				PRINTF("\r\nThe read of TSI channel %d failed.", tsiChn[j]);
			}
			// Calculates sum of average values.
			sum += measureResult[j];
		}
	}

	// Calculates average value afer 100 times measurement.
	avg = sum / (samples * BOARD_TSI_ELECTRODE_CNT);

	return avg;

}


/*! TSI IRQ handler */
void TSI0_IRQHandler(void)
{
  TSI_DRV_IRQHandler(TSI_INSTANCE);
}



