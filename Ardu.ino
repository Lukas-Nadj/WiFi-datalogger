#include "circ_buff.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>  // Include the mDNS library
#include <ESP8266HTTPClient.h>
#include <SPI.h>  // include library SPI.h
#include <SD.h>   // include library SD.h

File myFile;  // create object myFile from File

String ESPNAVN = "esp8266-0";
char hostname[10];
const char* service = "_http._tcp.local";
const char filnavn[] = "dinmor.csv";
ESP8266WebServer server(80);
int timer = 0;
circ_buff<float> buffer();


void setup() {
  //---------------------------------------------Serial og SD---------------------------------------------
  Serial.begin(115200);
  while (!Serial)
    ;
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }

  //---------------------------------------------WIFI---------------------------------------------
  //WiFi.begin("Telenor4053myk", "kIcob7jr4");
  WiFi.begin("Hdæw", "12345678");
  //WiFi.begin("EUC-iOT-HTX", "iOTeucHTX");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Find an available hostname
  String hostname;
  for (int i = 0; i < 20; i++) {
    hostname = "esp8266-" + String(i);
    if (isHostnameAvailable(hostname)) {
      Serial.println("Hostname " + hostname + " is available.");
      break;
    } else {
      Serial.println("Hostname " + hostname + " is taken.");
    }
  }

  // Set the hostname and start the mDNS responder
  if (MDNS.begin(hostname.c_str())) {
    Serial.println("mDNS responder started: " + hostname);
  } else {
    Serial.println("Error starting mDNS responder.");
  }

  // Add the HTTP service to mDNS
  MDNS.addService("http", "tcp", 80);

  // Start the server
  server.on("/", handleRoot);
  server.on("/temperature", temperatur);
  server.on("/voltage", voltage);
  server.on("/Data", Data);

  server.begin();

  Serial.println("Server started.");
}



