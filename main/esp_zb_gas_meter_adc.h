#include "esp_zb_gas_meter.h"
#ifdef FEATURE_MEASURE_BATTERY_LEVEL

#include "sys/time.h"
#include "freertos/task.h"
#include "esp_sleep.h"

// ADC Battery measurement
#define BAT_BUFFER_READ_LEN             256

// The ADC task handle allows the ISR 
// to notify the task when conversion completes.
extern TaskHandle_t adc_task_handle;

// Timestamp of the last battery voltage reading.
extern RTC_DATA_ATTR struct timeval last_battery_measurement_time;

void adc_task(void *arg);
#endif