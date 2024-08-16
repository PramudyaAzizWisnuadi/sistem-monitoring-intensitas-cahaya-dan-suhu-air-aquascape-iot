# sistem-monitoring-intensitas-cahaya-dan-suhu-air-aquascape-iot
IoT-based aquascape light intensity and water temperature monitoring system that connects to Blynk and displays notifications. The following is a picture of the equipment circuit

![1](https://github.com/user-attachments/assets/f921e214-e7e9-4e70-b165-49ca467bd10e)

with the pin configuration as follows
| **ESP32**  | **DS18B20** | **GY-302 BH1750** | **Relay** | **LCD I2C** |
|------------|-------------|-------------------|-----------|-------------|
| GND        | GND         | GND               | GND       | GND         |
| VCC        | VCC         | VCC               | VCC       | VCC         |
| GPIO 23    |             | SCL               |           | SCL         |
| GPIO 21    |             | SDA               |           | SDA         |
| GPIO 22    | DATA        |                   |           |             |
| GPIO 4     |             |                   | IN 1      |             |
| GPIO 17    |             |                   | IN 2      |             |
| GPIO 25    |             |                   | IN 3      |             |

More details can be seen in the following journal article
[Klik di sini untuk membaca artikel terkait](https://ejournal.uniramalang.ac.id/index.php/g-tech/article/view/4645)

**Hope it is useful**
