// Subscribe to MQTT Broker on Public Cloud Host with Authentication


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
int port = 1884;

// User Authentication
String user = "rw";
String password = "readwrite";

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
  
  mqttClient.setUsernamePassword(user,password);
  
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

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);
}

void loop() {
  
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    
    // Print Topic & 
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // Recopile Data of Serial
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    
    Serial.println("\n");
  }

}
