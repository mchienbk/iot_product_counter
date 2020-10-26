#include <Arduino.h>
int val;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(PIN_A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // val = analogRead(A0);   // read the input pin
  // digitalWrite(LED_BUILTIN,LOW);
  // Serial.println(val);
  // delay(200);
  // digitalWrite(LED_BUILTIN,HIGH);
  // delay(1000);

  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("A");
  delay(2000);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("B");
  delay(2000);
}