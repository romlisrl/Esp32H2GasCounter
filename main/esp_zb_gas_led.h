// Seeedstudio yellow pin (ESP32C6)
//#define LED_PIN GPIO_NUM_15

// ESP32H2: GPIO 8 
#define LED_PIN GPIO_NUM_8

esp_err_t config_led();

void led_on();

void led_off();

bool led_is_on();