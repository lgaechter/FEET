import processing.mqtt.*;

MQTTClient client;

void setup() {
  frameRate(1);
  background(255);
  size(200, 200);
  client = new MQTTClient(this);
  client.connect("mqtt://7dc71b64220f9034:60277088aaf9b5e71e1a5dfbeef76156@connect.shiftr.io", "randomDataGenerator");
}

void draw() {
  /*client.publish("/input/left/front", String.valueOf(randomNumber()));
  client.publish("/input/left/back", String.valueOf(randomNumber()));
  client.publish("/input/right/front", String.valueOf(randomNumber()));
  client.publish("/input/right/back", String.valueOf(randomNumber()));*/

  String value = String.valueOf(randomNumber() + "," + randomNumber() + "," + randomNumber() + "," + randomNumber());

  //println(value);

  client.publish("/input", value);
}

int randomNumber() {
  int low = 0;
  int high = 1023;

  return floor(map(random(1), 0, 1, low, high));
}

/**
 * This function is required for the shiftr connection to work
 */
void messageReceived(String topic, byte[] payload) {
  //println("new message: " + topic + " - " + new String(payload));
}
