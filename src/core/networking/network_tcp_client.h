#ifndef NETWORK_TCP_CLIENT_H
#define NETWORK_TCP_CLIENT_H

#include "network_connection.h"

class NetworkTCPClient {
  private:
    asio::io_context &context;
    TCPConnection *connection = nullptr;
    asio::ip::tcp::socket socket;
  public:
    NetworkTCPClient(asio::io_context &context, const std::string &ipAddress, int port) : context(context), socket(context) {}

    ~NetworkTCPClient() {
        Disconnect();
    }

    void Connect() {
        if (!connection) {
            connection = new TCPConnection(context, 1);
        }
    }

    void Disconnect() {
        if (connection) {
            delete connection;
            connection = nullptr;
        }
    }
};


#endif //NETWORK_TCP_CLIENT_H
