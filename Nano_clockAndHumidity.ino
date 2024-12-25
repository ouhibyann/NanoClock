#include <Wire.h>              // Handles communication with I2C devices like AM2320
#include <Adafruit_AM2320.h>   // Library to work with AM2320 temperature and humidity sensor
#include <LedControl.h>        // Library to control MAX7219 LED matrix
#include <Ds1302.h>            // Library to manage Ds1302 Real Time Clock (RTC)

// Initialize MAX7219 LED matrix (DIN = pin 11, CLK = pin 13, CS = pin 10, 1 matrix)
LedControl lc = LedControl(11, 13, 10, 1);

// Initialize AM2320 sensor
Adafruit_AM2320 am2320 = Adafruit_AM2320();

// Initialize Ds1302 RTC (RST = pin 8, DAT = pin 7, CLK = pin 6)
Ds1302 rtc(8, 7, 6);

void setup() {
  Serial.begin(9600);
  
  // Initialize MAX7219 LED matrix
  lc.shutdown(0, false);    // Turn on the LED matrix (0 refers to the first matrix)
  lc.setIntensity(0, 12);    // Set brightness level to medium (0-15 range)
  lc.clearDisplay(0);       // Clear the matrix to ensure it starts blank

  // Initialize AM2320 sensor
  if (!am2320.begin()) {    // Check if AM2320 is connected
    Serial.println("AM2320 sensor not found!"); // Error message if sensor is missing
  }

  // Initialize Ds1302 RTC  
  rtc.start();          // Ensure RTC is running 
  Serial.println("RTC and sensors initialized!"); // Confirmation message
}

void loop() {
  // Get the current time from the RTC
  Ds1302::DateTime now;
  rtc.getDateTime(&now);   // Retrieve time as an object
  
  // Print the time to the Serial Monitor
  Serial.print(now.hour);     // Print hours
  Serial.print(":");
  Serial.print(now.minute);      // Print minutes
  Serial.print(":");
  Serial.println(now.second);    // Print seconds
  
  // Get temperature and humidity from AM2320 sensor
  float temp = am2320.readTemperature(); // Read temperature in Celsius
  float hum = am2320.readHumidity();     // Read humidity as a percentage
  
  // Print temperature to the Serial Monitor
  Serial.print(temp);        // Print temperature value
  Serial.println(" °C");     // Add unit (°C) to the printed value
  
  // Print humidity to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(hum);         // Print humidity value
  Serial.println(" %");      // Add unit (%) to the printed value
  
  delay(1000); // Pause for 1 second before repeating the loop
}
