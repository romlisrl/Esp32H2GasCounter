[![Buy Me a Coffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://buymeacoffee.com/romlis)
![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.x-blue)
![Zigbee](https://img.shields.io/badge/Zigbee-IEEE802.15.4-green)
# External Converter for Zigbee2MQTT  

## 📄 Description  

This custom converter enables full support for the Esp32GasMeter (based on ESP32-H2) in Zigbee2MQTT. It ensures that the device's specific clusters — such as gas consumption, battery voltage, and pulse counting — are correctly mapped to Home Assistant entities.  

## 🛠 Installation

### Method 1: Using the GUI (Recommended)
* Open your Zigbee2MQTT Web Interface.  
* Navigate to Settings -> Dev Console -> External Converters.  
* In the section "Select converter to edit", leave it as N/A - Create new converter.  
  Name : gas_meter.js  
  Code : Paste the entire content of the micasa.js file from this repository.  
* Click Save and then Restart Zigbee2MQTT.  


### Method 2: Manual Installation  
Copy the converter file (e.g., micasa.js) to your Zigbee2MQTT data directory (usually zigbee2mqtt/data/external_converters).  
Open your configuration.yaml file and add the following:  
```bash
YAML
external_converters:
  - micasa.js
Restart Zigbee2MQTT.
```