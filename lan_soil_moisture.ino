/* Rainer Hoppe, https://test-wetterstation.de */


#include <EtherCard.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)
#if STATIC
// ethernet interface ip address - eigene statische IP-Adresse
// über diese kann mit dem Browser die Daten abgerufen werden

static byte myip[] = { 192, 168, 0, 132 };
// gateway ip address
static byte gwip[] = { 192, 168, 0, 1 };

#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

int iLauf = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("\n[backSoon]");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0)
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);


}

void loop() {
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) 
  {

    int iSoil_moisture=0; 
    float fSoil_moisture=0;
    iLauf ++; 
 
    String page = "";
    page += "HTTP/1.0 200 OK\r\n";
    page += "Content-Type: text/html\r\n";
    page += "\r\n";
    page += "<html>";
    page += "<head><title>Soil Moisture Sensors</title></head>";
    page += "<body>";
    page += "<h1>Soil Moisture Sensor - retrieval: " + String(iLauf)  +"</h1>";


    // Soil moisture Sensor 1 on Pin 0, 5V
    iSoil_moisture = analogRead(A0);
    fSoil_moisture = float(iSoil_moisture)/1023.0*5;
    page += "<span>Pin 0: " + String(fSoil_moisture, 1) + "V, Soil moisture: " + String(iSoil_moisture) + "</span><br/>";

    // Soil moisture Sensor 2 on Pin 1, 5V
    iSoil_moisture = analogRead(A1);
    fSoil_moisture = float(iSoil_moisture)/1023.0*5;
    page += "<span>Pin 1: " + String(fSoil_moisture, 1) + "V, Soil moisture: " + String(iSoil_moisture) + "</span><br/>";

    // Soil moisture Sensor 3 on Pin 2, 3.3V
    iSoil_moisture = analogRead(A2);
    fSoil_moisture = float(iSoil_moisture)/1023.0*3.3;
    page += "<span>Pin 2: " + String(fSoil_moisture, 1) + "V, Soil moisture: " + String(iSoil_moisture) + "</span><br/>";


    page += "</body></html>";
    int lengthOfContent = 300;
    char pageCopy[lengthOfContent];
    page.toCharArray(pageCopy, lengthOfContent);
    memcpy(ether.tcpOffset(), pageCopy, lengthOfContent);
    ether.httpServerReply(lengthOfContent);
  }
}
