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


#include "Packet.h"

Packet::Packet()
{
	_size = 0;
	_buffer = new char[15];		// Allocate a 15-BYTE buffer (this should handle the biggest messages too) //
}

Packet::Packet(const Packet& packet)
{
	_size = packet._size;
	_buffer = new char[_size];
	memcpy(_buffer,packet._buffer,_size);
}

Packet::~Packet()
{
	delete _buffer;
}

void Packet::Create(TYPES Type,char* Data,BYTE Size)
{
	_size = Size+ 2;
	_buffer[0] = _size;
	_buffer[1] = (char)Type;
	memcpy(_buffer+2,Data,Size-2);
}

Packet& Packet::operator<< (BYTE Data)
{
	_buffer[_size++] = Data;
return *this;
}

Packet& Packet::operator<< (float Data)
{
	memcpy(_buffer+_size,&Data,4);
	_size+=4;
return *this;
}

Packet& Packet::operator<< (int Data)
{
	memcpy(_buffer+_size,&Data,4);
	_size+=4;
return *this;
}
