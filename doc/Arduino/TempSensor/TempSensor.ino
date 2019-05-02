#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 26
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 125);
IPAddress server(192, 168, 43, 18);

float humidity = 0;
float celsius = 0;
float fahrenheit = 0;
char valBuff[40];

//Wifi Stuff
const char* ssid     = "Jesses10+";
const char* password = "gobison!";
WiFiServer wifiCon(80);

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("raspi","Lights Relay Connected");
      // ... and resubscribe
      client.subscribe("home/sensors/1");
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

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
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

  dht.begin();

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if ((millis() % 2000) == 0)
  {
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
  
    Serial.println(valBuff);
    client.publish("raspi/sensors/1", valBuff);
  }
}
