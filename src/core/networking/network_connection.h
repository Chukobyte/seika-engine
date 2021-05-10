#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "network_common.h"
#include "network_queue.h"

using NetworkConnectionId = int;

class NetworkConnection {
  protected:
    Logger *logger = nullptr;
    asio::ip::tcp::socket socket;
    NetworkConnectionId id;
    NetworkQueue<NetworkMessage> &networkQueue;
  public:
    explicit NetworkConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionId connectionId) : socket(context), networkQueue(networkQueue), id(connectionId), logger(Logger::GetInstance()) {}

    bool IsConnected() {
        return socket.is_open();
    }

    asio::ip::tcp::socket& GetSocket() {
        return socket;
    }

    void Disconnect() {
        socket.close();
    }

    int GetId() const {
        return id;
    }

    virtual void Start() = 0;
};

class TCPConnection : public NetworkConnection {
  private:
    std::vector<char> networkBuffer;
    const unsigned int NETWORK_BUFFER_SIZE = 20 * 1024;
  public:
    explicit TCPConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionId connectionId) : NetworkConnection(context, networkQueue, connectionId) {
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
                std::string message = "[FROM CLIENT] ";
//                std::cout << "[FROM CLIENT] ";
                for (int i = 0; i < bytes; i++) {
                    message += networkBuffer[i];
//                    std::cout << networkBuffer[i];
                }
                message += "\n";
//                std::cout << std::endl;
                NetworkMessage networkMessage{.message = message};
                networkQueue.PushBack(networkMessage);
                std::cout << "Pushed message to queue:\n" << networkMessage.message << std::endl;
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
