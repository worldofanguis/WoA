/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 *	Network packet header file
 */

/*          PACKET STRUCT 
 *	BYTE	-	Packet size		) Msg Header
 *	BYTE	-	Msg type		/
 *	...		-	Msg data		) Msg Body
 */

/*			PACKET TYPES
 *	MSG_MOVE_START [BYTE]				- Data: [Direction]		- Start moving in direction
 *	MSG_MOVE_STOP						-						- Stop moving
 *	MSG_MOVE_HEARTHBEAT [FLOAT][FLOAT]	- Data: [X][Y]			- Move hearthbeat
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
	
	/* Std Constructor - Creates a packet with a buffer sized 15 */
	Packet();
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

	/* Std Destructor */
	~Packet();

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
