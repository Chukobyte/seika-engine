#ifndef NETWORK_CONTEXT_H
#define NETWORK_CONTEXT_H

#include <map>

#include "network_connection.h"

class NetworkContext {
private:
    std::mutex connectionsMutex;
    std::map<NetworkConnectionId, TCPConnection*> networkConnections;
public:

    TCPConnection* NewTCPConnection(asio::io_context &context, NetworkConnectionId connectionId) {
        connectionsMutex.lock();
        TCPConnection *tcpConnection = new TCPConnection(context);
        networkConnections.emplace(connectionId, tcpConnection);
        connectionsMutex.unlock();
        return GetTCPConnection(connectionId);
    }

    TCPConnection* GetTCPConnection(NetworkConnectionId connectionId) {
        connectionsMutex.lock();
        TCPConnection *tcpConnection = networkConnections[connectionId];
        connectionsMutex.unlock();
        return tcpConnection;
    }
};


#endif //NETWORK_CONTEXT_H
