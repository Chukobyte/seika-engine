#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include "network_common.h"
#include "network_queue.h"

using NetworkConnectionId = int;

enum class NetworkConnectionHostType : int {
    SERVER,
    CLIENT,
};

class NetworkConnection {
  protected:
    Logger *logger = nullptr;
    asio::ip::tcp::socket socket;
    NetworkQueue<NetworkMessage> &networkQueue;
    NetworkConnectionHostType hostType;
    NetworkConnectionId id;
  public:
    explicit NetworkConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionHostType networkConnectionHostType, NetworkConnectionId connectionId)
        : socket(context), networkQueue(networkQueue), hostType(networkConnectionHostType), id(connectionId), logger(Logger::GetInstance()) {
    }

    virtual ~NetworkConnection() {
        if (IsConnected()) {
            Disconnect();
        }
    }

    bool IsConnected() const {
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

    virtual void StartReadingNetworkMessages() = 0;
};

class TCPConnection : public NetworkConnection {
  private:
    std::vector<char> networkBuffer;
    const unsigned int NETWORK_BUFFER_SIZE = 20 * 1024;
  public:
    explicit TCPConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionHostType networkConnectionHostType, NetworkConnectionId connectionId)
        : NetworkConnection(context, networkQueue, networkConnectionHostType, connectionId) {
        networkBuffer.resize(NETWORK_BUFFER_SIZE);
    }

    void SendNetworkMessage(const std::string &message)  {
        auto handleWriteFunction = [this] (const asio::error_code &errorCode, size_t bytes) {};
        asio::async_write(socket, asio::buffer(message), handleWriteFunction);
    }

    void StartReadingNetworkMessages() override;
};

#endif //NETWORK_CONNECTION_H
