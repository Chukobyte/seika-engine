#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "network_common.h"

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

    void HandleRead(const asio::error_code& errorCode) {

    }

    void Start() {}
};

#endif //NETWORK_CONNECTION_H
