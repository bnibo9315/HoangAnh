// Load Wi-Fi library
#include <ESP8266WiFi.h>
// Replace with your network credentials
const char* ssid     = "PhongTro4NG";
const char* password = "Adminlong98";
#define sensor1 4
#define sensor2 5
int value1 = 1 ;
int value2 = 1;
WiFiServer server(80);
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
  server.begin();

}
void loop() {
  ////////////////////////Main/////////////////////////////////////
  int value1 = digitalRead(sensor1);
  int value2 = digitalRead(sensor2);
  
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
        String text = client.readStringUntil('\r');// if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0){
            
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // x` the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta http-equiv='refresh' charshet=\"utf-8\" content='0.5' \name=\"viewport\" \">"); //http-equiv='refresh'
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println("#bay {font-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;border-collapse: collapse;width: 100%;}");
            client.println("#bay td, #bay th {border: 3px solid #ddd;padding: 8px;}");
            client.println("#bay tr:nth-child(even){background-color: #f2f2f2;}");
            client.println("#bay tr:hover {background-color: #ddd;}");
            client.println("#bay th {padding-top: 12px;padding-bottom: 12px;text-align: left;background-color: #4CAF50;color: white;}");
            client.println(".button1 {background-color: MidnightBlue; border-radius: 4px;}");
            client.println(".button2 {background-color: Red; border-radius: 4px;}");
            client.println(".button3 {background-color: Orange; border-radius: 4px;}");
            client.println(".background-image {opacity: 0.1;}");
            client.println(".background-image {opacity: 0.1;}</style>");
            client.println("<script>function OnMotor(){ var x = document.getElementById(\"OnMotor\"); x.setAttribute(\"src\", \"http://192.168.1.57/on\");};");
            client.println("function OffMotor(){ var y = document.getElementById(\"OffMotor\"); y.setAttribute(\"src\", \"http://192.168.1.57/off\"); }</script>");
            client.println("</head>");
            
            // Web Page Heading
            client.println("<body style=\"background-image: url('https://d3av3o1z276gfa.cloudfront.net/images/place/gYsaVvlH265n2JW3YW9UNYNIm0qDwuK8.jpeg');background-repeat: no-repeat;background-attachment: fixed;background-position: bottom;background-size: 300px 400px;height: 1600;width:2560;\" ><h1 style='font-size: 100px;');'>VAA AirPort </h1>");
            client.println("<table id=\"bay\">");
            client.println("<tr><th>Bay : </th><th>Fight No :</th><th>Status :</th>");
            client.println("<tr><td>Bay 1</td><td>VAA762</td><td>");
            if(value1 == 1 ){
              client.println("<img style=\"width:50px;height:50px;\" src=\"https://www.pikpng.com/pngl/b/181-1819748_green-online-icon-png-clipart.png\" alt=\"status\"  /></td>");
            }
            else
            {
              client.println("<img style=\"width:50px;height:50px;\" src=\"http://www.clker.com/cliparts/D/B/O/5/Q/z/glossy-red-icon-button-md.png\" alt=\"status\"  /></td>");
              }
              client.println("<tr><td>Bay 2</td><td>VAA442</td><td>");
            if(value2 == 1)
            {
              client.println("<img style=\"width:50px;height:50px;\" src=\"https://www.pikpng.com/pngl/b/181-1819748_green-online-icon-png-clipart.png\" alt=\"status\"  /></td>");
              }
            else
            {
              client.println("<img style=\"width:50px;height:50px;\" src=\"http://www.clker.com/cliparts/D/B/O/5/Q/z/glossy-red-icon-button-md.png\" alt=\"status\"  /></td>");
              }
            client.println("</table><h3><strong>Control device</strong></h3><button onclick=\"window.location.reload()\" class=\"button button3\">Refresh</button><button onclick=\"OnMotor()\" class=\"button button1\">Start</button><button onclick=\"OffMotor()\" class=\"button button2\">Stop</button>");
            client.println("<iframe id='OnMotor'  style='height:1px;width:1px;border:none;'></iframe>");
            client.println("<iframe id='OffMotor'  style='height:1px;width:1px;border:none;'></iframe>");
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
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
