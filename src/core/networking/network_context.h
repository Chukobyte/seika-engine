#ifndef NETWORK_CONTEXT_H
#define NETWORK_CONTEXT_H

#include "network_tcp_server.h"
#include "network_tcp_client.h"

class NetworkContext {
  private:
    asio::io_context context;
    Logger *logger = nullptr;
  public:
    NetworkTCPServer *server = nullptr;
    NetworkTCPClient *client = nullptr;

    NetworkContext() : logger(Logger::GetInstance()) {}

    void CreateServer(int port) {
        if (!server) {
            server = new NetworkTCPServer(context, port);
        } else {
            logger->Error("Server already created!");
        }
    }

    void StartServer() {
        if (server) {
            server->Start();
        } else {
            logger->Error("Server hasn't been created!");
        }
    }

    void StopServer() {
        if (server) {
            server->Stop();
        } else {
            logger->Error("Server hasn't been created!");
        }
    }

    void RemoveServer() {
        StopServer();
        delete server;
        server = nullptr;
    }

    void ServerSendMessageToAllClients(const std::string &message) {
        if (server) {
            server->SendMessageToAllClients(message);
        }
    }

    void CreateClient(const std::string &ipAddress, int port) {
        if (!client) {
            client = new NetworkTCPClient(context, ipAddress, port);
        } else {
            logger->Error("Client already created!");
        }
    }

    void ConnectClient() {
        if (client) {
            client->Connect();
        } else {
            logger->Error("Client hasn't been created!");
        }
    }

    void DisconnectClient() {
        if (client) {
            client->Disconnect();
        } else {
            logger->Error("Client hasn't been created!");
        }
    }

    void RemoveClient() {
        DisconnectClient();
        delete client;
        client = nullptr;
    }

    void ClientSendMessageToServer(const std::string &message) {
        if (client) {
            client->SendMessageToServer(message);
        }
    }

    void Poll() {
        if (server) {
            server->ProcessMessageQueue();
        } else if (client) {
            client->ProcessMessageQueue();
        }
    }

    bool DoesServerExists() const {
        return server != nullptr;
    }

    bool DoesClientExists() const {
        return client != nullptr;
    }
};

#endif //NETWORK_CONTEXT_H
