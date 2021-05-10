#ifndef NETWORK_CONTEXT_H
#define NETWORK_CONTEXT_H

#include <map>

#include "network_connection.h"

class NetworkContext {
  public:
    std::map<NetworkConnectionId, NetworkConnection*> networkConnections;

    template<typename ConnectionType>
    ConnectionType* NewConnection(asio::io_context &context, NetworkConnectionId connectionId) {
        ConnectionType *networkConnection = new ConnectionType(context);
        networkConnections.emplace(connectionId, networkConnection);
        return &networkConnection[connectionId];
    }
};


#endif //NETWORK_CONTEXT_H
