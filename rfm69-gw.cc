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
byte buff[MAX_MESSAGE_SIZE];
byte frameBuff[FRAME_BUFFER_SIZE];
void loop() {
	
	// READ Serial input if avaiable...
	if (Serial.available() > 3) {
		//Wait for serial buffer to fill
		delay(1200);
		// Read serial data into buffer
		// METHOD 1 Blind read, no limit (Risky?)
		int count=0;
		//int frameCount=0;

		for (int x = 0; x<FRAME_BUFFER_SIZE; x++) { //Read first three 
			frameBuff[x] = (byte)Serial.read();
		}
		sFrame = *(SerialFrame*)frameBuff;
		Serial.print("FrameValidation = ");
		Serial.println(sFrame.fHeader, HEX);
		Serial.print("FrameSize = ");
		Serial.println(sFrame.size, DEC);
	

		//while (Serial.available() > 0) {
		for (int y = 0; y < (int)sFrame.size; y++) {
			buff[y] = (byte)Serial.read();
			Serial.print("x");

			/*
			if (count >= MAX_MESSAGE_SIZE || (char)buff[count] == '\n') {
				// Break on delimiter or limit
				Serial.println("Max or Delimiter Reached!");
				break;
			}
			count++;
			*/
		}
		Serial.println();
		//Serial.flush();
		// METHOD 2 Read until new line
		//Serial.readBytesUntil(10, buff, MAX_PAYLOAD_SIZE);
		// Interpret serial data as gateway msg
		gwMsg = *(MoteinoMsg*)buff;
		Blink(LED, 20);
		Serial.print("NodeID = ");
		Serial.println(gwMsg.NodeID, HEX);
		Serial.print("MsgID = ");
		Serial.println(gwMsg.MsgID, HEX);
	}



}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
