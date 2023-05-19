#pragma once
//Using this for game persistence stats such as a username that dosen't need to be changed each game
//Based on the example code provided by ShadowMultiplayer
class ConnectionDetails
{
public:
	static void StaticInit();
	static std::unique_ptr<ConnectionDetails> sInstance;


	ConnectionDetails();
	void Load();
	string GetClientName();
	string GetClientDestination();
	uint16_t GetServerPort();

private:
	string m_clientName;
	string m_clientIP;
	uint16_t m_clientPort;
	uint16_t m_serverPort;

};

