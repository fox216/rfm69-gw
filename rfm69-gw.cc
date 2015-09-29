/************************************************************************** 
|PC| <-serial-> |Moteino_Gw| <-RFM69W-> |Target_Moteino|


***************************************************************************/


#include <RFM69.h>
#include <SPI.h>
#include <NodeGwMsg.h> // Load Gateway Message structure
#include <NodeConf.h>
// Initialize Redio
RFM69 radio;
// BEGIN Function Prototypes
void Blink(byte PIN, int DELAY_MS);
void txSetZone(byte zoneNum);
void txGetZoneStatus();
void rxZoneStatus();
// END Function Prototypes
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(10);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.encrypt(KEY);
  //char buff[50]; // Write to serial buffer 
  //sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  //DEBUGln(buff);
}

byte ackCount=0;
byte inputLen=0;
//char input[64];
byte buff[MAX_PAYLOAD_SIZE];

void loop() {
	
	// READ Serial input if avaiable...
	if (Serial.available() > 0) {
		// Read serial data into buffer
		// METHOD 1 Blind read, no limit (Risky?)
		
		while (Serial.available() > 0) {
			byte buff = (byte)Serial.read();
		}
		
		// METHOD 2 Read until new line
		//Serial.readBytesUntil(10, buff, MAX_PAYLOAD_SIZE);
		// Interpret serial data as gateway msg
		gwMsg = *(MoteinoMsg*)buff;
		Blink(LED, 20);
		Serial.print("NodeID = ");
		Serial.println(gwMsg.NodeID);
		Serial.print("MsgID = ");
		Serial.println(gwMsg.MsgID);
	}



}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
