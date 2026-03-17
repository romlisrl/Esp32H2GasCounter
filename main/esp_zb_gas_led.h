// Seedstudio yellow pin (ESP32C6)
//#define LED_PIN GPIO_NUM_15

// ESP32H2: GPIO 8 
#define LED_PIN GPIO_NUM_8

esp_err_t config_led();

typedef enum {
    LED_COLOR_RED    = 0,
    LED_COLOR_GREEN  = 1,
    LED_COLOR_BLUE   = 2,
    LED_COLOR_WHITE  = 3,
    LED_COLOR_YELLOW = 4,
} led_color_t;

void led_on(led_color_t color);

void led_off();

bool led_is_on();