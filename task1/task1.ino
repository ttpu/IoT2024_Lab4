
#include <WiFi.h>

// Wi-Fi credentials (replace with your own network details)
const char* ssid = "YOUR_SSID"; // Your Wi-Fi SSID
const char* password = "YOUR_PASSWORD"; // Your Wi-Fi Password

// Global variables
const int LM35_PIN = 34; // GPIO pin connected to LM35 sensor

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  
  // TODO: Add a loop to check WiFi.status() until it is connected.
  // When connected, print the IP address.
}

void loop() {
  // Check if Wi-Fi is connected
  if (WiFi.status() == WL_CONNECTED) {
    // Read temperature data from the LM35 sensor
    int analogValue = analogRead(LM35_PIN);
    
    // Convert analog reading to Celsius
    float temperatureC = convertToCelsius(analogValue);
    
    // TODO: Print temperature in Celsius to the Serial Monitor
    
    // Delay to wait 5 seconds before the next reading
    delay(5000);
  } else {
    // TODO: Print a message to the Serial Monitor indicating Wi-Fi connection issues
    // TODO: wait for 2 seconds before checking the wifi state
  }
}

// Function to convert LM35 analog reading to Celsius
float convertToCelsius(int analogValue) {
  // LM35 temperature formula (assuming a 3.3V reference voltage on ESP32):
  // TODO: Voltage (mV) = analogValue * (3300 / 4095.0);
  // TODO: Celsius = Voltage / 10.0;
  // TODO: return celcius value (float)
}
