#include "bus.hpp"
#include "config.hpp"
#include <eepp/network/tcpsocket.hpp>

using namespace EE::Network;

namespace ecode {

class BusSocket : public Bus {
  public:
	BusSocket( const Connection& connection );

	virtual ~BusSocket();

	bool start() override;

	bool close() override;

	void startAsyncRead( ReadFn readFn ) override;

	size_t write( const char* buffer, const size_t& size ) override;

	bool hasProcess() override { return false; }

  protected:
	Connection mConnection;
	TcpSocket mSocket;
};

} // namespace ecode
