#ifndef NETWORK_CONNECTION_CONTEXT_H
#define NETWORK_CONNECTION_CONTEXT_H

#include <map>

#include "network_connection.h"

class NetworkConnectionContext {
  private:
    std::mutex connectionsMutex;
    std::map<NetworkConnectionId, TCPConnection*> networkConnections;
  public:

    TCPConnection* NewTCPConnection(asio::io_context &context, NetworkQueue<NetworkMessage> &networkQueue, NetworkConnectionHostType hostType, NetworkConnectionId connectionId) {
        TCPConnection *tcpConnection = new TCPConnection(context, networkQueue, hostType, connectionId);
        networkConnections.emplace(connectionId, tcpConnection);
        return tcpConnection;
    }

    void RemoveTCPConnection(TCPConnection *tcpConnection) {
        tcpConnection->Disconnect();
        int networkId = tcpConnection->GetId();
//        delete networkConnections[networkId]; // TODO: Figure out why deleting doesn't work
        networkConnections.erase(networkId);
    }

    void RemoveAllConnection() {
        for (auto &pair : networkConnections) {
            TCPConnection *tcpConnection = pair.second;
            networkConnections.erase(tcpConnection->GetId());
            tcpConnection->Disconnect();
        }
    }
};


#endif //NETWORK_CONNECTION_CONTEXT_H
