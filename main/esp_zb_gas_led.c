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

// Turn led on with specified color
void led_on(led_color_t color)
{
    led_state = ON;
    if (led_strip) {
        uint8_t r = 0, g = 0, b = 0;
        switch (color) {
            case LED_COLOR_RED:
				r = 20;
				break;
            case LED_COLOR_GREEN:
				g = 20;
				break;
            case LED_COLOR_BLUE:
				b = 20;
				break;
            case LED_COLOR_WHITE:
				r = 20; g = 20; b = 20;
				break;
            case LED_COLOR_YELLOW:
				r = 20;
				g = 20;
				b = 20;
				break;
            default:
				g = 20;
				break;
        }
        led_strip_set_pixel(led_strip, 0, r, g, b);
        led_strip_refresh(led_strip);
    }
}

// Turn led off
void led_off()
{
	led_state = OFF;
	if (led_strip) {
		led_strip_clear(led_strip);
	}
}

// Check if led is on
bool led_is_on() {
	return led_state == ON;
}

// Configure led strip
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

	// Create device and save it in led_strip
    esp_err_t ret = led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);
    
    if (ret == ESP_OK) {
        led_strip_clear(led_strip);
        led_state = OFF;
    }

	return ret;
}
