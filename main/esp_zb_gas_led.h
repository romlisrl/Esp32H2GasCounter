// Seeedstudio yellow pin (ESP32C6)
//#define LED_PIN GPIO_NUM_15

// ESP32H2: GPIO 8 is a strapping pin (controls ROM log output).
// CHANGED: GPIO_NUM_8 -> GPIO_NUM_5  (safe, general-purpose on H2)
// Adjust to match your actual board wiring.
#define LED_PIN GPIO_NUM_5

esp_err_t config_led();

void led_on();

void led_off();

bool led_is_on();