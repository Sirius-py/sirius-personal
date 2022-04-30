// Publish to MQTT Broker on Public Cloud Host

// Libraries 
#include <ArduinoMqttClient.h>  // MQTT Manager
#include "WiFi.h"               // WiFi Manager

// WiFi Variables
////////////////////////////////////////// Put your own WiFi Credentials
char ssid[] = "Galaxy A10";     // WiFi Network SSID (name)
char pass[] = "3014308359";     // WiFi Network password

// MQTT Client Variables
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT Parameters
////////////////////////////////////////// Put your own Parameters
const char broker[]= "test.mosquitto.org";
const char topic[]= "Test/Esp";
int port = 1883;

// Interval for sending messages (milliseconds)
const long interval = 10000;
unsigned long previousMillis = 0;


// Function to Connect with Network via WiFi
void connectWIFI(){
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");
}

// Function to Connect to MQTT Broker
void connectBroker(){

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    return;
  }

  Serial.println("You're connected to the MQTT broker!\n");
}

void setup() {
  // Initialize Serial Monitor 
  Serial.begin(9600);
  
  // Wait until Open Serial Monitor
  while (!Serial) {}

  // Connection to Network via WiFi
  connectWIFI();

  // Connection to MQTT Broker
  connectBroker();
}

// Send Data to broker each 10 Sec with random Data
void loop() {
  // Call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    // Save the last time
    previousMillis = currentMillis;

    // Save Value
    int myvalue = random(0,1000);

    // Display Message to User in Serial Monitor
    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(myvalue);
    Serial.println();
    
    // Send Message to Broker
    mqttClient.beginMessage(topic);
    mqttClient.print(myvalue);
    mqttClient.endMessage();    
  }
}
