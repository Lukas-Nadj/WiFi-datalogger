#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>  // Include the mDNS library

ESP8266WebServer server(80);
int timer = 0;

void setup() {
  Serial.begin(115200);
  //WiFi.begin("EUC-iOT-HTX", "iOTeucHTX"); //Connect to the WiFi network
  WiFi.begin("test", "boje1234");
  //WiFi.begin("Telenor4053myk", "kIcob7jr4");
  checkwificonnection();
  server.enableCORS(true);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
    MDNS.addService("http", "tcp", 80);
  } else {
    Serial.println("MDNS Responder did not start");
  }

  
}

void loop() {
  checkwificonnection();
  MDNS.update();
  if(millis()>timer+10000){
    MDNS.announce();
    timer = millis();
  }
  server.handleClient();
}
void temperatur() {
  server.send(200, "text/html", String(analogRead(A0) / 320.0, 5));
}
void handleRoot() {
  server.send(200, "text/html", "bruh");
}



void checkwificonnection() {
  bool disconnected = false;
  if (WiFi.status() != WL_CONNECTED) {
    disconnected = true;
  }
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println("Waiting to connect…");
  }
  if (disconnected) {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", handleRoot);
    server.on("/temperature", temperatur);
    server.on("/voltage", temperatur);
    //server.on("/voltage", temperatur);
    server.begin();
  }
  //Print the local IP to access the server
}
