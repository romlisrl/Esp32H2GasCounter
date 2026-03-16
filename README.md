[![Buy Me a Coffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://buymeacoffee.com/romlis)
# ESP32H2 Gas Counter with Zigbee2MQTT

**ESP32H2-based gas counter** that measures pulses from a meter with an embedded magnet and sends them to **Zigbee2MQTT**.   

*Inspired by [ZigbeeGasCounter](https://github.com/IgnacioHR/ZigbeeGasCounter).*

---

## Features

- Counts pulses from a meter using a reed sensor connected to a GPIO and GND pin. 
- Stores pulse count in **non-volatile memory (NVS)**.  
- Sends data to **Zigbee2MQTT**:  
  - On a configurable timer  
  - When accumulated pulses reach a threshold  
  - Triggers immediate transmission when **Boot button** is pressed  
- Supports **deep sleep** for low power.  
- LED for pulse indication.  

---

## Hardware

- ESP32-H2-DevKitM-1 board (Aliexpress)  
- Gas meter with pulse output (e.g., BK-G4MT, G16-U25 Honeywell or similar)  
- Reed sensor: **Normally Open (NO)** – tested with GPS-01 Reed Switch 4×18 (Aliexpress)
- Optional battery  

---

## Software Requirements

- **ESP-IDF** v5.x  
- **Zigbee2MQTT** external converter  

---

## Wiring Example

| ESP32H2 Pin | Connection                                     |
|------------|------------------------------------------------|
| GPIO10     | Reed sensor signal                              |
| GND        | Reed sensor GND                                 |
| VBat(Vcc)  | +3.3V (check voltage with series resistor TBD)  |
| GND        | -3.3V                                           |
|            |                                                 |

<img src="./images/esp32-h2-devkitm1-pinlayout.png" width="400" alt="ESP32-H2 DevKitM-1 Pinout" />

---

## Configuration

| Parameter                  | Description                                                    |
|----------------------------|----------------------------------------------------------------|
| `MUST_SYNC_MINIMUM_TIME`   | Time between automatic transmissions (timer default 60m)       |
| `COUNTER_REPORT_DIFF`      | Number of pulses to trigger immediate transmission (default 10)|
| `INITIAL_COUNTER_VALUE`    | Initial value for the counter (2134 will be 21.34 m3)          |

---

## How It Works

1. ESP32H2 counts pulses from the meter.  
2. Pulses are stored in **NVS flash** to survive reboots or deep sleep.  
3. When **timer expires** or **pulse threshold** is reached data is sent to **Zigbee2MQTT**.  
4. Device enters **deep sleep** to save power until next event (pulse or timer).  

---

## Example Logs

```text
GAS_COUNTER: Counter loaded value=160
GAS_COUNTER: Setup deep sleep
GAS_COUNTER: Wake up from PULSE.
GAS_COUNTER: Checking if Zigbee radio should be enabled
GAS_COUNTER: Counter stored value=161
GAS_COUNTER: Configuring wake-up methods
GAS_COUNTER: Enabling wake-up timer , 162s
```

---
## Installation  

### 1️⃣ Using ESP-IDF (recommended)  

```bash
# Clone the repository
git clone https://github.com/romlisrl/Esp32H2GasCounter
cd Esp32H2GasCounter
# Erase flash completely before the first upload
idf.py erase-flash
# Configure the project (optional: partitions, Wi-Fi, OTA, etc.)
idf.py menuconfig
# Build and flash the project, and open the serial monitor
idf.py build flash monitor
```

### 2️⃣ Using a pre-built binary (flash_project.bin)

> ⚠️ Don't forget to create external convert in Zigbee2MQTT first!  
```bash
# Connect the board to the UART port (example: COM10 on Windows)
esptool.py --chip esp32h2 --port COM10 write_flash 0x0 flash_project.bin
```

---

## Notes

Make sure the Zigbee coordinator is running and paired.  
Configure Zigbee2MQTT to match firmware endpoint and cluster IDs.  
Optimized for battery-operated, low-power operation. 
