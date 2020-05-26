#include <ESP8266WiFi.h>
#include <Servo.h>
// Replace with your network credentials
const char* ssid     = "PhongTro4NG";
const char* password = "Adminlong98";
#define Motor1  D1
#define Motor2  D2
#define Motor3  D5
#define Motor4  D6
WiFiServer server(80);
Servo servo;
// Variable to store the HTTP request
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
int count = 0;
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup() {
  Serial.begin(115200);  
  // Connect to Wi-Fi network with SSID and password
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
  pinMode(Motor1,OUTPUT);
  pinMode(Motor2,OUTPUT);
  pinMode(Motor3,OUTPUT);
  pinMode(Motor4,OUTPUT);
  digitalWrite(Motor1,LOW);
  digitalWrite(Motor2,LOW);
  digitalWrite(Motor3,LOW);   
  digitalWrite(Motor4,LOW);
  server.begin();

}
void loop() {
  ////////////////////////Main/////////////////////////////////////
  
  //////////////////////////////WEB SITE/////////////////////////////
  
  WiFiClient client = server.available();   // Listen for incoming clients
   
  if (client) {                             // If a new client connects,
   
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {   
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
              
              
            if (header.indexOf("GET /on") >= 0) {
              digitalWrite(Motor1,LOW);
              digitalWrite(Motor2,1023);
            } else if (header.indexOf("GET /off") >= 0) {
              digitalWrite(Motor1,LOW);
              digitalWrite(Motor2,LOW);
            } 
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";

    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  
}
