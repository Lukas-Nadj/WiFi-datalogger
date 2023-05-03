#include <ESP8266WiFi.h> //wifi kapabilitet
#include <ESP8266WebServer.h> //wifi webserver, lytter til http og sender hjemmeside tilbage
#include <ESP8266mDNS.h> //Lokalt domæne f.eks. "esp8266.local"
#include <WiFiManager.h>  //automatisk skift af wifi mode til AP så man kan indstille wifi.
#include <SPI.h> //SPI kontrol
#include <SD.h> //SD Kort funktioner

WiFiManager wifiManager;
ESP8266WebServer server(80); //tallet '80' er porten det serveres på. http og https fra hjemmesider sendes over port 80, porten er derfor tit forebeholdt til dette. og det er standard port for browseren.
int timer = 0;

//pointers til aktive forsøgs-fil, og Boolean optagelse
bool optag = false;
File loglocation;
int frekvens = 0;
int mål = 0;
String sensor;


void setup() {
  //begynd serial.
  Serial.begin(115200);

  //Autoconnecter til gemt wifi og sætter et access point op til at skifte wifi ell. skrive information ind.
  wifiManager.autoConnect("esp8266 wifimanager");
  Serial.println(WiFi.localIP()); // printer ip til konsol.

  //definere weblokationer på domænet, requests at lytte efter og funktionerne til at håndtere dem.
  server.on("/", handleRoot);
  server.on("/data", Data); //håndteres af funktionen "data" 
  server.on("/toggleforsøg", toggle);
  server.on("/delete", Delete); //etc
  server.on("/voltagedata", voltagedata);
  
  // Cross Origin Resource Sharing. tilladelse til at hente hjemmesiden fra andre domæner. (det er normalt fra, på mange hjemmesider som YOUTUBE for at beskytte din information)
  server.enableCORS(true);   if (MDNS.begin("esp8266")) { //er mDNS sat op og klar?
    Serial.println("MDNS Responder Started"); //JA
    MDNS.addService("http", "tcp", 80); //lyt på domænet
  } else {
    Serial.println("MDNS Responder did not start"); //NEJ, øv
  }
  
  //starter webserveren op.
  server.begin();

  //kører sd.begin som initialisere SD objektet/library, og checker om det lykkes.
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present"); 
  }
}

void loop() {
  // Broadcaster og opdatere domænet til ruteren/ap.
  MDNS.update();
  if (millis() > timer + 10000) { //annoncere kun periodisk
    MDNS.announce();
    timer = millis();
  }

  if(optag&&loglocation!=null&&millis()>=mål){ // tid til at måle igen?
    //tilføj ny linje til dokumentet og flush
    if(sensor.equals(String("voltage"))){ //hvis vi logger volt.
        //append "String(analogRead(A0) / 320.0, 5)"
    } // else if humidity, etc.
    mål = millis()+frekvens; //refresh timeren.
  }
  

  //tjekker om der er indgående forbindelser og håndtere dem (se server.on() i setup).
  server.handleClient();
}

//---------------------FORSØG PÅ SD KORTET------------------
void Data() { 
  //åbner data mappen, som er standard lokation for vores forsøg på sd.
  File dir = SD.open("/data/");

  String Filer = "";
  while (true) {
    File entry = dir.openNextFile();
    if (!entry/* Er der ikke flere filer i mappen? */) {
      break; //stop loop
    }
    if (!entry.isDirectory() && String(entry.name()).charAt(0) != '.' && String(entry.name()).charAt(1) != '_') {
      /* Filen må ikke være en mappe, og må ikke starte med punktum, da det så ville være en skjult fil, der nogengange skabes for at give mere information om andre filer */
      /* og må heller ikke starter med _ af samme årsag, nogle SD formateringer skaber kopuier. */
      Filer += String(entry.name()) + String("\n");
    }
  }
  server.send(200, "text/plain", Filer);
}
//test
void handleRoot() {
  server.send(200, "text/plain", "bruh");
}

//---------------------DATALOGGER------------------
void voltagedata() {
  //analogRead læser værdier mellem 0 og 3.2 volt. ved at dividere med 320 ændre fra en værdi mellem 0-1024 til 0 - 3.2 hvilket svarer til volt
  server.send(200, "text/plain", String(analogRead(A0) / 320.0, 5)); 
  //sender rå data
}


void toggle(){  
  //TODO 
    //nyt formål server arg.
    //start og stop esp forsøg.
    //find hvordan man logger på filen.
  String argumentet = String(server.arg("formål"));
  
  //sender staten af forsøget (er forsøget i gang eller ej?)
  if(argumentet.equals(String("PING"))){ 
    server.send(200, "text/plain", String(optag));  
  } else 
  //Starter et nyt forsøg
  if (argumentet.equals(String("start"))){
    optag = true;  
    /*  IMPORTANT
     if(sd exists("filename")){
      server.send ("taken")
      } else {
        lav en ny fil og .csv header
         loglocation = new file blabla
      }
    */
    frekvens = 1000/toInt(String(server.arg("Frekvens"))); //frekvens til millisekund delay
    mål = millis()+frekvens;
  } else
  //stopper asynkron måling
  if(argumentet.equals(String("stop"))){
    optage = false;
    loglocation = null; //
  }
  
}



//---------------------SD KORT------------------
void Delete() { //SLET FORSØG/FIL
  //åbner forsøgsmappen
  File dir = SD.open("/data/");
  int numTabs = 2;
  String Filer = "";
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    //sammenligner navnet af filen der skal slettes, med filen vi er nået til
    if (String(entry.name()) == String(server.arg("filename"))) { 
      SD.remove(server.arg("filename")); //slet filen med det navn
      Serial.println(String("/data/")+String(server.arg("filename"))); //print at vi sletter.
    }
  }
  server.send(200, "text/plain", "deleted, " + String(server.arg("filename")));
  //server.send sender 3 argumenter som følge af http protokollet. 1. statuskode (200 -> OK) 2. dataformat 3. DATA
}
