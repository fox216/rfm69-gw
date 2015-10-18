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
  //char buff[50]; // Write to serial buffer 
  //sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  //DEBUGln(buff);
}

byte ackCount=0;
byte inputLen=0;
//char input[64];
byte buff[MAX_SERIAL_SIZE];
byte frameBuff[FRAME_BUFFER_SIZE];
byte nBuff[MAX_NETWORK_SIZE];
void loop() {
	
	// READ Serial input if avaiable...
	if (Serial.available() > 0) {
		//Wait for serial buffer to fill
		delay(1200);
		// Read serial data into buffer
		// METHOD 1 Blind read, no limit (Risky?)
		int count=0;
		//int frameCount=0;
		// Read header - determine if packet is valid, get sise of message
		/*
		for (int x = 0; x<FRAME_BUFFER_SIZE; x++) { //Read first three 
			frameBuff[x] = (byte)Serial.read();
		}
		*/

		// read until the serial buffer is empty
		while (Serial.available() > 0) {
			buff[count] = (byte)Serial.read();
			count++;
		}



		Serial.print("Count = ");
		Serial.println(count);
	 // End read data from serial 

	// read SerialFrame
	for (int b =0; b < FRAME_BUFFER_SIZE; b++) {
		frameBuff[b] = buff[b];
	}
	sFrame = *(SerialFrame*)frameBuff;

	if (sFrame.fDelimiter == 0) {
		// Valid Message
		Serial.print("NodeID = ");
		Serial.println(sFrame.NodeID);

		Serial.print("Message ID = ");
		Serial.println(sFrame.MsgID);

		Serial.print("Message Type = ");
		Serial.println(sFrame.MsgType);

		Serial.print("Message Size = ");
		Serial.println(sFrame.MsgSize);
		// Load Message
		int nCount = 0;
		for (int m = FRAME_BUFFER_SIZE; m < FRAME_BUFFER_SIZE + sFrame.MsgSize; m++) {
			nBuff[nCount] = buff[m];
			nCount++;
		}
		/*
			Test Message
			'\x00\x00\x04\x20\x0a\xf0\x14\xae\x61\x42\x2a\x00\x00\x00'
			f1 = 56.42
			li = 42
		*/		
		Serial.print("!! nCount = ");
		Serial.println(nCount);
	} else {
		// Invalid message
		Serial.println("DEBUG Invalid Message Discard!");
		
		Serial.print("Frame Delimiter = ");
		Serial.print(sFrame.fDelimiter);

		Serial.print("NodeID = ");
		Serial.print(sFrame.NodeID);

		Serial.print("Message ID = ");
		Serial.println(sFrame.MsgID);

		Serial.print("Message Type = ");
		Serial.println(sFrame.MsgType);

		Serial.print("Message Size = ");
		Serial.print(sFrame.MsgSize);
	}	

	if (sFrame.NodeID == 0) {
		Serial.println("Echo Request to Serial Gateway!!");
		tMsg = *(TestMsg*)nBuff;

		Serial.print("Test Size = ");
		Serial.println(tMsg.size);

		Serial.print("Test f1 = ");
		Serial.println(tMsg.f1);

		Serial.print("Test l1 = ");
		Serial.println(tMsg.l1);

	}

	/*
		sFrame = *(SerialFrame*)buff;
		
		Serial.print("FrameValidation = ");
		Serial.println(sFrame.fHeader);
		
		Serial.print("FrameSize = ");
		Serial.println(sFrame.size);
		
		Serial.print("Float = ");
		Serial.println(sFrame.f1);
		
		Serial.print("Long = ");
		Serial.println(sFrame.l1);
	*/
		Blink(LED, 20);
	}
		//delay(2000);
		/*
		//while (Serial.available() > 0) {
		for (int y = 0; y < (int)sFrame.size; y++) {
			buff[y] = (byte)Serial.read();
			Serial.print("x");

			
			if (count >= MAX_MESSAGE_SIZE || (char)buff[count] == '\n') {
				// Break on delimiter or limit
				Serial.println("Max or Delimiter Reached!");
				break;
			}
			count++;
			
		}
		Serial.println();
		//Serial.flush();
		// METHOD 2 Read until new line
		//Serial.readBytesUntil(10, buff, MAX_PAYLOAD_SIZE);
		// Interpret serial data as gateway msg
		gwMsg = *(MoteinoMsg*)buff;
		
		Serial.print("NodeID = ");
		Serial.println(gwMsg.NodeID, HEX);
		Serial.print("MsgID = ");
		Serial.println(gwMsg.MsgID, HEX);
		*/
	



}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
