#include "esp_err.h"
#include "esp_zigbee_core.h"
#include "esp_zb_gas_version.h"

#define OTA_UPGRADE_MAX_DATA_SIZE       223
#define OTA_ELEMENT_HEADER_LEN          6

extern uint16_t zigbee_zcl_version;
extern uint8_t  hw_version;
extern uint8_t  app_version;
extern uint8_t  stack_version;
extern uint16_t zigbee_stack_version;

esp_err_t check_boot_partition_change();
esp_err_t zb_ota_upgrade_status_handler(esp_zb_zcl_ota_upgrade_value_message_t message);
esp_err_t zb_ota_upgrade_query_image_resp_handler(esp_zb_zcl_ota_upgrade_query_image_resp_message_t message);