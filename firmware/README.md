[![Buy Me a Coffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://buymeacoffee.com/romlis)
![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)
![Zigbee](https://img.shields.io/badge/Zigbee-IEEE802.15.4-green)

### ⚠️ Don't forget to create an [external converter](./zigbee2mqtt/) in Zigbee2MQTT first!  

### 1️⃣ Using [esptool.py](https://docs.espressif.com/projects/esptool/en/latest/esp32/installation.html) (firmware_batmon.bin/firmware_wo_batmon.bin)  

- Connect the board to a UART port (e.g., COM10 on Windows)  

**With battery monitor:**  
```bash
esptool.py --chip esp32h2 --port COM10 write_flash 0x0 firmware_batmon.bin  
```
**Without battery monitor:**
```bash
esptool.py --chip esp32h2 --port COM10 write_flash 0x0 firmware_wo_batmon.bin  
```

### 2️⃣ Using [ESPHome Web](https://web.esphome.io/) (firmware_batmon.bin/firmware_wo_batmon.bin)  

- Connect the board via USB/UART  
- Select the firmware file:
  - `firmware_batmon.bin` (with battery monitor)
  - `firmware_wo_batmon.bin` (without battery monitor) 
- Flash it directly from the browser  

---