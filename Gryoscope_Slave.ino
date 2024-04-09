// slave
#include <SoftwareSerial.h>

SoftwareSerial bt(8,9);

char junk;
char t;
String inputString;

void setup()                    // run once, when the sketch starts
{
 Serial.begin(38400);            // set the baud rate to 9600, same should be of your Serial Monitor
 bt.begin(38400);
}

void loop()
{
  if(bt.available() > 0)
  {  
    t = bt.read();
    Serial.println(t);
  }
}
