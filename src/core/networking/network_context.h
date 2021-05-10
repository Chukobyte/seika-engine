#ifndef NETWORK_CONTEXT_H
#define NETWORK_CONTEXT_H

#include <map>

#include "network_connection.h"

class NetworkContext {
  private:
    std::mutex connectionsMutex;
    std::map<NetworkConnectionId, TCPConnection*> networkConnections;
  public:

    TCPConnection* NewTCPConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionId connectionId) {
        TCPConnection *tcpConnection = new TCPConnection(context, networkQueue, connectionId);
        networkConnections.emplace(connectionId, tcpConnection);
        return tcpConnection;
    }

    void RemoveTCPConnection(TCPConnection *tcpConnection) {
        tcpConnection->Disconnect();
        int networkId = tcpConnection->GetId();
//        delete networkConnections[networkId]; // TODO: Figure out why deleting doesn't work
        networkConnections.erase(networkId);
    }
};


#endif //NETWORK_CONTEXT_H
