#ifndef ESP_ZB_GAS_METER_H
#define ESP_ZB_GAS_METER_H

#define ESP_MANUFACTURER_NAME           "\x0E""Custom devices"
#define ESP_MODEL_IDENTIFIER            "\x11""ESP32H2GasCounter" /* Customized model identifier */
#define ESP_DATE_CODE                   "\x08""20260301"
#define ESP_PRODUCT_URL                 "\x2C""https://github.com/romlisrl/ZigbeeGasCounter"
#define ESP_PRODUCT_CODE                "\x00"

// ******************************************************************************
// ***                         FEATURES CONFIGURATION                        ****
// ******************************************************************************

// if defined, the device reports power and energy. This requires to compute the
// time elapsed between ticks and might to drain the battery more. Enable if you
// are powering the unit from external power
//#define FEATURE_MEASURE_FLOW_RATE

// define if the device is powered from batteries and you want the device to
// measure the battery voltage. Note battery voltage is not reportable. Use the GUI
// refresh button to obtain the latest measured value from the device.
//#define FEATURE_MEASURE_BATTERY_LEVEL

// Decide if you are going to use DEEP_SLEEP or LIGHT_SLEEP. Only one can be 
// defined. It is possible also to disable both in case the unit is not battery
// powered

// In DEEP_SLEEP mode the device wakes up once every hour, connect to the network
// report the values (the counter) and goes to sleep again. This means it is not
// likely the device will react to commands send from the user interface. But the
// benefit is a extended battery life
#define FEATURE_DEEP_SLEEP

// In LIGHT_SLEEP the ticks are reported more fulently to the coordinator and the
// device can react to the user interface (the sleep window is set in 30 seconds)
//#define FEATURE_LIGHT_SLEEP

// In zigbee2mqtt it is not possible to write the value to the real gas counter.
// The Zigbee Cluster Library Specification in Table 10-57 states that 
// CurrentSummationDelivered is read only. So, the trick is to implement a custom
// cluster so values written to it are transferred to the current counter value.
#define FEATURE_WRITE_COUNTER_VALUE

// ******************************************************************************
// ***                         HARDWARE CONFIGURATION                        ****
// ******************************************************************************

// ESP32H2: External antenna config is board-specific.
// Remove or adapt CONFIG_EXTERNAL_ANTENNA for your H2 board.
//#define CONFIG_EXTERNAL_ANTENNA

// ESP32H2 — GPIO strapping pin warnings:
//   GPIO 8  — strapping (controls LED)  <- was LED_PIN on C6
//   GPIO 9  — strapping (HIGH=normal, LOW=download mode)
// Using strapping pins after boot is possible but may cause issues.
// Remapped to safe pins below.

// input - pin with gas reel sensor (GPIO 10 is safe on H2)
#define PULSE_PIN                                               GPIO_NUM_10

// input - pin for the main button
// (GPIO 9 is BOOT/strapping pin on ESP32H2)
#define MAIN_BTN                                                GPIO_NUM_9

// output - pin to enable battery voltage monitoring
// NOTE: ESP32H2 has NO ADC. FEATURE_MEASURE_BATTERY_LEVEL must stay disabled.
// WARNING: GPIO_NUM_21 is in the SPI flash range (GPIO15-21) on ESP32H2 and
// is NOT recommended for general use. If you ever wire something to BAT_MON_ENABLE,
// change this to a safe pin (e.g. GPIO_NUM_11 or GPIO_NUM_12).
#define BAT_MON_ENABLE                                          GPIO_NUM_11

// ESP32H2 does NOT have an ADC peripheral — emit a hard error if someone
// accidentally enables battery measurement on this target.
#ifdef CONFIG_IDF_TARGET_ESP32H2
  #ifdef FEATURE_MEASURE_BATTERY_LEVEL
    #error "FEATURE_MEASURE_BATTERY_LEVEL is not supported on ESP32H2 (no ADC). Comment out that #define."
  #endif
#endif

#ifdef FEATURE_MEASURE_BATTERY_LEVEL
#define ADC_CHANNEL                                             ADC_CHANNEL_2
#endif

// ******************************************************************************

#include "esp_zigbee_type.h"
#include "freertos/FreeRTOS.h"

extern const char *TAG;

// Report event group events
#define CURRENT_SUMMATION_DELIVERED_REPORT  (EventBits_t)(1U << 0)
#ifdef FEATURE_MEASURE_FLOW_RATE
#define INSTANTANEOUS_DEMAND_REPORT         (EventBits_t)(1U << 1)
#endif
#define STATUS_REPORT                       (EventBits_t)(1U << 2)
#define EXTENDED_STATUS_REPORT              (EventBits_t)(1U << 3)
#ifdef FEATURE_MEASURE_BATTERY_LEVEL
#define BATTERY_REPORT                      (EventBits_t)(1U << 4)
#endif

// Main group events
#ifdef FEATURE_MEASURE_BATTERY_LEVEL
#define SHALL_MEASURE_BATTERY           (1U << 0)
// 1 hour in seconds
#define MEASURE_BATTERY_VOLTAGE_TIME		(60 * 60)
#endif
#define SHALL_ENABLE_ZIGBEE             (1U << 1)
// this is not implemented because of lack of support from esp-zigbee-sdk
// see https://github.com/espressif/esp-zigbee-sdk/issues/561
#define SHALL_DISABLE_ZIGBEE            (1U << 2) 

#ifdef FEATURE_DEEP_SLEEP
// Command to stop the deep sleep functionality at all. This is required
// while OTA is updating the firmware. New events shall no reschedule the
// deep sleep timer
#define SHALL_STOP_DEEP_SLEEP						(1U << 3)

// Command to start the deel sleep functionality. When the main loop starts
// and when the OTA is cancelled
#define SHALL_START_DEEP_SLEEP					(1U << 4)
#endif

extern EventGroupHandle_t report_event_group_handle;
extern EventGroupHandle_t main_event_group_handle;

#ifdef FEATURE_DEEP_SLEEP
extern QueueHandle_t deep_sleep_queue_handle;
extern TaskHandle_t deep_sleep_task_handle;
extern bool allow_report_to_coordinator;

TickType_t dm_deep_sleep_time_ticks();
#endif

esp_err_t gm_counter_set(const esp_zb_uint48_t *new_value);
int32_t time_diff_ms(const struct timeval *other);

#define COUNTER_INCREMENT_DEBOUNCE_TIME	3000 // milliseconds, blocks gas counter to increment the value for this period of time

#endif // ESP_ZB_GAS_METER_H