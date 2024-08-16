# sistem-monitoring-intensitas-cahaya-dan-suhu-air-aquascape-iot
IoT-based aquascape light intensity and water temperature monitoring system connected to Blynk. The following is a picture of the equipment circuit
![1](https://github.com/user-attachments/assets/f921e214-e7e9-4e70-b165-49ca467bd10e)

with the pin configuration as follows
| **Component** | **GND** | **VCC** | **SCL** | **SDA** | **DATA** | **IN 1** | **IN 2** | **IN 3** |
|---------------|---------|---------|---------|---------|----------|----------|----------|----------|
| **ESP32**     | GND     | VCC     | GPIO 23 | GPIO 21 | GPIO 22  | GPIO 4   | GPIO 17  | GPIO 25  |
| **DS18B20**   | GND     | VCC     |         |         |          |          |          |          |
| **GY-302 BH1750** | GND | VCC | SCL | SDA |          |          |          |          |
| **Relay**     | GND     | VCC     |         |         |          | IN 1     | IN 2     | IN 3     |
| **LCD I2C**   | GND     | VCC     | SCL     | SDA     |          |          |          |          |

