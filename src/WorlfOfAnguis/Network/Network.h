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
 
 
#pragma once
#include "Common.h"
#include "Network\Packet.h"

class Network
{
public:
	/* Std Constructor - Initializes WindowSockets */
	Network();
	/* Std Destructor - Deinizializes WindowSockets */
	~Network();
	/* Connects to the IP on the Port */
	bool Connect(char* IP,int Port);
	/* Return <true> if connected */
	bool IsConnected() {return _connected;}
	/* Disconnects from the IP */
	void Disconnect();
	
	/* Send a <packet> - see packets.h */
	void Send(Packet* packet);
	/* Returns with the next <packet> */
	Packet* GetPacket() {return _packets.front();}
	/* Deletes the current packet (which was returned with GetPacket()) */
	void Delete() {delete _packets.front(); _packets.pop();}
	/* Checks for new packets - return  0 if no packets
	 *							return  1 if there are new packets
	 *							return -1 if the connection is closed
	 */
	BOOL PeekMessages();
private:
	std::queue<Packet*> _packets;
	bool _connected;
	
	SOCKET _socket;
	timeval _tv;
	fd_set _base;
	fd_set _readtest;
	char *_workbuffer;
	unsigned int _workbufferoffset;
	int _recieved;
};
