#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST "wash-station.firebaseio.com"
#define FIREBASE_AUTH "HtkscMdQrWHWlNLQJb7EjKJuYjp0DW4sL1oieVME"
#define WIFI_SSID "ONOWASH_2.4G"
#define WIFI_PASSWORD "023456789"

#define BTN_01 5 // pin D1
#define BTN_02 4 // pin D2
#define BTN_03 0 // pin D3

// Firebase database
FirebaseData firebaseData;
FirebaseJson jsonStr;

// Define NTP Client to get time
const long utcOffsetInSeconds = 7 * 3600;
char daysOfTheWeek[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void Send_to_uno(char data);
void Update_datetime(void);

int ledStatus = 0; // Led status received

int data1, data2, data3;
int toDay, thisDay;
// Variables to save date and time
String formattedDate;
String sServerDate;
String sClientDate;

int i = 0;
char incomingByte;
String fireToday_dir = "/userdata/today";
String fireData_port1_dir;
String fireData_port2_dir;
String fireData_port3_dir;

void setup()
{
  pinMode(BTN_01, INPUT); // Button 01 input
  pinMode(BTN_02, INPUT); // Button 02 input
  pinMode(BTN_03, INPUT); // Button 03 input
  pinMode(LED_BUILTIN, OUTPUT);

  for (i = 0; i < 50; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    // Serial.print(".");
    delay(500);
  }

  // // Print local IP address
  // Serial.println();
  // Serial.print("Connected to ");
  // Serial.println(WIFI_SSID);
  // Serial.print("IP Address is : ");
  // Serial.println(WiFi.localIP());

  // Start timeClient
  timeClient.begin();

  // Start server
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);

  // Get current date of data from sever
  if (Firebase.getString(firebaseData, fireToday_dir))
    sServerDate = firebaseData.stringData();

  // Test server
  // if (Firebase.setString(firebaseData, "message", "hello world") != 1){
  //   Serial.print("setting /message failed:");
  //   Serial.println(firebaseData.errorReason());
  //   return;
  // }

  // Update firebase folder
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Get moment date at client
  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  sClientDate = formattedDate.substring(0, splitT);

  if(sClientDate != sServerDate){
    // Make new data of today
    fireData_port1_dir = "/userdata/" + sClientDate + "/port1";
    fireData_port2_dir = "/userdata/" + sClientDate + "/port2";
    fireData_port3_dir = "/userdata/" + sClientDate + "/port3";
    Firebase.setInt(firebaseData, fireData_port1_dir, 0);
    Firebase.setInt(firebaseData, fireData_port2_dir, 0);
    Firebase.setInt(firebaseData, fireData_port3_dir, 0);
  } 
  else{
    // Up date continously
    ; 
  }

  // toDay = timeClient.getDay();
  // fireData_port1_dir = "/userdata/" + (String)(daysOfTheWeek[toDay]) + "/port1";
  // fireData_port2_dir = "/userdata/" + (String)(daysOfTheWeek[toDay]) + "/port2";
  // fireData_port3_dir = "/userdata/" + (String)(daysOfTheWeek[toDay]) + "/port3";
  // thisDay = toDay;

  // Firebase.setInt(firebaseData, fireData_port1_dir, 0);
  // Firebase.setInt(firebaseData, fireData_port2_dir, 0);
  // Firebase.setInt(firebaseData, fireData_port3_dir, 0);
}

