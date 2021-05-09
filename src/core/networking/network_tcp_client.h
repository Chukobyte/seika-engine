#ifndef NETWORK_TCP_CLIENT_H
#define NETWORK_TCP_CLIENT_H

#include "network_common.h"

class NetworkTCPClient {
  private:
    asio::ip::tcp::socket socket;
  public:
    NetworkTCPClient(asio::io_context &context, const std::string ipAddress, int port);
};


#endif //NETWORK_TCP_CLIENT_H
