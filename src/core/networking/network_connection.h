#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "network_common.h"

using NetworkConnectionId = int;

class NetworkConnection {
  protected:
    Logger *logger = nullptr;
    asio::ip::tcp::socket socket;
  public:
    NetworkConnection(asio::io_context &context) : socket(context), logger(Logger::GetInstance()) {}

    bool IsConnected() {
        return socket.is_open();
    }

    asio::ip::tcp::socket& GetSocket() {
        return socket;
    }

    virtual void Start() = 0;
};

class TCPConnection : public NetworkConnection {
  private:
    std::vector<char> networkBuffer;
    const unsigned int NETWORK_BUFFER_SIZE = 20 * 1024;
  public:
    TCPConnection(asio::io_context &context) : NetworkConnection(context) {
        networkBuffer.resize(NETWORK_BUFFER_SIZE);
    }

    void SendNetworkMessage(const std::string &message)  {
        auto handleWriteFunction = [this] (const asio::error_code &errorCode, size_t bytes) {
            logger->Debug("Wrote stuff from connection!");
        };
        asio::async_write(socket, asio::buffer(message), handleWriteFunction);
    }

    void ReadNetworkMessages() {
        auto handleReadFunction = [this] (const asio::error_code &errorCode, size_t bytes) {
            if (IsConnected()) {
                logger->Debug("Reading from connection!");
                std::cout << "[FROM CLIENT] ";
                for (int i = 0; i < bytes; i++) {
                    std::cout << networkBuffer[i];
                }
                std::cout << std::endl;
                ReadNetworkMessages();
            } else {
                logger->Warn("Connection closed!");
            }
        };
        socket.async_read_some(asio::buffer(networkBuffer.data(), networkBuffer.size()), handleReadFunction);

    }

    void Start() override {
        SendNetworkMessage("[FROM SERVER] Hello from server!\n");
        ReadNetworkMessages();
    }
};

#endif //NETWORK_CONNECTION_H
