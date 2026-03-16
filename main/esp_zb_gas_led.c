#include "esp_check.h"
#include "driver/gpio.h"
#include "led_strip.h"

#include "esp_zb_gas_meter.h"
#include "esp_zb_gas_led.h"

static led_strip_handle_t led_strip;
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
	if (led_strip) {
		led_strip_set_pixel(led_strip, 0, 0, 20, 0);  // white (led_strip, 0, 50, 50, 50)
		led_strip_refresh(led_strip);
	}
}

/**
 * @brief Turn led off
 *
 */
void led_off()
{
	led_state = OFF;
	if (led_strip) {
		led_strip_clear(led_strip);
	}
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
	led_strip_config_t strip_config = {
		.strip_gpio_num = LED_PIN,
		.max_leds = 1,
	};

	led_strip_rmt_config_t rmt_config = {
		.clk_src = RMT_CLK_SRC_DEFAULT,
		.resolution_hz = 10 * 1000 * 1000, // 10MHz
		.flags = {
			.with_dma = false,
		}
	};

	// Создаем устройство и сохраняем его в led_strip
    esp_err_t ret = led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);
    
    if (ret == ESP_OK) {
        led_strip_clear(led_strip);
        led_state = OFF;
    }

	return ret;
}
