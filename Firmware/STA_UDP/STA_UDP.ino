#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define NAME "ESP_01_AP"
#define PASSWORD "test12586"
#define PACKET_SIZE 100
#define STOP_SIGN '}'

IPAddress staticIP(192,168,1,22);   //IP configuration for STATION (CLIENT)
IPAddress gateway(192,168,1,15);
IPAddress subnet(255,255,255,0);

IPAddress apStaticIP(192,168,1,15); //IP and port configuration data from AP
unsigned int apRemotePort = 4281;

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  //arbitrary values
char receivePacket[PACKET_SIZE];           
char  transmitPacket[PACKET_SIZE];
         
void setup() {

  WiFi.mode(WIFI_STA);
  
  Serial.begin(115200);

  WiFi.begin(NAME, PASSWORD);
  boolean configChange = WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED && !configChange);

  char c = '2';
  Serial.print(c);

  Udp.begin(localUdpPort);

}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    int len = Udp.read(receivePacket, PACKET_SIZE);
    if (len > 0)
    {
      receivePacket[len] = 0;
    }
    Serial.print(receivePacket);
    memset(receivePacket, 0, sizeof(receivePacket));                //resetting receive buffer
    
  }
    
  if (receiveUntilStopSign() >= 1) {
    Udp.beginPacket(apStaticIP, apRemotePort);
    Udp.write(transmitPacket);
    Udp.endPacket();
    memset(transmitPacket, 0, sizeof(transmitPacket));             //resetting transmit values
   
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
