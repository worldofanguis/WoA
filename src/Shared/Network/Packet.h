/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 */


/* Class: Packet
 * Description: This class is a holder for the info sent over the network
 */


/*          PACKET STRUCT 
 *	BYTE	-	Packet size		) Msg Header
 *	BYTE	-	Msg type		/
 *	...		-	Msg data		) Msg Body
 */

/* TODO: Rethink the packet types!!! */

/*			PACKET TYPES
 *	MSG_MOVE_START [BYTE]				- Data: [Direction]		- Start moving in direction
 *	MSG_MOVE_STOP						-						- Stop moving
 *	MSG_MOVE_HEARTHBEAT [INT][INT]		- Data: [X][Y]			- Move hearthbeat
 *	MSG_JUMP							-						- Jump
 *	MSG_FIRE_START [BYTE]				- Data: [WeaponID]		- Start fireing
 *	MSG_FIRE_STOP						-						- Stop fireing
 *	MSG_FIRE_HEARTHBEAT [FLOAT]			- Data: [Angle]			- Fire hearthbeat
 */

#pragma once
#include "Common.h"

class Packet
{
public:
	enum TYPES {MSG_MOVE_START,MSG_MOVE_STOP,MSG_MOVE_HEARTHBEAT,
				MSG_JUMP,
				MSG_FIRE_START,MSG_FIRE_STOP,MSG_FIRE_HEARTHBEAT};
	
	Packet();
	~Packet();
	/* Constructor - call Create function */
	Packet(TYPES Type,char* Data,BYTE Size) {Create(Type,Data,Size);}
	/* Copy Constructor */
	Packet(const Packet&);
	
	/* Overloaded operator * - return the data buffer */
	char* operator* () {return _buffer;}
	/* Overloaded operator << - adds a BYTE to the packet */
	Packet& operator<< (BYTE);
	/* Overloaded operator << - adds a float to the packet */
	Packet& operator<< (float);
	/* Overloaded operator << - adds an int to the packet */	
	Packet& operator<< (int Data);

	/* Returns with the size of the msg */
	unsigned int GetMsgSize() {return _size;}
	/* Returns with the type of the msg */
	TYPES GetMsgType() {return (TYPES)_buffer[1];}
	/* Return with the msg data */
	char* GetMsgData() {return _buffer+2;}
	/* Creates a packet */
	void Create(TYPES Type,char* Data,BYTE Size);

private:
	char* _buffer;
	BYTE _size;
};
