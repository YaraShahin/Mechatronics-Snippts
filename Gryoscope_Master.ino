// master
#include<Wire.h>
#include <SoftwareSerial.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
char data;
double x;
double y;
double z;

SoftwareSerial bt(8,9);

void setup(){
  Serial.begin(38400);
  bt.begin(38400);
    
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
   
  Serial.print("AngleX= ");
  Serial.println(x);
   
  Serial.print("AngleY= ");
  Serial.println(y);
   
  //Serial.print("AngleZ= ");
  //Serial.println(z);
  
  delay(400);

  if (x<340 && x>290) {
    bt.write('f');
    Serial.println('f');
  }
   
    
  else if (x>20 && x<60) {
      bt.write('b');
      Serial.println('b');
  }
  
  
  else if (y<315 && y>260) {
      Serial.println("r");
      bt.write('r');
  }
   
  else if (y>10 && y<80) {
      Serial.println("l");
      bt.write('l');
  }

  bt.flush();

}
