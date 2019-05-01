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
IPAddress server(192, 168, 43, 18);

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

  if (payload[0] == '#')
  {
    byte num1 = payload[1];
    byte num2 = payload[2];
    byte num3 = payload[3];
    byte num4 = payload[4];
    byte num5 = payload[5];
    byte num6 = payload[6];
    
    byte r = (asciiToNum((byte)payload[2]) + (asciiToNum((byte)payload[1]) << 4));
    byte g = (asciiToNum((byte)payload[4]) + (asciiToNum((byte)payload[3]) << 4));
    byte b = (asciiToNum((byte)payload[6]) + (asciiToNum((byte)payload[5]) << 4));
    setAllNeo(r,g,b);
  }
  else
  {
  }
}

byte asciiToNum(byte asciiChar)
{
  byte num = 0;
  if (asciiChar > 0x39)
  {
    num = asciiChar - 0x37;
  }
  else
  {
    num = asciiChar - 0x30;
  }
  num &= 0x0f;
  return num;
}

void setAllNeo(byte r, byte g, byte b)
{
  strip.setPixelColor(0, r, g, b);
  strip.setPixelColor(1, r, g, b);
  strip.setPixelColor(2, r, g, b);
  strip.setPixelColor(3, r, g, b);
  strip.setPixelColor(4, r, g, b);
  strip.setPixelColor(5, r, g, b);
  strip.setPixelColor(6, r, g, b);
  strip.setPixelColor(7, r, g, b);
  strip.setPixelColor(8, r, g, b);
  strip.setPixelColor(9, r, g, b);
  strip.setPixelColor(10, r, g, b);
  strip.setPixelColor(11, r, g, b);
  strip.setPixelColor(12, r, g, b);
  strip.show();
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
      client.publish("raspi", "Lights Relay Connected");
      // ... and resubscribe
      client.subscribe("home/leds/1");
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

  strip.begin();
  strip.clear();

  int count = -1;
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
  strip.clear();
  strip.show();
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
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
