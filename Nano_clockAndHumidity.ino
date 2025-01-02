#include <Wire.h>             // Handles communication with I2C devices like AM2320
#include <Adafruit_AM2320.h>  // Library to work with AM2320 temperature and humidity sensor
#include <Ds1302.h>           // Library to manage Ds1302 Real Time Clock (RTC)
#include <MD_MAX72xx.h>       // Library to control the MAX7219 matrix
#include <SPI.h>              // Serial Peripheral Interface library

#define MAX_DEVICES 4  // Number of 8x8 matrices connected
#define CLK_PIN 13     // Pin for CLK
#define DATA_PIN 11    // Pin for DIN
#define CS_PIN 10      // Pin for CS (LOAD)


// Initialize the LED matrix
MD_MAX72XX matrix = MD_MAX72XX(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Initialize AM2320 sensor
Adafruit_AM2320 am2320 = Adafruit_AM2320();

// Initialize Ds1302 RTC (RST = pin 8, DAT = pin 7, CLK = pin 6)
// Ds1302 rtc(8, 7, 6);

void resetMatrix(void) {
  matrix.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  matrix.clear();
}

void displayText(const char* text) {
  matrix.clear();                 
  int textLength = strlen(text); 

  // Reversed loop to have Matrix Diplay right to left
  for (int i = -MAX_DEVICES * 8; i < textLength * 8; i++) {  // Scroll through text
    matrix.clear();
    for (int j = 0; j < textLength; j++) {
      matrix.setChar(i + (j * 8), text[j]);
    }
    matrix.update();
    delay(75);  // Adjust scrolling speed
  }
}

// So that Temp and Humidity can be read left to right 
void reverseString(char* str) {
  int len = strlen(str);  
  for (int i = 0; i < len / 2; i++) {
    char temp = str[i];  // Swap characters from start and end
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
}

void setup() {
  Serial.begin(9600);

  // Initialize AM2320 sensor
  if (!am2320.begin()) {
    Serial.println("AM2320 sensor not found!");
  }

  // Initialize Ds1302 RTC
  // rtc.start();
  // Serial.println("RTC and sensors initialized!");

  // Initialize LED Matrix
  matrix.begin();
  resetMatrix();
}

void loop() {
  // Get the current time from the RTC
  // Ds1302::DateTime now;
  // rtc.getDateTime(&now);  // Retrieve time as object

  // // Print the time to the Serial Monitor
  // Serial.print(now.hour);
  // Serial.print(":");
  // Serial.print(now.minute);
  // Serial.print(":");
  // Serial.println(now.second);

  // Get temperature and humidity from AM2320 sensor
  float temp = am2320.readTemperature();  // Read temperature in Celsius
  float hum = am2320.readHumidity();      // Read humidity as a percentage

  // Format temperature and humidity as Temp:XX.XC Hum:XX.X%
  char tBuffer[8];
  char hBuffer[4];
  dtostrf(temp, 4, 2, tBuffer);
  dtostrf(hum, 4, 0, hBuffer);
  reverseString(tBuffer);
  reverseString(hBuffer);

  char tempBuffer[16];
  char humBuffer[16];
  snprintf(tempBuffer, 16, "C%s:pmeT", tBuffer);
  snprintf(humBuffer, 16, "%s:muH", hBuffer);

  // Display temperature and humidity on the matrix
  displayText(tempBuffer);  
  displayText(humBuffer);
  delay(1000);
}
