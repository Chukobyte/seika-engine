#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "network_common.h"

using NetworkConnectionId = int;

class NetworkConnection {
  protected:
    asio::ip::tcp::socket socket;
    Logger *logger = nullptr;
  public:
    NetworkConnection(asio::io_context &context) : socket(context) {}

    virtual asio::ip::tcp::socket& GetSocket() = 0;

    virtual void SendNetworkMessage(const std::string &message) = 0;

    virtual void ReadNetworkMessages() = 0;

    virtual void Start() = 0;

    virtual bool IsConnected() = 0;
};

class TCPConnection : public NetworkConnection {
  private:
    std::vector<char> networkBuffer;
    const unsigned int NETWORK_BUFFER_SIZE = 20 * 1024;
  public:
    TCPConnection(asio::io_context &context) : NetworkConnection(context) {
        networkBuffer.resize(NETWORK_BUFFER_SIZE);
    }

    asio::ip::tcp::socket& GetSocket() override {
        return socket;
    }

    void SendNetworkMessage(const std::string &message) override {
        auto handleWriteFunction = [this] (const asio::error_code &errorCode, size_t bytes) {
            logger->Debug("Wrote stuff from connection!");
        };
        asio::async_write(socket, asio::buffer(message), handleWriteFunction);
    }

    void ReadNetworkMessages() override {
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
        logger->Debug("NC Start");
        SendNetworkMessage("[FROM SERVER] Hello from server!\n");
        ReadNetworkMessages();
    }

    bool IsConnected() override {
        return socket.is_open();
    }
};

#endif //NETWORK_CONNECTION_H
