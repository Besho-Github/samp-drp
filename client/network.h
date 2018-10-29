#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "dllmain.h"

#define DEFAULT_APPLICATION_ID "415624739151806464"

typedef Packet*(__fastcall* ReceivePacket_t)(RakClientInterface*, void*);

namespace Network
{
	enum incoming_packets
	{
		ID_CONNECTION_ACCEPTED = 34,
		ID_INITIALIZE = 248,
		ID_SET_DETAILS = 249,
		ID_SET_STATE = 250,
		ID_SET_LARGE_IMAGE = 251,
		ID_SET_LARGE_IMAGE_TEXT = 252,
		ID_SET_SMALL_IMAGE = 253,
		ID_SET_SMALL_IMAGE_TEXT = 254
	};

	enum outgoing_packets
	{
		ID_DISCORD_USER = 253
	};

	extern std::string application_id;
	extern std::string details;
	extern std::string state;
	extern std::string large_image;
	extern std::string large_image_text;
	extern std::string small_image;
	extern std::string small_image_text;

	extern DWORD connect_tick;
	extern BOOL connect_to_server;
	extern bool drp_initialized;
	extern ReceivePacket_t ReceivePacket;

	Packet* __fastcall PacketReceived(RakClientInterface* RakClient, void* EDX);
}

#endif 