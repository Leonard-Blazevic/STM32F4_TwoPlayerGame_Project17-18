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

