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
 
 
 #pragma comment(lib,"ws2_32.lib")
 #include "Network.h"
 

 #define WORKBUFFERSIZE 512				// The size of the buffer which'll hold the not processed packets //
 
Network::Network()
{
	WSADATA wsaData;					// Initialize the windows sockets //
	WSAStartup(MAKEWORD(2,2),&wsaData);
	
	FD_ZERO(&_base);
	_tv.tv_sec = 0;
	_tv.tv_usec = 250;					// We'll wait 250 usec witch each select call (do decide if there is any data to recieve) //

	_socket = NULL;
	_workbufferoffset = 0;
	_connected = false;
	_workbuffer = new char[WORKBUFFERSIZE];
}

Network::~Network()
{
	delete[] _workbuffer;
	Disconnect();
	WSACleanup();
}

bool Network::Connect(char* IP,int Port)
{
	Disconnect();				// Disconnect if we're connected //
	_workbufferoffset = 0;		// Remove any data from the buffer //
	SOCKADDR_IN	SocketAddrIn;
	if((_socket = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
		return false;
	SocketAddrIn.sin_family = AF_INET;
	SocketAddrIn.sin_addr.s_addr = inet_addr(IP);
	SocketAddrIn.sin_port = htons(Port);
	if(connect(_socket,(SOCKADDR*)&SocketAddrIn,sizeof(SocketAddrIn)) == SOCKET_ERROR)
		{
		closesocket(_socket);
		return false;
		}

	FD_SET(_socket,&_base);		// Register the socket for the select call //
	_connected = true;
return true;
}

void Network::Disconnect()
{
	if(_connected)
		{
		FD_CLR(_socket,&_base);		// Remove the socket reference //
		closesocket(_socket);
		_socket = NULL;
		_connected = false;
		}
}
	
void Network::Send(Packet* packet)
{
	if(!_connected)
		return;
	send(_socket,**packet,packet->GetMsgSize(),0);
}

BOOL Network::PeekMessages()
{
	if(!_connected)
		return 0;

		
	_readtest = _base;
	if(select(_socket,&_readtest,NULL,NULL,&_tv) == SOCKET_ERROR)		// Check if there is any event //
			{						// If the remote hung-up disconnect //
			Disconnect();
			return -1;
			}

	if(FD_ISSET(_socket,&_readtest))			// Check if there is data to recieve //
		{
		_recieved = recv(_socket,_workbuffer+_workbufferoffset,WORKBUFFERSIZE-_workbufferoffset,0);
		if(_recieved == SOCKET_ERROR || _recieved == 0)
			{						// If something goes wrong (ex.: remote disconnects)
			Disconnect();			// Close the connection //
			return -1;
			}
		_workbufferoffset += _recieved;
		}

	if(_workbufferoffset > 0)		// If we have data to work with //
		{					// First BYTE in the packet is the size //
		if(_workbufferoffset >= _workbuffer[0])
			{
			BYTE size = _workbuffer[0];
			/* TODO: rewrite this in a 'CALLBACK' like system (if requied) */
			_packets.push(new Packet((Packet::TYPES)_workbuffer[1],_workbuffer+2,size));
			memmove(_workbuffer,_workbuffer+ size,_workbufferoffset-size);
			_workbufferoffset -= size;
			}
		}

return !_packets.empty();		// return true if we recieved a whole packet //
}
