#include "hall.h"
#include "common.h"
#include "fsm.h"
#include "serial.h"

#include <stdint.h>

static uint16_t hall_data = {0};
static _Bool hall_adc_complete = FALSE;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    hall_adc_complete = TRUE;
}

void hall_read_data(ADC_HandleTypeDef *hadc) {
    HAL_StatusTypeDef stat =
        HAL_ADC_Start_DMA(hadc, (uint32_t *)&hall_data, __ADC_CHANNEL_COUNT);
    if (HAL_ERROR == stat) {
        fsm_update(FSM_EVENT_ERROR);
    }
}

_Bool hall_data_is_ready(void) { return hall_adc_complete; }

uint16_t hall_get_data(void) {
    hall_adc_complete = FALSE;
    return hall_data;
}
