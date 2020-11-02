#include <Arduino.h>

#define P_IN_01  3
#define P_IN_02  4
#define P_IN_03  5


#define P_OUT_01  6
#define P_OUT_02  7
#define P_OUT_03  8
#define P_OUT_04  9
#define P_OUT_05  12
#define P_OUT_06  13


#define PWM_01  10
#define PWM_02  11


#define INT_CN0 0

volatile int btn_id = 0;

char process_sst = false;
int check_rcv = 0;

void get_btn_id(void);

void process_1(void);
void process_2(void);
void process_3(void);


void senddata(char data);
