idf_component_register(
        SRCS "esp_zb_gas_meter_zigbee.c" "esp_zb_gas_ota.c" "esp_zb_gas_meter.c" "esp_zb_gas_meter_adc.c" "esp_zb_gas_meter_zigbee.c" "esp_zb_gas_ota.c" "esp_zb_gas_led.c"
        INCLUDE_DIRS "."
        # esp_adc removed: ESP32H2 has no ADC peripheral.
        # If you re-enable FEATURE_MEASURE_BATTERY_LEVEL (unsupported on H2),
        # add esp_adc back here.
        REQUIRES esp-zigbee-lib nvs_flash esp_timer esp_driver_gpio app_update led_strip
)
