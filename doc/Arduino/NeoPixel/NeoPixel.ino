#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>

#define LED_PIN 26
#define LED_COUNT 12

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 125);
IPAddress server(192, 168, 1, 121);

//Wifi Stuff
const char* ssid     = "Jesses10+";
const char* password = "gobison!";
WiFiServer wifiCon(80);
String header;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (payload[0] == 0x30)
  {
  }
  else
  {
  }
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/raspi", "Lights Relay Connected");
      // ... and resubscribe
      client.subscribe("/home/lights/1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

//  pinMode(26, OUTPUT);
//  pinMode(27, OUTPUT);

  strip.begin();
  strip.clear();

  int count = 0;
  bool flip = false;

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    if (flip)
    {
      strip.setPixelColor(11 - count, 0, 0, 0);
      strip.show();
      count--;
      if (count <= -1) flip = !flip;
    }
    else
    {
      count++;
      if (count >= 11) flip = !flip;
      strip.setPixelColor(count, 150, 0, 0);
      strip.show();
    }
    
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  wifiCon.begin();

  client.setServer(server, 1883);
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  strip.clear();
//  if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();
  
  

//  strip.clear();
//  Serial.println("Clearing colors");
//  for (int i = 0; i < 12; i++) {
//    strip.setPixelColor(i, count%255, (count*2)%255, (count*3)%255);
//
//    strip.show();
//    count = count + rand()*10;
//
//    delay(50);
//  }
}
