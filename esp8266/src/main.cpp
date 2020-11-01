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

int ledStatus = 0; // Led status received

int data1, data2, data3;
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
  Firebase.setBool(firebaseData, "LED_STATUS", 0);
  delay(1000);

}

void loop()
{

  // Get data from firebase
  if (Firebase.getBool(firebaseData, "LED_STATUS"))
    ledStatus = firebaseData.boolData();
  if (ledStatus == 0){
    Serial.println("Led Turned ON");
    digitalWrite(LED_BUILTIN, LOW);
  }
  else{
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(Firebase.getInt(firebaseData, "/userdata/port1"))
    data1 = firebaseData.intData();
  if(Firebase.getInt(firebaseData, "/userdata/port2"))
    data2 = firebaseData.intData();
  if(Firebase.getInt(firebaseData, "/userdata/port3"))
    data3 = firebaseData.intData();

  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);

  data1+=1;
  data2+=2;
  data3+=3;
  Firebase.setInt(firebaseData, "/userdata/port1", data1);
  Firebase.setInt(firebaseData, "/userdata/port2", data2);
  Firebase.setInt(firebaseData, "/userdata/port3", data3);

  delay(1000);

}