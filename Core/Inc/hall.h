#ifndef __HALL_H__
#define __HALL_H__

#include "stm32f4xx_hal.h"

/**
 * @brief The number of ADC channels.
 */
#define __ADC_CHANNEL_COUNT ((size_t)1)

/**
 * @brief HAL ADC DMA callback function.
 * @param hadc ADC handler.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

/**
 * @brief Read and send sensor's data.
 */
void hall_read_data(ADC_HandleTypeDef *hadc);

/**
 * @brief Check if the ADC coonvertion is finished.
 * @return True if data is ready, false otherwise.
 */
_Bool hall_data_is_ready(void);

/**
 * @brief Get the read value.
 * @return An unsigned integer representing the data read by hall sensor.
 */
uint16_t hall_get_data(void);

#endif // __HALL_H__
