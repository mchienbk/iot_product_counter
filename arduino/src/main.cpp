#include <Arduino.h>


#define P_OUT_01  2
#define P_OUT_02  3
#define P_OUT_03  4
#define P_OUT_04  5
#define P_OUT_05  6
#define P_OUT_06  7
#define P_OUT_07  8
#define P_OUT_08  9
#define P_OUT_09  12
#define P_OUT_10  13      // Led built-in

#define P_PWM_01  10
#define P_PWM_02  11

#define INT_CN0 0

#define PRO_ID_01 5
#define PRO_ID_02 4
#define PRO_ID_03 0

volatile int btn_id = 0;

char incomingByte;
// char process_sst = false;
// int check_rcv = 0;
int i;
// void get_btn_id(void);
void process_1(void);
void process_2(void);
void process_3(void);
void senddata(char data);

void setup()
{
  pinMode(P_OUT_01, OUTPUT);
  pinMode(P_OUT_02, OUTPUT);
  pinMode(P_OUT_03, OUTPUT);
  pinMode(P_OUT_04, OUTPUT);
  pinMode(P_OUT_05, OUTPUT);
  pinMode(P_OUT_06, OUTPUT);
  pinMode(P_OUT_07, OUTPUT);
  pinMode(P_OUT_08, OUTPUT);
  pinMode(P_OUT_09, OUTPUT);
  pinMode(P_OUT_10, OUTPUT);
  pinMode(P_PWM_01, OUTPUT);
  pinMode(P_PWM_02, OUTPUT);
  digitalWrite(P_OUT_01, HIGH);     // Output HIGH
  digitalWrite(P_OUT_02, HIGH);     // Output HIGH
  digitalWrite(P_OUT_03, HIGH);     // Output HIGH
  digitalWrite(P_OUT_04, HIGH);     // Output HIGH
  digitalWrite(P_OUT_05, HIGH);     // Output HIGH
  digitalWrite(P_OUT_06, HIGH);     // Output HIGH
  digitalWrite(P_OUT_07, HIGH);     // Output HIGH
  digitalWrite(P_OUT_08, HIGH);     // Output HIGH
  digitalWrite(P_OUT_09, HIGH);     // Output HIGH
  digitalWrite(P_OUT_10, HIGH);     // Output HIGH

  for(i = 0; i < 50; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }
  Serial.begin(9600);
  delay(200);
}
void loop()
{
  if (Serial.available() > 0) {       // Check request signal
    incomingByte = Serial.read();
    // Serial.print("Received: ");
    // Serial.println(incomingByte);

    switch (incomingByte)
    {
    case PRO_ID_01:
      process_1();
      senddata(PRO_ID_01);
      break;

    case PRO_ID_02:
      process_2();
      senddata(PRO_ID_02);
      break;

    case PRO_ID_03:
      process_3();
      senddata(PRO_ID_03);
      break;

    default:
      break;
    }
  }
}




// Code for prosess 01
void process_1(void){
  digitalWrite(P_OUT_01, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_01, HIGH);     // Output HIGH
  digitalWrite(P_OUT_02, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_02, HIGH);     // Output HIGH
  digitalWrite(P_OUT_03, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_03, HIGH);     // Output HIGH
  digitalWrite(P_OUT_04, LOW);      // Output LOW
  delay(5000); 
  digitalWrite(P_OUT_04, HIGH);     // Output HIGH
  delay(5000);
}

// Code for prosess 02
void process_2(void){
  digitalWrite(P_OUT_05, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_05, HIGH);     // Output HIGH
  digitalWrite(P_OUT_06, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_06, HIGH);     // Output HIGH
  digitalWrite(P_OUT_07, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_07, HIGH);     // Output HIGH
  digitalWrite(P_OUT_08, LOW);      // Output LOW
  delay(5000); 
  digitalWrite(P_OUT_08, HIGH);     // Output HIGH
  delay(5000); 
}

// Code for prosess 03
void process_3(void){
  digitalWrite(P_OUT_09, LOW);      // Output LOW
  delay(5000);
  digitalWrite(P_OUT_09, HIGH);     // Output HIGH
  digitalWrite(P_OUT_10, LOW);      // Output LOW
  delay(5000);
}

void senddata(char data){
  Serial.print(data);
}


#if 0

void loop()
{
  // switch(btn_id){
  //   case 1:
  //     process_sst = true;
  //     process_1();
  //     senddata(49);
  //     process_sst = false;
  //     break;
  //   case 2:
  //     process_sst = true;
  //     process_2();
  //     senddata(50);
  //     process_sst = false;
  //     break;
  //   case 3:
  //     process_sst = true;
  //     process_3();
  //     senddata(51);
  //     process_sst = false;
  //     break;

  //   default:
  //     break;
  // }
  // delay(100);

}




// Get button which pressed
void get_btn_id()
{
  if(process_sst == false){
    if(digitalRead(P_IN_01) == 0){
      btn_id = 1;
    } else if(digitalRead(P_IN_02) == 0){
      btn_id = 2;
    } else if(digitalRead(P_IN_03) == 0){
      btn_id = 3; 
    } else{
      btn_id = 0;
    }
  }else{
    btn_id = 0;
  }
}
#endif



