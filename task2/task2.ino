
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials (replace with your own network details)
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Unique dweet.io identifiers for each team
const char* myDeviceID = "teamA_device";  // Replace with your device ID
const char* otherTeamID = "teamB_device"; // Replace with other team's device ID

// Global variables
const int LM35_PIN = 34; // GPIO pin connected to LM35 sensor

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);

  // TODO: Add a loop to check WiFi.status() until it is connected.
  // TODO: When connected, print the IP address.
}

void loop() {
  // Check if Wi-Fi is connected
  if (WiFi.status() == WL_CONNECTED) {
    // Step 1: Read temperature from LM35 sensor
    int analogValue = analogRead(LM35_PIN);
    float temperatureC = convertToCelsius(analogValue);

    // Step 2: Send temperature data to dweet.io
    sendTemperatureToDweet(temperatureC);

    // Wait 3 seconds before the next operation
    delay(3000);

    // Step 3: Retrieve data from the other team's device
    float otherTeamTemp = getTemperatureFromDweet();

    // TODO: Print the other team's temperature to the Serial Monitor

    // Wait 3 seconds before repeating the cycle
    delay(3000);
  } else {
    // TODO: Print a message to the Serial Monitor indicating Wi-Fi connection issues
  }
}

// Function to convert LM35 analog reading to Celsius
float convertToCelsius(int analogValue) {
  // LM35 temperature formula (assuming a 3.3V reference voltage on ESP32):
  // Voltage (mV) = analogValue * (3300 / 4095.0);
  // Celsius = Voltage / 10.0;
  // TODO: return celcius value (float)
}

// Function to send temperature data to dweet.io
void sendTemperatureToDweet(float temperature) {
  HTTPClient http; // Create HTTPClient object
  
  // Format the URL to send a GET request to dweet.io with temperature data
  // Example URL: https://dweet.io/dweet/for/myDeviceID?temp=<temperature>
  // Construct the URL with device ID and temperature data
  String url = "https://dweet.io/dweet/for/" + String(myDeviceID) + "?temp=" + String(temperature);
  
  // TODO: Open HTTP connection and send the request
  // TODO: Check if the request was successful and print a confirmation to Serial
  
  // TODO: End the HTTP connection
}

// Function to get temperature data from the other team's device on dweet.io
float getTemperatureFromDweet() {
  HTTPClient http; // Create HTTPClient object
  
  // TODO: Format the URL to retrieve data from the other team's dweet.io endpoint
  // Example URL: https://dweet.io/get/latest/dweet/for/<otherTeamID>
  
  // TODO: Open HTTP connection and send GET request
  // TODO: Check if the request was successful
  
  // Parse JSON response
  float otherTeamTemp = 0.0; // Initialize variable to store temperature
  if (http.GET() > 0) { 
    // TODO: Get the response payload to a string variable "payload"
    
    // Use ArduinoJSON to parse JSON response and extract "temp" value
    /* Example JSON structure: 
    {
      "this": "succeeded",
      "by": "getting",
      "the": "dweets",
      "with": [
            {
                "thing": "<otherTeamID>",
                "created": "2024-10-30T06:11:41.710Z",
                "content": {
                    "temp": 35.2
                }
            }
        ]
    } */

    // Allocate memory for the JSON document
    DynamicJsonDocument doc(1024);

    // Deserialize the JSON payload
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      // Navigate through JSON structure to extract the "temp" value
      otherTeamTemp = doc["with"][0]["content"]["temp"].as<float>();
    } else {
      Serial.print("JSON deserialization failed: ");
      Serial.println(error.c_str());
    }
      
    // TODO: Convert parsed value to float and store in otherTeamTemp
  } else {
    // TODO: Print an error message if the request fails
  }

  // TODO: End the HTTP connection
  return otherTeamTemp; // Return the retrieved temperature
}
