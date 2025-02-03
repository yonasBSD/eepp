
#include <iostream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <ctime>

#include <nlohmann/json.hpp>

#if defined(__unix__) || defined(_APPLE__)
	#include <sys/socket.h>
	#include <sys/un.h>
#endif

struct DiscordIPCActivity {
	std::string state = "";
	std::string details = "";
	time_t start = NULL;
	time_t stop = NULL;
	std::string largeImage = "";
	std::string largeText = "";
	std::string smallImage = "";
	std::string smallText = "";
};

enum DiscordIPCOpcodes {
	Handshake = 0,
	Frame,
	Close,
	Ping,
	Pong
};

class DiscordIPC {
	public:
	
		virtual ~DiscordIPC();
		DiscordIPC();

		// false - FileNotFound/OSNotSupported  
		// true  - Success
		bool tryConnect();
		
		void setActivity( DiscordIPCActivity a );
		void clearActivity();
		
		
		
	protected:
		std::string mIpcPath;
		int mPID;
		
		//Configurables
		std::string mcClientID;
		
		#if defined(__unix__) || defined(_APPLE__)
			int mSocket;
		#endif		
		
		void doHandshake();
		
		void reconnect();
		
		void sendPacket( DiscordIPCOpcodes opcode, nlohmann::json j );
};

