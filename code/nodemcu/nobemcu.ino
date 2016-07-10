/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <Servo.h> 

 
Servo bservo;
Servo kservo;

const char* ssid     = ".........";
const char* password = ".........";

const char* host = "..........";

void setup() {
  
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the (unnecesary) lines of the reply from server
  String line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');
  line = client.readStringUntil('\r');

  int commaIndex = line.indexOf(';');
  String bstring = line.substring(0, commaIndex);
  String kstring = line.substring(commaIndex+1);

  Serial.println(bstring);
  Serial.println(kstring);
  
  int bpos = 180-bstring.toInt()*18;  
  if(bpos>180){
    bpos = 180;
  }

  int kpos = 180-kstring.toInt()*18;  
  if(kpos>180){
    kpos = 180;
  }

  Serial.println(bpos);
  Serial.println(kpos);

  //Attach Servos to pin 2 (D4!) and 4(D2!)
  bservo.attach(2);
  kservo.attach(4); 
  delay(100);

  bservo.write(bpos); 
  kservo.write(kpos);  

  //detach servos because of buzzing issue
  delay(100);
  bservo.detach();
  kservo.detach();  
  delay(20000);
}

