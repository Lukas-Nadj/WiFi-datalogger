#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);


void setup() {
  Serial.begin(115200);
  //WiFi.begin("EUC-iOT-HTX", "iOTeucHTX"); //Connect to the WiFi network
  //WiFi.begin("Hdæw", "12345678");
  WiFi.begin("Telenor4053myk", "kIcob7jr4");
  checkwificonnection();
  server.enableCORS(true);
}

void loop() {
  checkwificonnection();
  server.handleClient(); 
}
void temperatur(){
  server.send(200, "text/html", "123");
}
void handleRoot(){
  String page="";
 page+="<!DOCTYPE html>";
 page+="";
 page+="<head>";
 page+="    <title>Basic Layout with CSS Grid</title>";
 page+="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />";
 page+="    <meta charset=\"utf-8\" />";
 page+="";
 page+="    <script src=\"https://code.highcharts.com/highcharts.js\"></script>";
 page+="    <style>";
 page+="        body {";
 page+="            margin: 0px;";
 page+="            padding: 0px;";
 page+="            background-color: #365B7D;";
 page+="            font-family: Arial, \"Helvetica Neue\", Helvetica, sans-serif;";
 page+="            font-size: 14px;";
 page+="            color: #000;";
 page+="        }";
 page+="";
 page+="        input[type=number]::-webkit-inner-spin-button {";
 page+="            opacity: 1;";
 page+="            background-color: gray;";
 page+="            background: gray;";
 page+="        }";
 page+="";
 page+="        input[type=number] {";
 page+="            width: 10vh;";
 page+="            height: 1em;";
 page+="        }";
 page+="";
 page+="        .grid div {";
 page+="            padding: 10px;";
 page+="            border: 1px solid #000000;";
 page+="            background-color: #D9D9D9;";
 page+="        }";
 page+="";
 page+="        .grid {";
 page+="            width: 100vw;";
 page+="            height: 100vh;";
 page+="";
 page+="            display: grid;";
 page+="";
 page+="            grid-template-columns: repeat(4, 1fr);";
 page+="            grid-template-rows: 0.3fr;";
 page+="";
 page+="            gap: 10px;";
 page+="            padding: 10px;";
 page+="            box-sizing: border-box;";
 page+="        }";
 page+="";
 page+="        .chart {";
 page+="            display: unset;";
 page+="            display: flex;";
 page+="            justify-content: center;";
 page+="            align-items: center;";
 page+="            background-color: #365B7D !important;";
 page+="            border-color: #365B7D !important;";
 page+="            margin: 0;";
 page+="            grid-row-start: 1;";
 page+="            grid-row-end: 1;";
 page+="            grid-column-start: 2;";
 page+="            grid-column-end: 5;";
 page+="        }";
 page+="";
 page+="        .container div {";
 page+="            padding: 0px;";
 page+="        }";
 page+="";
 page+="        .container {";
 page+="            display: revert;";
 page+="            border-color: #D9D9D9;";
 page+="            padding: 0px !important;";
 page+="            width: 1000px;";
 page+="            height: 400px;";
 page+="";
 page+="        }";
 page+="";
 page+="        .container div {";
 page+="            position: relative;";
 page+="            top: 0px;";
 page+="            left: 0px;";
 page+="            padding: -10px;";
 page+="";
 page+="        }";
 page+="";
 page+="        .box {";
 page+="            margin: 0;";
 page+="            padding: 0 px;";
 page+="            line-height: 2.4;";
 page+="            grid-row-start: 1;";
 page+="            grid-row-end: 1;";
 page+="            grid-column-start: 1;";
 page+="            grid-column-end: 2;";
 page+="        }";
 page+="    </style>"; 
 page+="</head>";
 page+="";
 page+="<body>";
 page+="    <div class=\"grid\">";
 page+="        <div class=\"box\">";
 page+="            <form action=\"stop.html\">";
 page+="                <input type=\"number\" name=\"Frekvens\" id=\"\" required> Frekvens <br>";
 page+="                <input type=\"number\" name=\"Punkter\" id=\"\" required> Hvor mange gemter punkter? <br>";
 page+="                <input type=\"text\" name=\"Destination\" id=\"\" required> Destination <br>";
 page+="                <select name=\"cars\" id=\"cars\" required>";
 page+="                    <option value=\"V+A\">Volt+Ampere meter</option>";
 page+="                    <option value=\"P\">Tryksensor</option>";
 page+="                    <option value=\"T\">Temperaturmåler</option>";
 page+="                </select> Sensor <br>";
 page+="                <input type=\"submit\" value=\"Submit\">";
 page+="            </form>";
 page+="        </div>";
 page+="        <div class=\"chart\">";
 page+="            <div id=\"chart-temperature\" class=\"container\"></div>";
 page+="        </div>";
 page+="        <script>";
 page+="";
 page+="var chartT = new Highcharts.Chart({";
 page+="    chart:{ renderTo : 'chart-temperature' },";
 page+="    title: { text: 'DataGraf' },";
 page+="    series: [{";
 page+="      showInLegend: true,";
 page+="      name: 'Voltage',";
 page+="      data: []";
 page+="    }, {";
 page+="      showInLegend: true,";
 page+="      name: 'Amperes',";
 page+="      data: []";
 page+="    }],";
 page+="    plotOptions: {";
 page+="      line: { animation: false,";
 page+="        dataLabels: { enabled: true }";
 page+="      },";
 page+="      series: { color: '#059e8a' }";
 page+="    },";
 page+="    xAxis: { type: 'datetime',";
 page+="      dateTimeLabelFormats: { second: '%H:%M:%S' }";
 page+="    },";
 page+="    yAxis: {";
 page+="      title: { text: 'Temperature (Celsius)' }";
 page+="    },";
 page+="    credits: { enabled: false }";
 page+="  });";
 page+="  setInterval(function ( ) {";
 page+="    var xhttp = new XMLHttpRequest();";
 page+="    xhttp.onreadystatechange = function() {";
 page+="      if (this.readyState == 4 && this.status == 200) {";
 page+="        var x = (new Date()).getTime(),";
 page+="            y = parseFloat(this.responseText);";
 page+="        if(chartT.series[0].data.length > 40) {";
 page+="          chartT.series[0].addPoint([x, y], true, true, true);";
 page+="        } else {";
 page+="          chartT.series[0].addPoint([x, y], true, false, true);";
 page+="        }";
 page+="      }";
 page+="    };";
 page+="    xhttp.open(\"GET\", \"http://\"+window.location.hostname+\"/temperature\", true);";
 page+="    xhttp.send();";
 page+="  }, 1000 ) ;";
 page+="  ";
 page+="  ";
 page+="";
 page+="        </script>";
 page+="    </div>";
 page+="</body>";

  server.send(200, "text/html", page);
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
