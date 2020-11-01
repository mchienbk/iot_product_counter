#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Set these to run example.

#define FIREBASE_HOST   "wash-station.firebaseio.com"
#define FIREBASE_AUTH   "HtkscMdQrWHWlNLQJb7EjKJuYjp0DW4sL1oieVME"
#define WIFI_SSID       "Wireless-HN"
#define WIFI_PASSWORD   "vohongnhi"

FirebaseData firebaseData;
FirebaseJson jsonStr;

String fireStatus = ""; // Led status received

int i = 0;
// #define LED 2

void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }


  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");

  // Print local IP address
  Serial.println(WiFi.localIP());

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Test set string value
  // Test set string value
  if (Firebase.setString(firebaseData, "message", "hello world") != 1){
    Serial.print("setting /message failed:");
    Serial.println(firebaseData.errorReason());
    return;
  }
  delay(1000);
  // Firebase Set Led status
  Firebase.setString(firebaseData, "LED_STATUS", "OFF");
}

void loop()
{

  // Get data from firebase
  fireStatus = Firebase.getString(firebaseData, "LED_STATUS");
  if (fireStatus == "ON"){
    Serial.println("Led Turned ON");
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (fireStatus == "OFF"){
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    Serial.println("Wrong Credential! Please send ON/OFF");
  }

  i += 1;
  Firebase.setInt(firebaseData, "COUNT", i);

  delay(1000);

}