void loop()
{

  // Check button 01 was pressed
  if (digitalRead(BTN_01) == LOW)
  {
    for(i = 0; i < 20; i++){
      if(digitalRead(BTN_01) != LOW){
        return;
      }
      delay(10);
    }
    while (digitalRead(BTN_01) == LOW)
    { // Wait for unpressed
      delay(10);
    }

    digitalWrite(LED_BUILTIN, LOW); // Working-LED ON

    Send_to_uno(BTN_01); // Send start signal 01
    while (true)
    {
      if (Serial.available() > 0)
      { // Check finish signal 01
        incomingByte = Serial.read();
        // Serial.print("Received: ");
        // Serial.println(incomingByte);
        if (incomingByte == BTN_01)
        {
          // Serial.println("Done");
          Update_datetime();
          digitalWrite(LED_BUILTIN, HIGH); // Working-LED OFF
          break;
        }
      }
      delay(10);
    }
    // Update data 01
    if (Firebase.getInt(firebaseData, fireData_port1_dir))
      data1 = firebaseData.intData() + 1;
    Firebase.setInt(firebaseData, fireData_port1_dir, data1);
  }

  // Check button 02 was pressed
  if (digitalRead(BTN_02) == LOW)
  {
    for(i = 0; i < 20; i++){
      if(digitalRead(BTN_02) != LOW){
        return;
      }
      delay(10);
    }
    while (digitalRead(BTN_02) == LOW)
    { // Wait for unpressed
      delay(10);
    }

    digitalWrite(LED_BUILTIN, LOW); // Working-LED ON

    Send_to_uno(BTN_02); // Send start signal 02
    while (true)
    {
      if (Serial.available() > 0)
      { // Check finish signal 02
        incomingByte = Serial.read();
        // Serial.print("Received: ");
        // Serial.println(incomingByte);
        if (incomingByte == BTN_02)
        {
          // Serial.println("Done");
          Update_datetime();
          digitalWrite(LED_BUILTIN, HIGH); // Working-LED OFF
          break;
        }
      }
      delay(10);
    }
    // Update data 02
    if (Firebase.getInt(firebaseData, fireData_port2_dir))
      data2 = firebaseData.intData() + 1;
    Firebase.setInt(firebaseData, fireData_port2_dir, data2);
  }

  // Check button 03 was pressed
  if (digitalRead(BTN_03) == LOW)
  {
    for(i = 0; i < 20; i++){
      if(digitalRead(BTN_03) != LOW){
        return;
      }
      delay(10);
    }
    while (digitalRead(BTN_03) == LOW)
    { // Wait for unpressed
      delay(10);
    }

    digitalWrite(LED_BUILTIN, LOW); // Working-LED ON

    Send_to_uno(BTN_03); // Send start signal 01
    while (true)
    {
      if (Serial.available() > 0)
      { // Check finish signal 01
        incomingByte = Serial.read();
        // Serial.print("Received: ");
        // Serial.println(incomingByte);
        if (incomingByte == BTN_03)
        {
          // Serial.println("Done");
          Update_datetime();
          digitalWrite(LED_BUILTIN, HIGH); // Working-LED OFF
          break;
        }
      }
      delay(10);
    }
    // Update data 03
    if (Firebase.getInt(firebaseData, fireData_port3_dir))
      data3 = firebaseData.intData() + 1;
    Firebase.setInt(firebaseData, fireData_port3_dir, data3);
  }
}

void Send_to_uno(char data)
{
  Serial.print(data);
}


void Update_datetime(void){
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
    // Get moment date at client
  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  sClientDate = formattedDate.substring(0, splitT);

  if(sClientDate != sServerDate){
    // Make new data of today
    fireData_port1_dir = "/userdata/" + sClientDate + "/port1";
    fireData_port2_dir = "/userdata/" + sClientDate + "/port2";
    fireData_port3_dir = "/userdata/" + sClientDate + "/port3";
    Firebase.setInt(firebaseData, fireData_port1_dir, 0);
    Firebase.setInt(firebaseData, fireData_port2_dir, 0);
    Firebase.setInt(firebaseData, fireData_port3_dir, 0);
  }
}


#if 0
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
  
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("Received: ");
    Serial.println(incomingByte);

    if(Firebase.getInt(firebaseData, "/userdata/port1"))
      data1 = firebaseData.intData();    
    if(Firebase.getInt(firebaseData, "/userdata/port2"))
      data2 = firebaseData.intData();
    if(Firebase.getInt(firebaseData, "/userdata/port3"))
      data3 = firebaseData.intData();

    switch (incomingByte)
    {
    case 49:
      data1++;
      Firebase.setInt(firebaseData, "/userdata/port1", data1);
      break;
    case 50:
      data2++;
      Firebase.setInt(firebaseData, "/userdata/port2", data2);
      break;
    case 51:
      data3++;
      Firebase.setInt(firebaseData, "/userdata/port3", data3);
      break;    
    default:
      break;
    }   
    Serial.println(data1);
    Serial.println(data2);
    Serial.println(data3);
  }
}

// Update data 01
// if (Firebase.getInt(firebaseData, "/userdata/port1"))
//     data1 = firebaseData.intData() + 1;
// Firebase.setInt(firebaseData, "/userdata/port1", data1);
#endif
