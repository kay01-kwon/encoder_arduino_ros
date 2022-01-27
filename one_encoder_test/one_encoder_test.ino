#include "one_encoder_test.hpp"

using std_msgs::Int32;

ros::NodeHandle nh;
Int32 encoder_data;
ros::Publisher enc_publisher("/encoder_data",&encoder_data);

void setup() {
  // put your setup code here, to run once:

nh.initNode();
nh.advertise(enc_publisher);

Serial.begin(115200);

pinMode(pinA,INPUT);
pinMode(pinB,INPUT);

CurrA = digitalRead(pinA);
CurrB = digitalRead(pinB);

LastA = CurrA;
LastB = CurrB;

}

void loop() {
  // put your main code here, to run repeatedly:
CurrA = digitalRead(pinA);
CurrB = digitalRead(pinB);


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

  LastA = CurrA;
  LastB = CurrB;

    current_time = millis();

  if((current_time-previous_time) >= 20)
  {
    encoder_data.data = encoderPosition1;
    enc_publisher.publish(&encoder_data);
    nh.spinOnce();
    previous_time = current_time;
  }

}
