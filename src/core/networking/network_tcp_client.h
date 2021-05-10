#ifndef NETWORK_TCP_CLIENT_H
#define NETWORK_TCP_CLIENT_H

#include "network_connection.h"
#include "network_connection_context.h"

class NetworkTCPClient {
  private:
    NetworkConnectionContext *networkConnectionContext = nullptr;
    asio::io_context &context;
    TCPConnection *connection = nullptr;
    asio::ip::tcp::socket socket;
    NetworkQueue<NetworkMessage> networkQueue;
    const std::string &ipAddress;
    const int port;
    Logger *logger = nullptr;
  public:
    NetworkTCPClient(asio::io_context &context, const std::string &ipAddress, int port);

    ~NetworkTCPClient();

    void Connect();

    void Disconnect();

    void ProcessMessageQueue();
};


#endif //NETWORK_TCP_CLIENT_H