void loop() {
  MDNS.update();

  if (millis() > timer + 10000) {
    MDNS.announce();
    timer = millis();
  }
  server.handleClient();
}
void temperatur() {
  server.send(200, "text/html", String(analogRead(A0) / 320.0, 5));
}
void Data() {
  //for (i = 0; i < 1; i++) {



    
 // }
  SD.open("/data/");
}
void voltage() {
  String str = server.arg("filename");
  char* cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  newfile("Voltage, Ampere", cstr);
  server.send(200, "text/html", String(analogRead(A0) / 320.0, 5));
}
void handleRoot() {
  Serial.println(server.arg("filename"));
  //thething
  String page = "";
  page += "<!DOCTYPE html>";
  page += "";
  page += "<head>";
  page += "    <title>Basic Layout with CSS Grid</title>";
  page += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />";
  page += "    <meta charset=\"utf-8\" />";
  page += "";
  page += "    <script src=\"https://code.highcharts.com/highcharts.js\"></script>";
  page += "    <style>";
  page += "        body {";
  page += "            margin: 0px;";
  page += "            padding: 0px;";
  page += "            background-color: #365B7D;";
  page += "            font-family: Arial, \"Helvetica Neue\", Helvetica, sans-serif;";
  page += "            font-size: 14px;";
  page += "            color: #000;";
  page += "        }";
  page += "";
  page += "        input[type=number]::-webkit-inner-spin-button {";
  page += "            opacity: 1;";
  page += "            background-color: gray;";
  page += "            background: gray;";
  page += "        }";
  page += "";
  page += "        input[type=number] {";
  page += "            width: 10vh;";
  page += "            height: 1em;";
  page += "        }";
  page += "";
  page += "        .grid div {";
  page += "            padding: 10px;";
  page += "            border: 1px solid #000000;";
  page += "            background-color: #D9D9D9;";
  page += "        }";
  page += "";
  page += "        .grid {";
  page += "            width: 100vw;";
  page += "            height: 100vh;";
  page += "";
  page += "            display: grid;";
  page += "";
  page += "            grid-template-columns: repeat(4, 1fr);";
  page += "            grid-template-rows: 0.3fr;";
  page += "";
  page += "            gap: 10px;";
  page += "            padding: 10px;";
  page += "            box-sizing: border-box;";
  page += "        }";
  page += "";
  page += "        .chart {";
  page += "            display: unset;";
  page += "            display: flex;";
  page += "            justify-content: center;";
  page += "            align-items: center;";
  page += "            background-color: #365B7D !important;";
  page += "            border-color: #365B7D !important;";
  page += "            margin: 0;";
  page += "            grid-row-start: 1;";
  page += "            grid-row-end: 1;";
  page += "            grid-column-start: 2;";
  page += "            grid-column-end: 5;";
  page += "        }";
  page += "";
  page += "        .container div {";
  page += "            padding: 0px;";
  page += "        }";
  page += "";
  page += "        .container {";
  page += "            display: revert;";
  page += "            border-color: #D9D9D9;";
  page += "            padding: 0px !important;";
  page += "            width: 1000px;";
  page += "            height: 400px;";
  page += "";
  page += "        }";
  page += "";
  page += "        .container div {";
  page += "            position: relative;";
  page += "            top: 0px;";
  page += "            left: 0px;";
  page += "            padding: -10px;";
  page += "";
  page += "        }";
  page += "";
  page += "        .box {";
  page += "            margin: 0;";
  page += "            padding: 0 px;";
  page += "            line-height: 2.4;";
  page += "            grid-row-start: 1;";
  page += "            grid-row-end: 1;";
  page += "            grid-column-start: 1;";
  page += "            grid-column-end: 2;";
  page += "        }";
  page += "    </style>";
  page += "</head>";
  page += "";
  page += "<body>";
  page += "    <div class=\"grid\">";
  page += "        <div class=\"box\">";
  page += "            <form action=\"stop.html\">";
  page += "                <input type=\"number\" name=\"Frekvens\" id=\"\" required> Frekvens <br>";
  page += "                <input type=\"number\" name=\"Punkter\" id=\"\" required> Hvor mange gemter punkter? <br>";
  page += "                <input type=\"text\" name=\"Destination\" id=\"\" required> Destination <br>";
  page += "                <select name=\"cars\" id=\"cars\" required>";
  page += "                    <option value=\"V+A\">Volt+Ampere meter</option>";
  page += "                    <option value=\"P\">Tryksensor</option>";
  page += "                    <option value=\"T\">Temperaturmåler</option>";
  page += "                </select> Sensor <br>";
  page += "                <input type=\"submit\" value=\"Submit\">";
  page += "            </form>";
  page += "        </div>";
  page += "        <div class=\"chart\">";
  page += "            <div id=\"chart-temperature\" class=\"container\"></div>";
  page += "        </div>";
  page += "        <script>";
  page += "";
  page += "var chartT = new Highcharts.Chart({";
  page += "    chart:{ renderTo : 'chart-temperature' },";
  page += "    title: { text: 'DataGraf' },";
  page += "    series: [{";
  page += "      showInLegend: true,";
  page += "      name: 'Voltage',";
  page += "      data: []";
  page += "    }, {";
  page += "      showInLegend: true,";
  page += "      name: 'Amperes',";
  page += "      data: []";
  page += "    }],";
  page += "    plotOptions: {";
  page += "      line: { animation: false,";
  page += "        dataLabels: { enabled: true }";
  page += "      },";
  page += "      series: { color: '#059e8a' }";
  page += "    },";
  page += "    xAxis: { type: 'datetime',";
  page += "      dateTimeLabelFormats: { second: '%H:%M:%S' }";
  page += "    },";
  page += "    yAxis: {";
  page += "      title: { text: 'Temperature (Celsius)' }";
  page += "    },";
  page += "    credits: { enabled: false }";
  page += "  });";
  page += "  setInterval(function ( ) {";
  page += "    var xhttp = new XMLHttpRequest();";
  page += "    xhttp.onreadystatechange = function() {";
  page += "      if (this.readyState == 4 && this.status == 200) {";
  page += "        var x = (new Date()).getTime(),";
  page += "            y = parseFloat(this.responseText);";
  page += "        if(chartT.series[0].data.length > 40) {";
  page += "          chartT.series[0].addPoint([x, y], true, true, true);";
  page += "        } else {";
  page += "          chartT.series[0].addPoint([x, y], true, false, true);";
  page += "        }";
  page += "      }";
  page += "    };";
  page += "    xhttp.open(\"GET\", \"http://\"+window.location.hostname+\"/temperature\", true);";
  page += "    xhttp.send();";
  page += "  }, 1000 ) ;";
  page += "  ";
  page += "  ";
  page += "";
  page += "        </script>";
  page += "    </div>";
  page += "</body>";

  server.send(200, "text/html", page);
}

void newfile(String heading, char nytfilnavn[]) {
  char fi[] = "/data/";
  strcpy(fi, "/data/"); /* copy name into the new var */
  strcat(fi, nytfilnavn);
  strcat(fi, ".csv");                      /* add the extension */
  File txtFile = SD.open(fi, FILE_WRITE);  //opening the file
  if (!txtFile) {                          //if file not found
    Serial.print("error opening ");
    Serial.println(filename);
    while (1)
      ;
  }
  // Add heading
  txtFile.println(heading);
}


bool isHostnameAvailable(String hostname) {
  WiFiClient client;
  HTTPClient http;
  bool isAvailable = true;

  if (http.begin(client, "http://" + hostname)) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      isAvailable = false;
    }
    http.end();
  } else {
    Serial.println("Unable to connect to HTTP server.");
  }

  return isAvailable;
}