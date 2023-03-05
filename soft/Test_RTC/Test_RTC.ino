#include <Wire.h>
#define RTC_ADDRESS 0x32
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

byte Minute, Hour;
byte  Week, Day, Month;
void SetRTC()
{
// sets time and date data to DS3231
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(1); // set next input to start at the Minutes register
  
  Wire.write(decToBcd(Minute)); // set minutes
  Wire.write(decToBcd(Hour)); // set hours
  Wire.write(decToBcd(Week)); // set week
  Wire.write(decToBcd(Day)); // set days
  Wire.write(decToBcd(Month)); // set month
  Wire.endTransmission();
  digitalWrite(8,LOW);  
}

void ReadRTC()                    
{
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(1); // set RTC register pointer to 01h
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 7);
  
  Minute = bcdToDec(Wire.read());
  Hour = bcdToDec(Wire.read());
  Week = bcdToDec(Wire.read());
  Day = bcdToDec(Wire.read());
  Month = bcdToDec(Wire.read());
  digitalWrite(8,LOW);  
}





void setup() {
  Wire.begin();
  Serial.begin(9600);
  Hour=14;
  Minute=33;
  ReadRTC();
}

void loop() {
  Serial.print(Hour);
  Serial.print(":");
  Serial.println(Minute);
  delay(1000);

}
