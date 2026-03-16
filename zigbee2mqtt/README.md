# External Converter for Zigbee2MQTT

## 📄 Description

This custom converter enables full support for the Esp32GasMeter (based on ESP32-H2) in Zigbee2MQTT. It ensures that the device's specific clusters — such as gas consumption, battery voltage, and pulse counting — are correctly mapped to Home Assistant entities.

## 🛠 Installation

### Method 1: Using the GUI (Recommended)
* Open your Zigbee2MQTT Web Interface.

* Navigate to Settings -> Dev Console -> External Converters.

* In the section "Select converter to edit", leave it as N/A - Create new converter.

  Name : gas_meter.js
  
  Code : Paste the entire content of the gas_meter.js file from this repository.

* Click Save and then Restart Zigbee2MQTT.


### Method 2: Manual Installation
Copy the converter file (e.g., gas_meter.js) to your Zigbee2MQTT data directory (usually zigbee2mqtt/data/external_converters).

Open your configuration.yaml file and add the following:

YAML
external_converters:
  - esp32_gas_meter.js
Restart Zigbee2MQTT.
