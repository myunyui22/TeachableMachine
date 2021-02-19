#include <ESP8266WiFi.h>

 const char* ssid = "ACSLab2.4G";// 본인 스마트 폰 핫스팟의 ID
 const char* password = "acsl0103";// 본인 스마트 폰 핫스팟의 비밀번호

 int ledPin = 13; //
 WiFiServer server(80);

 void setup() {
   Serial.begin(115200);
   delay(10);

   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH);

   // Set WiFi to station mode and disconnect from an AP if it was previously connected
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(100);

   Serial.println("Setup done");

   // Connect to WiFi network
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
   Serial.println("WiFi connected");

   // Start the server
   server.begin();
   Serial.println("Server started");

   // Print the IP address
   Serial.print("Use this URL to connect: ");
   Serial.print("http://");
   Serial.print(WiFi.localIP());
   Serial.println("/");

 }

 void loop() {
   // Check if a client has connected
   WiFiClient client = server.available();
   if (!client) {
     return;
   }

   // Wait until the client sends some data
   Serial.println("new client");
   while(!client.available()){
     delay(1);
   }

   // Read the first line of the request
   String request = client.readStringUntil('\r');
   Serial.println(request);
   client.flush();

   // Match the request

   int value = LOW;
   if (request.indexOf("/LED=ON") != -1)  {
     digitalWrite(ledPin, LOW);
     value = HIGH;
   }

 // Set ledPin according to the request

   // Return the response
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println(""); //  do not forget this one
   client.println("<!DOCTYPE HTML>");

client.print("<html>");
client.print("<head>");

//client.print("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>");
client.print("<div style='text-align:center;width:400px;padding:1em 0;'> <h2><a style='text-decoration:none;'");
client.print("href='http://www.zeitverschiebung.net/en/city/1835848'><span style='color:gray;'>");
client.print("Current local time in</span><br />Seoul, South Korea</a></h2> ");
client.print("<iframe src='http://www.zeitverschiebung.net/clock-widget-iframe-v2?language=en&timezone=Asia%2FSeoul'");
client.print("width='100%' height='150' frameborder='0' seamless></iframe> <small style='color:gray;'>© ");
client.print("<a href='http://www.zeitverschiebung.net/en/' style='color: gray;'>Time Difference</a></small> </div>");

client.print("</body>");
   client.println("</html>");
   delay(1);
   Serial.println("Client disonnected");
   Serial.println("");

 }
