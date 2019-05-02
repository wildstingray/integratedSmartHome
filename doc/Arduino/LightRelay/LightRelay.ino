#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 125);
IPAddress server(192, 168, 43, 18);

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

  if (payload[0] == 0x30)
  {
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(25, LOW);
  }
  else
  {
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(25, HIGH);
  }
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
      client.subscribe("home/lights/1");
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

  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(25, OUTPUT);
  // Set outputs to LOW
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(25, LOW);

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
