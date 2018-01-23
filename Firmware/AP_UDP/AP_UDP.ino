#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define NAME "ESP_01_AP"
#define PASSWORD "test12586"
#define PACKET_SIZE 100
#define STOP_SIGN '}'

IPAddress staticIP(192,168,1,15);        //IP configuration for AP
IPAddress gateway(192,168,1,22);
IPAddress subnet(255,255,255,0);

IPAddress stationStaticIP(192,168,1,22); //IP and port configuration data from STATION (CLIENT)
unsigned int stationRemotePort = 4210;

WiFiUDP Udp;
unsigned int localUdpPort = 4281;        //arbitrary values for port and array size
char receivePacket[PACKET_SIZE];                   
char  transmitPacket[PACKET_SIZE]; 

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
    int len = Udp.read(receivePacket, PACKET_SIZE);
    if (len > 0)
    {
      receivePacket[len] = 0;
    }
    Serial.print(receivePacket);
    memset(receivePacket, 0, sizeof(receivePacket));     //resetting receive buffer
    
  }
  
  if (receiveUntilStopSign() >= 1) 
  {
    Udp.beginPacket(stationStaticIP, stationRemotePort);
    Udp.write(transmitPacket);
    Udp.endPacket();
    memset(transmitPacket, 0, sizeof(transmitPacket));  //resetting transmit values
   
  }

}

int receiveUntilStopSign(){
  char receivedByte;
  int position = 0;
  int numOfReceivedBytes = 0;
  
  while(Serial.available() > 0)
  {
    receivedByte = Serial.read();

    if(receivedByte != STOP_SIGN)
    {
     transmitPacket[position++] = receivedByte;
     numOfReceivedBytes++;

     if(position >= PACKET_SIZE)
     {
      position = 0;
     }
    }
    else 
    {
      transmitPacket[position] = '\0';
      return numOfReceivedBytes;
    }
  }
  return 0;
  
}

