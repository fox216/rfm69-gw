/*********** GATEWAY MESSAGE STRUCTURE *******************
Gateways structure is a simplified, abstracted, message 
type used to relay messages between host computer and 
wireless sensor network. 

Gateway message format 
HEADER
	- MESSAGE PAYLOAD

Function:
Gateway relays messages by inspecting only the message 
header. Payload forwarded to target node intact...

MOTEINO MESSAGE FORMAT
----------------------------------

MAX_MESSAGE_SIZE = 66
MESSAGE FRAME SIZES
------------------------
PAYLOAD = 1
ADDRESS_BYTE = 1
FROM_ADDRESS = 1
CONTROL_BYTE = 1
NETWORK_ID = 1
MAX_PAYLOAD = 66 - 5 = 61 BYTES!!!
_____________________________________
Moteino References 
https://github.com/LowPowerLab/RFM69
http://lowpowerlab.com/blog/2013/06/20/rfm69-library/#more-917

Developer Notes
1. Payload is not inspected by the gateway. 
2. Header inspected by Gateway, used to route message
3. Target node is responsible for processing payload.
4. ASSUMPTION = AVR(Big Endian) RPI(Little Endian)
5. NodeID + MsgID used together to create unique index for xmit.
*/

#ifndef NodeMsg_h
#define NodeMsg_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif
#define FRAME_BUFFER_SIZE 11
#define MAX_MESSAGE_SIZE 61
#define MAX_PAYLOAD_SIZE 59 // Package size in payload
#define WATCHDOG_DEFAULT 10000 // 10 seconds used by node
/*---------------------------------------------
|	!! PKG Types !!
|	Structure written to pkg[] array...
|
*/


// Gateway Message Structure 
typedef struct {		
  byte 				NodeID;
  byte 				MsgID;					
  byte           	Payload[MAX_PAYLOAD_SIZE];  // 61 bytes
} MoteinoMsg;
MoteinoMsg gwMsg;

typedef struct { 
	unsigned int	fHeader; 	// Python short(2)
	byte 			size; 		// Python B (1)
	float			f1;			// Python f (4)
	long 			l1;			// Python l (4)
} SerialFrame;
SerialFrame sFrame;

#endif