#include "encoder_test.hpp"

using std_msgs::Int32;

ros::NodeHandle nh;
Int32 enc_left;
Int32 enc_right;
ros::Publisher left_enc_publisher("/enc_left",&enc_left);
ros::Publisher right_enc_publisher("/enc_right",&enc_right);


void setup() {

nh.initNode();
nh.advertise(left_enc_publisher);
nh.advertise(right_enc_publisher);

Serial.begin(115200);


pinMode(pinA,INPUT);
pinMode(pinB,INPUT);

pinMode(pinC,INPUT);
pinMode(pinD,INPUT);

CurrA = digitalRead(pinA);
CurrB = digitalRead(pinB);

CurrC = digitalRead(pinC);
CurrD = digitalRead(pinD);

LastA = CurrA;
LastB = CurrB;

LastC = CurrC;
LastD = CurrD;

}

void loop() {
  // put your main code here, to run repeatedly:

CurrA = digitalRead(pinA);
CurrB = digitalRead(pinB);

CurrC = digitalRead(pinC);
CurrD = digitalRead(pinD);

if(LastA != CurrA && LastB == CurrB){
  if(LastA == LOW && CurrA == HIGH){
    if(CurrB == LOW)
      encoderPosition1++;
    else
      encoderPosition1--;
    }
    else
      if(CurrB == HIGH)
        encoderPosition1++;
      else
        encoderPosition1--;
}

if(LastA == CurrA && LastB != CurrB){
  if(LastB == LOW && CurrB == HIGH){
    if(CurrA == HIGH)
      encoderPosition1++;
    else
      encoderPosition1--;
    }
    else
    if(CurrA == LOW)
      encoderPosition1++;
    else
      encoderPosition1--;
}

if(LastC != CurrC && LastD == CurrD){
  if(LastC == LOW && CurrC == HIGH){
    if(CurrD == LOW)
      encoderPosition2++;
    else
      encoderPosition2--;
    }
    else
      if(CurrD == HIGH)
        encoderPosition2++;
      else
        encoderPosition2--;
}

if(LastC == CurrC && LastD != CurrD){
  if(LastD == LOW && CurrD == HIGH){
    if(CurrC == HIGH)
      encoderPosition2++;
    else
      encoderPosition2--;
    }
    else
    if(CurrC == LOW)
      encoderPosition2++;
    else
      encoderPosition2--;
}


  LastA = CurrA;
  LastB = CurrB;

  LastC = CurrC;
  LastD = CurrD;

/**
  Serial.print("Encoder Position: ");
  Serial.print(encoderPosition1);
  Serial.print(" ");
  Serial.print(encoderPosition2);
  Serial.print("\n");  
**/
  current_time = millis();

  if((current_time-previous_time) > 10)
  {
  enc_left.data = encoderPosition1;
  enc_right.data = encoderPosition2;
  left_enc_publisher.publish(&enc_left);
  right_enc_publisher.publish(&enc_right);
  nh.spinOnce();
  previous_time = current_time;
  }
}
