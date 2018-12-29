#ifndef _SAMPQUERY_H_
#define _SAMPQUERY_H_

#include <string>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

// Values returned by Get* functions
#define SAMP_QUERY_SUCCESS  (0)
#define SAMP_QUERY_FAILED   (1)
#define SAMP_INVALID_SOCKET (2)

class SampQuery
{
private:
	struct PlayersStruct
	{
		std::string name;
		int score;
	};

	struct RulesStruct
	{
		std::string name;
		std::string value;
	};

	void SendPacket(char opcode);

	struct sockaddr_in samp_server;
	SOCKET samp_socket;

public:
	SampQuery(const std::string ip, const short port, const int timeout);
	~SampQuery();

	struct ServerInformation
	{
		unsigned char is_locked;
		unsigned short total_players;
		unsigned short max_players;
		std::string hostname;
		std::string gamemode;
		std::string language;
	};

	std::vector<PlayersStruct> ServerPlayers;
	std::vector<RulesStruct> ServerRules;

	unsigned char GetInformation(ServerInformation *info);
	unsigned char GetPlayersInfo();
	unsigned char GetServerRules();
};

#endif
