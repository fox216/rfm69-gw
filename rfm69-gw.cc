/************************************************************************** 
|PC| <-serial-> |Moteino_Gw| <-RFM69W-> |Target_Moteino|

NOTE: Endian Conversion Required to properly read encoded data
https://docs.python.org/2/library/struct.html
Linux = Little Endian (Python conversion table)
Moteino =  Big endian
Data Type Cross Reference Table
--------------------------------
Type	Linux(python)	Moteino
byte 	char(1)			byte(1)
int 	short(2)		int(2)
long 	long(4) 		long(4)
float 	float(4)		float(4)

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

}

byte ackCount=0;
byte inputLen=0;
//char input[64];
byte buff[MAX_SERIAL_SIZE];
void loop() {
	
	// READ Serial input if avaiable...
	if (Serial.available() > 0) {
		//Wait for serial buffer to fill
		delay(100);
		// Read serial data into buffer
		// METHOD 1 Blind read, no limit (Risky?)
		int count=0;

		// read until the serial buffer is empty
		while (Serial.available() > 0) {
			buff[count] = (byte)Serial.read();
			count++;
		}

		Serial.print("Count = ");
		Serial.println(count);
	 // End read data from serial 
	// read Serial Message
	sMsg = *(SerialMsg*)buff;

	if (sMsg.SerialDelimiter == 0) {
		// Valid Message
		Serial.print("NodeID = ");
		Serial.println(sMsg.NodeID);

		Serial.print("Message Size = ");
		Serial.println(sMsg.SerialPayloadSize);
		// Load Message
		
		/*
			Test Message
			'\x00\x00\x0a\x04\x20\xf0\x14\xae\x61\x42\x2a\x00\x00\x00'
			f1 = 56.42
			li = 42
		*/		
		// Get Payload from Serial Payload
		payload = *(Payload*)sMsg.SerialPayload;
		Serial.print("Message ID = ");
		Serial.println(payload.MsgID);

		Serial.print("Message Type = ");
		Serial.println(payload.MsgType);

		Serial.print("LED Number = ");
		Serial.println(sMsg.SerialPayload[2]);

		Serial.print("LED State = ");
		Serial.println(sMsg.SerialPayload[3]);

		/*
			Turn on Light # 7
			\x00\x2a\x04\x05\x0a\x07\x01

			Turn off Light # 7
			\x00\x2a\x04\x05\x0a\x07\x00
		*/
		//memcpy(o_payload.msg, &sMsg.SerialPayload, sizeof(sMsg.SerialPayloadSize));
		radio.sendWithRetry(sMsg.NodeID, (const void*)(&sMsg.SerialPayload), sMsg.SerialPayloadSize);

	} else {
		// !!!!!! Invalid message
		Serial.println("DEBUG Invalid Message Discard!");
		// Print debug info about message
		Serial.print("[DEBUG]Serial Delimiter = ");
		Serial.println(sMsg.SerialDelimiter);

		Serial.print("[DEBUG]NodeID = ");
		Serial.println(sMsg.NodeID);

		Serial.print("[DEBUG]Message Size = ");
		Serial.println(sMsg.SerialPayloadSize);
	}	
		Blink(LED, 10);
	}
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
