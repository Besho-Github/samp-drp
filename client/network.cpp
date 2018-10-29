#include "network.h"

namespace Network
{
	std::string application_id = DEFAULT_APPLICATION_ID;
	std::string details;
	std::string state;
	std::string large_image;
	std::string large_image_text;
	std::string small_image;
	std::string small_image_text;

	DWORD connect_tick = NULL;
	BOOL connect_to_server = 1;
	bool drp_initialized = false;
	ReceivePacket_t ReceivePacket = NULL;

	Packet* __fastcall PacketReceived(RakClientInterface* RakClient, void* EDX)
	{
		Packet* packet = ReceivePacket(RakClient, EDX);

		if (packet)
		{
			RakNet::BitStream packet_bitstream(packet->data, packet->length, false);
			packet_bitstream.IgnoreBits(8);

			switch (packet->data[0])
			{
				case incoming_packets::ID_CONNECTION_ACCEPTED:
				{
					if (connect_to_server)
					{
						connect_tick = GetTickCount() + 3000; // If the ID_INITIALIZE packet is not sent by the server, DRP will initialize as if connect_to_server was false.

						RakNet::BitStream bs;
						bs.Write(static_cast<uint8_t>(outgoing_packets::ID_DISCORD_USER));
						RakClient->Send(&bs, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
					}
					else
					{
						if (!drp_initialized) // Just in-case the player suffers a timeout. They could reconnect without starting the game again and DRP would already be initialized, so we don't want it to happen again.
						{
							drp_initialized = true;

							Discord_Initialize(application_id.c_str(), NULL, 0, NULL);
						}
					}
					break;
				}
				case incoming_packets::ID_INITIALIZE: // This and the packets below will never be sent to the client if connect_to_server is false
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					application_id.resize(buffer_length);
					packet_bitstream.Read(&application_id[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					details.resize(buffer_length);
					packet_bitstream.Read(&details[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					state.resize(buffer_length);
					packet_bitstream.Read(&state[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					large_image.resize(buffer_length);
					packet_bitstream.Read(&large_image[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					large_image_text.resize(buffer_length);
					packet_bitstream.Read(&large_image_text[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					small_image.resize(buffer_length);
					packet_bitstream.Read(&small_image[0], buffer_length);

					packet_bitstream.Read(buffer_length);
					small_image_text.resize(buffer_length);
					packet_bitstream.Read(&small_image_text[0], buffer_length);

					if (!drp_initialized) // Just in-case the player suffers a timeout. They could reconnect without starting the game again and DRP would already be initialized, so we don't want it to happen again.
					{
						drp_initialized = true;

						Discord_Initialize(application_id.c_str(), NULL, 0, NULL);
					}
					break;
				}
				case incoming_packets::ID_SET_DETAILS:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					details.resize(buffer_length);
					packet_bitstream.Read(&details[0], buffer_length);
					break;
				}
				case incoming_packets::ID_SET_LARGE_IMAGE:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					large_image.resize(buffer_length);
					packet_bitstream.Read(&large_image[0], buffer_length);
					break;
				}
				case incoming_packets::ID_SET_LARGE_IMAGE_TEXT:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					large_image_text.resize(buffer_length);
					packet_bitstream.Read(&large_image_text[0], buffer_length);
					break;
				}
				case incoming_packets::ID_SET_SMALL_IMAGE:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					small_image.resize(buffer_length);
					packet_bitstream.Read(&small_image[0], buffer_length);
					break;
				}
				case incoming_packets::ID_SET_SMALL_IMAGE_TEXT:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					small_image_text.resize(buffer_length);
					packet_bitstream.Read(&small_image_text[0], buffer_length);
					break;
				}
				case incoming_packets::ID_SET_STATE:
				{
					uint8_t buffer_length;

					packet_bitstream.Read(buffer_length);
					state.resize(buffer_length);
					packet_bitstream.Read(&state[0], buffer_length);
					break;
				}
			}
		}
		return packet;
	}
}