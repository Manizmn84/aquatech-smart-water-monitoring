# AquaTech

Local ESP32 water monitoring firmware for Arduino IDE. Open `firmware/AquaTech/AquaTech.ino`, select ESP32 Dev Module, and install OneWire, DallasTemperature, Adafruit GFX and Adafruit SSD1306 (including dependencies).

Phase 1 includes asynchronous DS18B20 acquisition, CQRobot CQRSENTDS01 TDS, an experimental IR turbidity circuit, CSV Serial output at 115200 baud and an assumed SSD1306 128x64 I2C OLED. No network services are required.

See [hardware and calibration notes](docs/hardware-and-calibration.md) before hardware integration. Implementation and successful compilation do not establish measurement accuracy or hardware operation.
