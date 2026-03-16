#include "esp_zb_gas_meter.h"
#ifdef FEATURE_MEASURE_BATTERY_LEVEL

#include "sys/time.h"
#include "freertos/task.h"
#include "esp_sleep.h"

/* ADC Battery measurement */
#define BAT_BUFFER_READ_LEN             256

// adc task handle so the conversion ISR can tell
// to the adc task about process done
extern TaskHandle_t adc_task_handle;

// last time battery voltage was adquired 
extern RTC_DATA_ATTR struct timeval last_battery_measurement_time;

void adc_task(void *arg);
#endif