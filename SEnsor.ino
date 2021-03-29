#include <ESP8266WiFi.h>
String apiKey = "8QN86N7GDA4VF3EJ"; // Enter your Write API key from ThingSpeak
const char *ssid = "User_Hannover_188" ;// replace with your wifi ssid and wpa2 key
const char *pass = "Wir_wohnen_in_Hannover188";
const char* server = "api.thingspeak.com";
float Gaslevel;
WiFiClient client;
void setup()
{
Serial.begin(115200);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

if (WiFi.status() == WL_CONNECTED)
{
  WiFi.mode(WIFI_STA);
}
}
void loop()
{
float h = analogRead(A0);
if (isnan(h))
{
Serial.println("Failed to read from MQ-5 sensor!");
return;
}
 
if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
{
  Gaslevel = (h/1023*100);
String postStr = apiKey;
postStr += "&field1=";
postStr += String(h);
postStr += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
Serial.print("Gas Level: ");
Serial.println(h);
Serial.println("Data Send to Thingspeak");
}

client.stop();
Serial.println("Waiting...");
 
// thingspeak needs minimum 15 sec delay between updates.

}
