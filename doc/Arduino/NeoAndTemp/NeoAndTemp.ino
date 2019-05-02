#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>
#include <DHT.h>

#define LED_PIN 27
#define LED_COUNT 12

#define DHTPIN 26
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

float humidity = 0;
float celsius = 0;
float fahrenheit = 0;
char valBuff[40];

byte r = 0;
byte g = 0;
byte b = 0;

unsigned long currentMs = 0;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

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
    r = (asciiToNum((byte)payload[2]) + (asciiToNum((byte)payload[1]) << 4));
    g = (asciiToNum((byte)payload[4]) + (asciiToNum((byte)payload[3]) << 4));
    b = (asciiToNum((byte)payload[6]) + (asciiToNum((byte)payload[5]) << 4));
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

void setAllNeo(byte red, byte gre, byte blu)
{
  strip.setPixelColor(0, red, gre, blu);
  strip.setPixelColor(1, red, gre, blu);
  strip.setPixelColor(2, red, gre, blu);
  strip.setPixelColor(3, red, gre, blu);
  strip.setPixelColor(4, red, gre, blu);
  strip.setPixelColor(5, red, gre, blu);
  strip.setPixelColor(6, red, gre, blu);
  strip.setPixelColor(7, red, gre, blu);
  strip.setPixelColor(8, red, gre, blu);
  strip.setPixelColor(9, red, gre, blu);
  strip.setPixelColor(10, red, gre, blu);
  strip.setPixelColor(11, red, gre, blu);
  strip.setPixelColor(12, red, gre, blu);
  strip.show();
}

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
  strip.show();

  dht.begin();

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

  static int ledMode = 0;

  static unsigned long lastMs1 = 0;
  currentMs = millis();
  static int index = 0;
  switch (ledMode)
  {
    static byte r2 = 0;
    static byte g2 = 0;
    static byte b2 = 0;
    case 0:
      if ((r2 != r) || (g2 != g) || (b2 != b) || ((currentMs - lastMs1) > 10000))
      {
        r2 = r;
        g2 = g;
        b2 = b;
        setAllNeo(r,g,b);
        lastMs1 = currentMs;
      }
      break;
    case 1:
      if ((currentMs - lastMs1) > 50)
      {
        static int lastInd = 0;
        index = (index + 1) % 12;
        strip.setPixelColor(lastInd, r, g, b);
        strip.setPixelColor(index, r, g, b);
        lastInd = index;
        strip.show();
        lastMs1 = currentMs;
      }
      break;
    case 2:
      if ((currentMs - lastMs1) > 500)
      {
        index = (index + 1) % 2;
        strip.clear();
        for (int i = 0; i < LED_COUNT/2; i++)
        {
          strip.setPixelColor((i * 2) + (index), r, g, b);
        }
        lastMs1 = currentMs;
        strip.show();
      }
      break;
    default:
      break;
  }

  static unsigned long lastMs2 = 0;
  if ((currentMs - lastMs2) > 10000)
  {
    ledMode = (ledMode + 1) % 3;
    lastMs2 = currentMs;
  }

  static unsigned long lastMs3 = 0;
  if ((currentMs - lastMs3) > 10000)
  {
    lastMs3 = currentMs;
    //Read values
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();
    fahrenheit = dht.readTemperature(true);
  
    //Publish Values
    for (int i = 0; i < sizeof(valBuff); i++)
    {
      valBuff[i] = 0x00;
    }
  
    sprintf(valBuff, "%3.1f_%3.1f_%3.1f", humidity, celsius, fahrenheit);
    client.publish("raspi/sensors/1", valBuff);
  }
}
