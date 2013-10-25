    #include <SPI.h>
    #include <WiFly.h>
    #include <PubSubClient.h>
    #include <Ethernet.h>
    #include "wifi_credentials.h"

    int missilePin = 4;
    int missileSwitch = LOW;
    int sendValue = true;

    char* onSignal = "1";
    char* offSignal = "0";

    char* sam = "04X474DF";
    char* ash = "LN94J9K0";
    char* charles = "C78JP0K";
    char* will = "44ZXRF8G";
    char* chris = "9GJH34BB";
    char* john = "7JHK990B";

    byte currentPayload;

    int keepAliveTimer = 0;

    long connectionCheck = 0;
    int connectionTimeout = 30000; //miliiseconds

    //wifly
    byte ip[] = { 192, 168, 1, 147 }; // DEVELOPMENT
    // byte ip[] = { 178, 79, 132, 119 }; // PRODUCTION
    WiFlyClient fypClient;

    PubSubClient cl(ip, 8080, subscriptions, fypClient);

    //Topics to subscribe to
    char* nodeTopic = "5/node";

    //Publish Topics set as Char Arrays
    char* connectedCheck = "connected/yes";
    char* keepAliveTopic ="1/keepAlive";

    char* rfid = "burrito/";


    void subscriptions (char* topic, byte* payload, unsigned int length) {

    // if(String(topic) == keepAliveTopic){

    //     keepAliveTimer++;

    //     Serial.print("Keep Alive: ");
    //     Serial.println(keepAliveTimer);
    // }
}

void setup()
{
    Serial.begin(9600);

    pinMode(missilePin, INPUT_PULLUP);

    wifiConnect();
    mqttSubscribe();

}

void loop() {

    missileSwitch = digitalRead(missilePin);

    if (missileSwitch == HIGH){

        if( sendValue  == true ) {
            Serial.println("missileSwitch is on");
            cl.publish(rfid, sam);

            sendValue = false;
        }

    } else if ( missileSwitch == LOW && sendValue == false) {

            Serial.println("missileSwitch is off");
            cl.publish(rfid, will);
            sendValue = true;
    }
    //connectionChecker();    //Checks to see if connection has dropped and trys to re-connect

    cl.loop();      //MQTT Client loop function. Pub & Sub


}// End Loop

//BEGIN FUNCTIONS

void wifiConnect() {

  WiFly.begin();

  Serial.println("WiFly Connecting...");
  delay(3000);

    if (!WiFly.join(ssid, passphrase)) {

      Serial.println("Connection failed.");

      while (1) {

        Serial.println("hanging...");
      // Hang on failure.
      }
  }

  Serial.println("Connected to WiFi!");
  delay(3000);

}

void mqttSubscribe(){

    if (cl.connect("Arduino")) {

        //List Topics to subscribe to ->
        cl.publish(connectedCheck, onSignal);

        Serial.println("MQTT subscribed.");

    } else {

        Serial.println("NOT Connected : MQTT subscription failed");
    }


}

// void connectionChecker() {

//     unsigned long currentTime = millis();

//     if (currentTime - connectionCheck > connectionTimeout ) {

//         connectionCheck = currentTime;

//         if (cl.connected() == false ){

//             Serial.println("Disconnected from MQTT broker.");
//             Serial.println("Trying to re-connect..");

//             mqttSubscribe();

//         }

//         // if (fypClient.connected() == false ) {

//         //     Serial.println("Disconnected from WiFi..");
//         //     Serial.println("Trying to re-connect...");
//         //     wifiConnect();

//         // }


//     }
//}