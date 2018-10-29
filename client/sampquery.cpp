#include "sampquery.h"

SampQuery::SampQuery(std::string ip, const short port, const int timeout)
{
	WSAData data;

	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		return;
	}

	this->samp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (this->samp_socket == INVALID_SOCKET)
	{
		WSACleanup();
	}
	else
	{
		setsockopt(this->samp_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), 4);

		this->samp_server.sin_family = AF_INET;

		if (inet_pton(AF_INET, ip.c_str(), &this->samp_server.sin_addr) != 1)
		{
			struct addrinfo hints, *result, *p;
			struct sockaddr_in *h;

			memset(&hints, 0, sizeof(hints));

			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;

			if (!getaddrinfo(ip.c_str(), NULL, &hints, &result))
			{
				for (p = result; p != NULL; p = p->ai_next)
				{
					h = reinterpret_cast<sockaddr_in*>(p->ai_addr);

					this->samp_server.sin_addr = h->sin_addr;
				}

				freeaddrinfo(result);
			}
		}

		this->samp_server.sin_port = htons(port);
	}
}

SampQuery::~SampQuery()
{
	closesocket(this->samp_socket);
	WSACleanup();
}

void SampQuery::SendPacket(char opcode)
{
	std::string packet;

	packet = "SAMP";

	packet += this->samp_server.sin_addr.s_net;
	packet += this->samp_server.sin_addr.s_host;
	packet += this->samp_server.sin_addr.s_lh;
	packet += this->samp_server.sin_addr.s_impno;

	packet += static_cast<unsigned char>(this->samp_server.sin_port & 0xFF);
	packet += static_cast<unsigned char>(this->samp_server.sin_port >> 8 & 0xFF);

	packet += opcode;

	sendto(this->samp_socket, packet.c_str(), 11, 0, reinterpret_cast<sockaddr*>(&this->samp_server), sizeof(sockaddr));
}

unsigned char SampQuery::GetInformation(ServerInformation *info)
{
	if (this->samp_socket == INVALID_SOCKET) return SAMP_INVALID_SOCKET;

	this->SendPacket('i');

	char buffer[512] = { 0 };

	sockaddr from;

	int length = sizeof(sockaddr), receivedbytes = recvfrom(samp_socket, buffer, 512, 0, &from, &length);

	if (receivedbytes > 11)
	{
		char* key = buffer + 11;

		info->is_locked = *reinterpret_cast<unsigned char*>(key);

		key += 1;

		info->total_players = *reinterpret_cast<unsigned short*>(key);

		key += 2;

		info->max_players = *reinterpret_cast<unsigned short*>(key);

		key += 2;

		int hostname_length = *reinterpret_cast<int*>(key);

		key += 4;

		info->hostname = std::string(key, hostname_length);

		key += hostname_length;

		int gamemode_length = *reinterpret_cast<int*>(key);

		key += 4;

		info->gamemode = std::string(key, gamemode_length);

		key += gamemode_length;

		int language_length = *reinterpret_cast<int*>(key);

		key += 4;

		info->language = std::string(key, language_length);
	}
	else
	{
		return SAMP_QUERY_FAILED;
	}
	return SAMP_QUERY_SUCCESS;
}

unsigned char SampQuery::GetPlayersInfo()
{
	if (this->samp_socket == INVALID_SOCKET) return SAMP_INVALID_SOCKET;

	this->SendPacket('c');

	char buffer[512] = { 0 };

	sockaddr from;

	int length = sizeof(sockaddr), receivedbytes = recvfrom(samp_socket, buffer, 512, 0, &from, &length);

	if (receivedbytes > 11)
	{
		ServerPlayers.clear();

		char* key = buffer + 11;
		short player_count;

		unsigned char name_length;

		PlayersStruct players_struct;

		player_count = *reinterpret_cast<unsigned short*>(key);

		key += 2;

		for (unsigned short a = 0; a < player_count; a++)
		{
			name_length = *reinterpret_cast<unsigned char*>(key);

			key += 1;

			players_struct.name = std::string(key, name_length);

			key += name_length;

			players_struct.score = *reinterpret_cast<int*>(key);

			key += 4;

			ServerPlayers.push_back(players_struct);
		}
	}
	else
	{
		return SAMP_QUERY_FAILED;
	}
	return SAMP_QUERY_SUCCESS;
}

unsigned char SampQuery::GetServerRules()
{
	if (this->samp_socket == INVALID_SOCKET) return SAMP_INVALID_SOCKET;

	this->SendPacket('r');

	char buffer[512] = { 0 };

	sockaddr from;

	int length = sizeof(sockaddr), receivedbytes = recvfrom(samp_socket, buffer, 512, 0, &from, &length);

	if (receivedbytes > 11)
	{
		ServerRules.clear();

		char* key = buffer + 11;
		int rule_length, rule_value_length, rule_count = *reinterpret_cast<unsigned short*>(key);

		RulesStruct rules_struct;

		key += 2;

		for (unsigned short a = 0; a < rule_count; a++)
		{
			rule_length = *reinterpret_cast<unsigned char*>(key);

			key += 1;

			rules_struct.name = std::string(key, rule_length);

			key += rule_length;

			rule_value_length = *reinterpret_cast<unsigned char*>(key);

			key += 1;

			rules_struct.value = std::string(key, rule_value_length);

			key += rule_value_length;

			ServerRules.push_back(rules_struct);
		}
	}
	else
	{
		return SAMP_QUERY_FAILED;
	}
	return SAMP_QUERY_SUCCESS;
}