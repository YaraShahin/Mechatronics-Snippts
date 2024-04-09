#include "Arduino.h"
#include<Wire.h>

int rMotor1 = 7;
int rMotor2 = 8;
int rMotor = 6;

int lMotor1 = 10;
int lMotor2 = 11;
int lMotor = 9;

int rPower = 70;
int lPower = 70;

const int MPU_addr = 0x69;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

char mpu() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

  Serial.print("AngleY= ");
  Serial.println(y);

  //here u can include if statements with angle ranges to send a char for each direction
  if (y > 97 or y < 83) return 'f';
  else return 'd';
}

void brake() {
  Serial.println("brake");
  digitalWrite(rMotor1, LOW);
  digitalWrite(rMotor2, LOW);
  digitalWrite(lMotor1, LOW);
  digitalWrite(lMotor2, LOW);
  analogWrite(rMotor, 0);
  analogWrite(lMotor, 0);
}

void reverse() {
  Serial.println("reverse");

  digitalWrite(rMotor1, HIGH);
  digitalWrite(rMotor2, LOW);
  digitalWrite(lMotor1, LOW);
  digitalWrite(lMotor2, HIGH);

  analogWrite(rMotor, rPower);
  analogWrite(lMotor, lPower);
}

void right() {
  Serial.println("right");

  digitalWrite(rMotor1, HIGH);
  digitalWrite(rMotor2, LOW);
  digitalWrite(lMotor1, HIGH);
  digitalWrite(lMotor2, LOW);
}

void left() {
  Serial.println("left");

  digitalWrite(rMotor1, LOW);
  digitalWrite(rMotor2, HIGH);
  digitalWrite(lMotor1, LOW);
  digitalWrite(lMotor2, HIGH);
}



void setup() {
  Serial.begin(9600);

  pinMode(rMotor1, OUTPUT);
  pinMode(rMotor2, OUTPUT);
  pinMode(lMotor1, OUTPUT);
  pinMode(lMotor2, OUTPUT);

  pinMode(rMotor, OUTPUT);
  pinMode(lMotor, OUTPUT);


  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  //WARNING: This 3azama of a code is uncompiled, untested, and written by Yara. That's three reasons for it not to work. 
  //Happy Debugging!
}

void loop() {
  char d = mpu();
    if (d == 'f') {
      digitalWrite(rMotor1, HIGH);
      digitalWrite(rMotor2, LOW);
      digitalWrite(lMotor1, LOW);
      digitalWrite(lMotor2, HIGH);

      analogWrite(rMotor, rPower);
      analogWrite(lMotor, lPower);
    }
    if (d == 'r') right();
    //etc
    
}