// Example 15a.1
#include <SoftwareSerial.h>
SoftwareSerial id20(3,2); // virtual serial port
char i;
void setup()
{
 Serial.begin(9600);
 id20.begin(9600);
}
void loop ()
{
 if(id20.available()) {
 i = id20.read(); // receive character from ID20
 Serial.print(i); // send character to serial monitor
 Serial.print(" ");
 }
}