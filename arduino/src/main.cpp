#include "header.h"



void setup()
{
  pinMode(P_IN_01, INPUT);
  pinMode(P_IN_02, INPUT);
  pinMode(P_IN_03, INPUT);


  pinMode(P_OUT_01, OUTPUT);
  pinMode(P_OUT_02, OUTPUT);
  pinMode(P_OUT_03, OUTPUT);
  pinMode(P_OUT_04, OUTPUT);
  pinMode(P_OUT_05, OUTPUT);
  pinMode(P_OUT_06, OUTPUT);

  pinMode(PWM_01, OUTPUT);
  pinMode(PWM_02, OUTPUT);

  attachInterrupt(INT_CN0, get_btn_id, LOW); // pin 2

  Serial.begin(9600);
  Serial.println("You are welcome");


}
void loop()
{
  switch(btn_id){
    case 1:
      process_sst = true;
      process_1();
      senddata(1);
      process_sst = false;
      break;
    case 2:
      process_sst = true;
      process_2();
      senddata(2);
      process_sst = false;
      break;
    case 3:
      process_sst = true;
      process_3();
      senddata(3);
      process_sst = false;
      break;

    default:
      // process_sst = false;
      // digitalWrite(P_OUT_01, HIGH);
      // digitalWrite(P_OUT_02, HIGH);
      // digitalWrite(P_OUT_03, HIGH);
      break;
  }
  
  // digitalWrite(pin, state);
  delay(1000);
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

void process_1(void){
  digitalWrite(P_OUT_01, LOW);
  digitalWrite(P_OUT_02, HIGH);
  digitalWrite(P_OUT_03, HIGH);

  analogWrite(PWM_01,255);
  btn_id = 0;
}

void process_2(void){
  digitalWrite(P_OUT_01, HIGH);
  digitalWrite(P_OUT_02, LOW);
  digitalWrite(P_OUT_03, HIGH);
  
  analogWrite(PWM_02,255);
  btn_id = 0;
}

void process_3(void){
  digitalWrite(P_OUT_01, HIGH);
  digitalWrite(P_OUT_02, HIGH);
  digitalWrite(P_OUT_03, LOW);
  analogWrite(PWM_01,0);
  analogWrite(PWM_02,0);
  btn_id = 0;
}



void senddata(int data){
  check_rcv = 0;
  Serial.print(data, DEC);
  // while(true){
  //   if (Serial.available() > 0) {
  //     check_rcv++;
  //     if(Serial.read()==1)
  //       break;
  //     if(check_rcv>1000){
  //       Serial.println("Error");
  //       break;
  //     }
  //   }
  // }
}
