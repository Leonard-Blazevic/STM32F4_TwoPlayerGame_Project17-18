#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define NAME "ESP_01_AP"
#define PASSWORD "test12586"

IPAddress staticIP(192,168,1,15);        //IP configuration for AP
IPAddress gateway(192,168,1,22);
IPAddress subnet(255,255,255,0);

IPAddress stationStaticIP(192,168,1,22); //IP and port configuration data from STATION (CLIENT)
unsigned int stationRemotePort = 4210;

WiFiUDP Udp;
unsigned int localUdpPort = 4281;        //arbitrary values for port and array size
char receivePacket;                   
char  transmitPacket; 

void setup() {

  WiFi.mode(WIFI_AP);
  
  Serial.begin(115200);                  //starting serial communication, baudrate 115200 (ESP default)
  boolean result, configChange;
  
  while(1){                                              //setting AP
    result = WiFi.softAP(NAME, PASSWORD);
    if(result)
    {
      configChange = WiFi.softAPConfig(staticIP, gateway, subnet);
      if(configChange)
      {
        break;
      }
    }

  }

  while(WiFi.softAPgetStationNum() != 1)         //waiting for station (client) to connect
  {
    delay(500);
  }

  char c='2';
  Serial.print(c);
  
  Udp.begin(localUdpPort);

}

void loop() {

  int packetSize = Udp.parsePacket();             //receiving incoming UDP packets
  if (packetSize)
  {
    receivePacket = Udp.read();
    Serial.print(receivePacket);
    
  }
  
  if (ReceiveByte()) 
  {
    Udp.beginPacket(stationStaticIP, stationRemotePort);
    Udp.write(transmitPacket);
    Udp.endPacket();
   
  }

}

int ReceiveByte(void){
  int received=0;

  if(Serial.available() > 0)
  {
    transmitPacket = Serial.read();
    received = 1;
  }
  
  
  return received;
  
}

