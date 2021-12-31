#include "encoder_test.hpp"

using lm4075e_msgs::Int32;

ros::NodeHandle nh;
Int32 encoder_data;
ros::Publisher enc_publisher("/encoder_data",&encoder_data);

void setup() {

nh.initNode();
nh.advertise(enc_publisher);

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

  if((current_time-previous_time) >= 20)
  {
    encoder_data.left_pos = encoderPosition1;
    encoder_data.right_pos = encoderPosition2;
    enc_publisher.publish(&encoder_data);
    nh.spinOnce();
    previous_time = current_time;
  }
}
