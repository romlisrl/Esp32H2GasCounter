[![Buy Me a Coffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://buymeacoffee.com/romlis)
![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)
![Zigbee](https://img.shields.io/badge/Zigbee-IEEE802.15.4-green)

# ⚡ Installation firmware  

## ⚠️ Don't forget to create an [external converter](./zigbee2mqtt/) in Zigbee2MQTT first!  

### 1️⃣ Using [esptool.py](https://docs.espressif.com/projects/esptool/en/latest/esp32/installation.html) (firmware.bin)  
Connect the board to the UART port (example: COM10 on Windows)  
```bash
esptool.py --chip esp32h2 --port COM10 write_flash 0x0 firmware.bin  
```

### 2️⃣ Using [ESPHome Web](https://web.esphome.io/) (firmware.bin)  

- Connect the board via USB/UART  
- Select firmware.bin file  
- Flash it directly from the browser  

---