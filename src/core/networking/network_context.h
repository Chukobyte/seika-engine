#ifndef NETWORK_CONTEXT_H
#define NETWORK_CONTEXT_H

#include <map>

#include "network_connection.h"

class NetworkContext {
  public:
    std::map<NetworkConnectionId, TCPConnection*> networkConnections;

    TCPConnection* NewTCPConnection(asio::io_context &context, NetworkConnectionId connectionId) {
        TCPConnection *tcpConnection = new TCPConnection(context);
        networkConnections.emplace(connectionId, tcpConnection);
        return GetTCPConnection(connectionId);
    }

    TCPConnection* GetTCPConnection(NetworkConnectionId connectionId) {
        return networkConnections[connectionId];
    }
};


#endif //NETWORK_CONTEXT_H
