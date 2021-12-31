#include <ros.h>
#include <lm4075e_msgs/Int32.h>
#include <Arduino.h>

#define pinA 4
#define pinB 5
#define pinC 2
#define pinD 3

int LastA, LastB;
int CurrA, CurrB;
long encoderPosition1 = 0;

int LastC, LastD;
int CurrC, CurrD;
long encoderPosition2 = 0;
unsigned long current_time = 0;
unsigned long previous_time = 0;
