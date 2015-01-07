#include <Bridge.h>
#include <YunClient.h>
#include <MQTTClient.h>

#define PRESSURE_FRONT A0
#define PRESSURE_BACK A1

int pressureFront = 0;
int pressureBack = 0;

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("incoming: ");
 Serial.write(payload, length);
 Serial.println();
}

YunClient net;
MQTTClient client("connect.shiftr.io", 1883, net);

void setup()
{
  Bridge.begin();
  Serial.begin(9600);

  pinMode(PRESSURE_FRONT, INPUT);
  pinMode(PRESSURE_BACK, INPUT);
  
  Serial.println("connecting...");
  if (client.connect("teet-alpha", "2ba467a7534549c6", "d955e5d5a02418a35b0fbb58eefb2844")) {
   Serial.println("connected!");
 } else {
   Serial.println("not connected!");
 }
}

void loop()
{
  client.loop();
  
  pressureFront = analogRead(PRESSURE_FRONT);
  pressureBack = analogRead(PRESSURE_BACK);
  
  if (pressure1 >= 940) {
    sendFront();
  }
  
  if (pressure2 >= 940) {
    sendBack();
  }
}

void sendFront()
{
  // sende Daten an /input/front
  client.publish("/input/front", String(pressure1));
}

void sendBack()
{
  // sende Daten an /input/back
  client.publish("/input/back", String(pressure2));
}