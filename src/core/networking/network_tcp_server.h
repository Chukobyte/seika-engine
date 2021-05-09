#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <vector>

#include "network_common.h"
#include "../utils/logger.h"

class TCPConnection {
  public:

};

class NetworkTCPServer {
  private:
//    asio::ip::tcp::endpoint endpoint;
//    asio::ip::tcp::acceptor acceptor;
//    asio::ip::tcp::socket socket;

    asio::io_context &context;
    asio::ip::tcp::acceptor acceptor;
    int port;
    static std::vector<char> networkBuffer;

    Logger *logger = nullptr;
  public:
    NetworkTCPServer(asio::io_context &context, int port);
    void Start();
};

#endif //NETWORK_TCP_SERVER_H
