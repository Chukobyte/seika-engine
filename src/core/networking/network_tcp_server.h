#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <vector>

#include "network_connection.h"
#include "network_context.h"
#include "../utils/logger.h"

class NetworkTCPServer {
  private:
    NetworkContext *networkContext = nullptr;
    asio::io_context &context;
    asio::ip::tcp::acceptor acceptor;
    int port;
    NetworkQueue<NetworkMessage> networkQueue;
    std::thread threadContext;
    Logger *logger = nullptr;
  public:
    NetworkTCPServer(asio::io_context &context, int port);

    void Start();

    void AcceptConnections();

    void Stop();

    void ProcessMessageQueue();

};

#endif //NETWORK_TCP_SERVER_H
