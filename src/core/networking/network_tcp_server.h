#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <vector>

#include "network_common.h"
#include "../utils/logger.h"

class TCPConnection {
  private:
    asio::ip::tcp::socket socket;
  public:
    TCPConnection(asio::io_context &context) : socket(context) {}

    asio::ip::tcp::socket& GetSocket() {
        return socket;
    }

    void HandleWrite(const asio::error_code& errorCode) {

    }

    static TCPConnection* Create(asio::io_context &context) {
        return new TCPConnection(context);
    }

    void Start() {}
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

    void AcceptConnections();

    void HandleAccept(const asio::error_code& errorCode);

};

#endif //NETWORK_TCP_SERVER_H
