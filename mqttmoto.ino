#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define LED D0
int IN1 = D1;
int IN2 = D2;
int IN3 = D7;
int IN4 = D6;
const char* ssid = "valorant";
const char* password =  "freedomwebtech";
const char* mqtt_server = "mqtt.fluux.io";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(D1,INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(MQTTcallback);
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266"))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.subscribe("test2");
}
void MQTTcallback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) 
  {
    message = message + (char)payload[i];
  }
  Serial.print(message);
  if (message == "back") 
  {
    digitalWrite(LED, LOW);
    analogWrite(IN1, 100);
    digitalWrite(IN2, LOW);
    analogWrite(IN3, 100);
    digitalWrite(IN4, LOW);
  }
   if (message == "turn") 
  {
    digitalWrite(LED, LOW);
    
   
    delay(200);
   
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(200);
   
   
  }
 
  
  if (message == "forward") 
  {
    digitalWrite(LED, LOW);
    digitalWrite(IN1, LOW);
    analogWrite(IN2,100);
    digitalWrite(IN3, LOW);
    analogWrite(IN4, 100);
  }
  else if (message == "stop") 
  {
    digitalWrite(LED, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  Serial.println();
  Serial.println("-----------------------");
}
void loop() 
{
  
  client.loop();
}
