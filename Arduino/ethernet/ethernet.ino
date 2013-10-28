#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x02, 0xE0 };
byte ip[] = { 192, 168, 1, 123 };
byte samip[] = { 192, 168, 1, 147 }; // DEVELOPMENT

SoftwareSerial id20(3,2); // virtual serial port
int RFIDResetPin = 7;
EthernetClient client;

// Sam
char* onSignal = "1";
char* offSignal = "0";
char* burrito = "3/";
char* mainStage = "1/";
char* secondStage = "2/";
byte currentPayload;
PubSubClient cl(samip, 8080, subscriptions, client);

// Register Tags
char tag1[13] = "4400E6A4D2D4";
char tag2[13] = "4400E6EF93DE";
char tag3[13] = "4400E6A02A28";
char tag4[13] = "4400E6FF5508";
char tag5[13] = "4400E6BFADB0";
char tag6[13] = "4400E6FE4B17";
char tag7[13] = "4400E6FB7A23";

void subscriptions (char* topic, byte* payload, unsigned int length) {

}

// Setup Function
void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  id20.begin(9600);

  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);

  // LED
  pinMode(8, OUTPUT); // RED LED
  pinMode(9, OUTPUT); // GREEN LED

  mqttSubscribe();

}

// Main Loop
void loop() {

  int index = 0;
  boolean reading = false;
  char tagString[13];

  // Check to see if Serial data is avaible
  while(id20.available()){

    // Reads incoming serial data
    // Read next available byte
    int readByte = id20.read();

    // Print out serial data
    Serial.print("I received: ");
    Serial.println(readByte);

    if(readByte == 2) reading = true;
    if(readByte == 3) reading = false;

    if(reading && readByte != 2 && readByte != 10 && readByte != 13){
      // Temporary store the tag
      tagString[index] = readByte;
      index ++;
    }

  } // end while

  // Check the tag against stored tags
  // Clear the tagString
  // Reset the reader
  checkTag(tagString);
  clearTag(tagString);
  resetReader();

}


void checkTag(char tag[]){
// Check tag against known tags

  // Empty tag
  if(strlen(tag) == 0) return; //empty, no need to contunue

  if(compareTag(tag, tag1)){ // if matched tag1, do this
    lightLED(8);
    cl.publish(mainStage, tag1);
  } else if(compareTag(tag, tag2)){
    lightLED(8);
    cl.publish(mainStage, tag2);
  } else if(compareTag(tag, tag3)){
    lightLED(8);
    cl.publish(mainStage, tag3);
  } else if(compareTag(tag, tag4)){
    lightLED(8);
    cl.publish(mainStage, tag4);
  } else if(compareTag(tag, tag5)){
    lightLED(8);
    cl.publish(mainStage, tag5);
  } else if(compareTag(tag, tag6)){
    lightLED(8);
    cl.publish(burrito, tag6);
    } else if(compareTag(tag, tag7)){
    lightLED(8);
    cl.publish(burrito, tag7);
  } else {
    lightLED(9);
  }

}

void mqttSubscribe(){

  if (cl.connect("Arduino")) {

      //List Topics to subscribe to ->
      // cl.publish(connectedCheck, onSignal);

      Serial.println("MQTT connected.");

  } else {

      Serial.println("NOT Connected : MQTT failed");
  }

}

void clearTag(char one[]){
// clear the char array by filling with null - ASCII 0

  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}

void lightLED(int pin){
// Turn on LED pin for 250ms

  digitalWrite(pin, HIGH);   // turn the pin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);

}

void resetReader(){
// Reset reader to read again

  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(150);

}

boolean compareTag(char one[], char two[]){
// Compare two value to see if same,

  if(strlen(one) == 0) return false; //empty

  for(int i = 0; i < 12; i++){
    if(one[i] != two[i]) return false;
  }

  return true; //no mismatches
}