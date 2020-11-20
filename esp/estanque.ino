#define NODEBUG_SOCKETIOCLIENT
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <ESP8266httpUpdate.h>
char* redHTML = "0";
char* greenHTML = "0";
char* blueHTML = "0";

SocketIoClient webSocket;
void eventRED(const char* payload, size_t length) {
  Serial.println(payload);
  redHTML = strdup(payload);
}

void eventBLUE(const char* payload, size_t length) {
  Serial.println(payload);
  blueHTML = strdup(payload);
}

void eventGREEN(const char* payload, size_t length) {
  Serial.println(payload);
  greenHTML = strdup(payload);
  Serial.println(redHTML);
  Serial.println(blueHTML);
  Serial.println(greenHTML);
}

int RPIN = 14;
int GPIN = 13;
int BPIN = 12;



const char* ssid = "Vasoamarillo 2.4";
const char* password = "CINCO8CABLES";
void setup(void) {
  
  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  
  
  Serial.begin(115200);
//  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); 
  Serial.println("...");
  
  int i = 0;

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(++i); Serial.print(' '); 
  }
  
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP adress:\t");
  Serial.println(WiFi.localIP());

  webSocket.on("REDValue", eventRED);
  webSocket.on("BLUEValue", eventGREEN);
  webSocket.on("GREENValue", eventBLUE);
 
  //webSocket.emit("test", "\"arduino fabio\"");
  webSocket.begin("estanque.herokuapp.com", 80, "/socket.io/?transport=websocket");
  
  
}

void loop() {
  webSocket.loop();
  
  int redINT; 
  sscanf(redHTML, "%d", &redINT);
  int blueINT; 
  sscanf(blueHTML, "%d", &blueINT); 
  int greenINT; 
  sscanf(greenHTML, "%d", &greenINT); 

  
  setColor(redINT, blueINT, greenINT);
  delay(500);
}

void setColor(int red, int blue, int green){
  analogWrite(RPIN, red);
  analogWrite(GPIN, green);
  analogWrite(BPIN, blue);
}
