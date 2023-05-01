#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>  // Include the mDNS library
#include <SPI.h>
#include <SD.h>


ESP8266WebServer server(80);
int timer = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin("Test", "boje1234");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect");
  }
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/data", Data);
  server.on("/delete", Delete);
  server.on("/voltagedata", voltagedata);
  server.enableCORS(true);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
    MDNS.addService("http", "tcp", 80);
  } else {
    Serial.println("MDNS Responder did not start");
  }
  server.begin();
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  MDNS.update();
  if (millis() > timer + 10000) {
    MDNS.announce();
    timer = millis();
  }
  server.handleClient();
}
void Data() {

  File dir = SD.open("/data/");
  int numTabs = 2;

  String Filer = "";
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    if (!entry.isDirectory() && String(entry.name()).charAt(0) != '.' && String(entry.name()).charAt(1) != '_') {
      Filer += String(entry.name()) + String("\n");
    }
  }
  server.send(200, "text/plain", Filer);
}

void handleRoot() {
  server.send(200, "text/plain", "bruh");
}

void voltagedata() {
  server.send(200, "text/plain", String(analogRead(A0) / 320.0, 5));
}

void Delete() {
  File dir = SD.open("/data/");
  int numTabs = 2;
  String Filer = "";
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    if (String(entry.name()) == String(server.arg("filename"))) {
      SD.remove(server.arg("filename"));
      Serial.println(String("/data/")+String(server.arg("filename")));
    }
  }
  server.send(200, "text/plain", "deleted, " + String(server.arg("filename")));
}
