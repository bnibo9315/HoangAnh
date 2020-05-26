#include <ESP8266WiFi.h>

// Initialize sensor parameters
#define sensor1 4
#define sensor2 5
// Initialize network parameters
const char* ssid = "PhongTro4NG";
const char* password = "Adminlong98";
const char* host = "192.168.1.36"; // as specified in Host.ino
const int httpPort = 80;
int text_send ;
WiFiClient client;
int value1 = 1 ;
int value2 = 2;
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Connecting to Network");
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, password);               // Matching the SSID and Password
  delay(1000);

  // Waiting to connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Status : Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------------------");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(host);
}
void loop() {
  sent_text();
  delay(200);
}
void sent_text()
{
  int value1 = digitalRead(sensor1);
  int value2 = digitalRead(sensor2);
  
  int data_assignment = 0;
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  if(value1 == 1 && value2 == 1 )
  {
  client.println("OffAll");
  Serial.print("OffAll");
  delay(500); 
  }
  else if (value1 == 1 && value2 != 1)
  {
  client.println("OffOn");
  Serial.print("OffOn");
  delay(500);
  }
  else if(value2 == 1 && value1 != 1 )
  {
  client.println("OnOff");
  Serial.print("OnOff");
  delay(500);
  }
  else
  {
  client.println("OnAll");
  Serial.print("OnAll");
  delay(500);
  }
  
}
