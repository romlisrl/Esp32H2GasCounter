#include "esp_check.h"
#include "driver/gpio.h"

#include "esp_zb_gas_meter.h"
#include "esp_zb_gas_led.h"

typedef enum LedState_e {
	ON,
	OFF
} led_state_t;

led_state_t led_state;

/**
 * @brief Turn led on
 *
 */
void led_on()
{
	led_state = ON;
	gpio_set_level(LED_PIN, 0);
}

/**
 * @brief Turn led off
 *
 */
void led_off()
{
	led_state = OFF;
	gpio_set_level(LED_PIN, 1);
}

/**
 * @brief true if the led is on
 *
 * @return true
 * @return false
 */
bool led_is_on() {
	return led_state == ON;
}

/**
 * @brief Configure the led pin
 *
 */
esp_err_t config_led()
{
	uint64_t led_switch_pin = 1ULL << LED_PIN;
	gpio_config_t led_conf = {
			.intr_type = GPIO_INTR_DISABLE,
			.mode = GPIO_MODE_OUTPUT,
			.pin_bit_mask = led_switch_pin,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.pull_up_en = GPIO_PULLUP_ENABLE
	};
	ESP_RETURN_ON_ERROR(gpio_config(&led_conf), TAG, "Failed to configure LED pin");
	ESP_RETURN_ON_ERROR(gpio_set_level(LED_PIN, 1), TAG, "Failed to turn off led");

	return ESP_OK;
}
