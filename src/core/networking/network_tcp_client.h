#ifndef NETWORK_TCP_CLIENT_H
#define NETWORK_TCP_CLIENT_H

#include "network_connection.h"

class NetworkTCPClient {
  private:
    TCPConnection *connection = nullptr;
    asio::ip::tcp::socket socket;
  public:
    NetworkTCPClient(asio::io_context &context, const std::string ipAddress, int port);

    ~NetworkTCPClient() {
        Disconnect();
    }

    void Connect() {
        if (!connection) {
            connection = new TCPConnection();
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
