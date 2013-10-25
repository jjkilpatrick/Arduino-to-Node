    #include <SPI.h>
    #include <WiFly.h>
    #include <PubSubClient.h>
    #include <Ethernet.h>
    #include "wifi_credentials.h"

    int missilePin = 4;
    int missileSwitch = LOW;
    int missileSwitchActive = false;

    char* onSignal = "1";
    char* offSignal = "0";

    char* sam = "4400E6FF5508";
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

    char* burrito = "3/";
    char* mainStage = "1/";
    char* secondStage = "2/";
    char* entrance = "entrace/";


    void subscriptions (char* topic, byte* payload, unsigned int length) {

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

    if(missileSwitch == HIGH){

        if ( missileSwitchActive == false) {

                Serial.println("missileSwitch is on");
                cl.publish(burrito, sam);

                missileSwitchActive = true;
        }

    } else {

        missileSwitchActive = false;
    }

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

        Serial.println("MQTT connected.");

    } else {

        Serial.println("NOT Connected : MQTT failed");
    }


}