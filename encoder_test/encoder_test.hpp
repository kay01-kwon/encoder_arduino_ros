#include <ros.h>
#include <std_msgs/Int32.h>
#include <Arduino.h>

#define pinA 2
#define pinB 3
#define pinC 4
#define pinD 5

int LastA, LastB;
int CurrA, CurrB;
long encoderPosition1 = 0;

int LastC, LastD;
int CurrC, CurrD;
long encoderPosition2 = 0;
unsigned long current_time = 0;
unsigned long previous_time = 0;
