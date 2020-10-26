#include <Arduino.h>
char Rdata;

void setup()
{
  Serial.begin(9600);
  pinMode(14, OUTPUT);
  pinMode(13, INPUT);
  delay(500);
  Serial.println("AT+CIPMUX=1");
  delay(2000);
  Serial.println("AT+CIPSERVER=1,5000");
  delay(2000);
  Serial.println("AT+CIPSTO=3600");
  delay(2000);
}

void loop(){
  while (Serial.available()){

    Rdata = Serial.read();
    
    if (Rdata == 'A' || Rdata == 'a'){
      digitalWrite(14, HIGH);
      delay(50);
    }

    else if (Rdata == 'B' || Rdata == 'b'){
      digitalWrite(14, LOW);
      delay(10);
      digitalWrite(14, HIGH);
      delay(10);
      digitalWrite(14, LOW);
    }
  }
  if(digitalRead(13) == LOW)
    digitalWrite(14, HIGH);
  else
    digitalWrite(14, LOW);       
}