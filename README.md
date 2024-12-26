# NanoClock&Humidity

Hi there, this little project of mine has been on my todo for quite a time now; I let it under the rug but I happened to have some time at hand lately so.. here I am!

I didn't rebuild the wheel, and all the resources I used can be found on the official [Arduino website](https://www.arduino.cc)


## Components:
- Arduino Nano 
- MAX7219 8x8 LED matrix
- DS1302 Real Time Clock - you'll need a battery for it.
- AM2320 Temperature and humidity sensor
- A breadboard


## Schematic for Connections:

##### MAX7219 LED Matrix
- **VCC** → **5V** on Arduino Nano 
- **GND** → **GND** on Arduino Nano
- **DIN** → **Pin D11** (MOSI)
- **CS** → **Pin D10**
- **CLK** → **Pin D13** (SCK)

##### DS1302 RTC
- **VCC** → **5V** on Arduino Nano
- **GND** → **GND** on Arduino Nano
- **CLK** → **Pin D6**
- **DAT** → **Pin D7**
- **RST** → **Pin D8**

##### AM2320 Sensor
- **VCC** → **5V** on Arduino Nano
- **GND** → **GND** on Arduino Nano
- **SCL** → **A5** (I2C Clock)
- **SDA** → **A4** (I2C Data)