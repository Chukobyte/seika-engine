#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <vector>

#include "../utils/logger.h"
#include "network_connection_context.h"

class NetworkTCPServer {
  private:
    NetworkConnectionContext *networkConnectionContext = nullptr;
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
