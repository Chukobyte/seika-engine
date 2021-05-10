#include "network_tcp_client.h"
#include "../global_dependencies.h"

NetworkTCPClient::NetworkTCPClient(asio::io_context &context, const std::string &ipAddress, int port) : context(context), socket(context), ipAddress(ipAddress), port(port) {
    networkContext = GD::GetContainer()->networkContext;
    logger = Logger::GetInstance();
}

NetworkTCPClient::~NetworkTCPClient() {
    Disconnect();
}

void NetworkTCPClient::Connect() {
    if (!connection) {
        connection = new TCPConnection(context, networkQueue, 1);

        asio::error_code  errorCode;
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ipAddress.c_str(), errorCode), port);

        if (!errorCode) {
            TCPConnection *tcpConnection = networkContext->NewTCPConnection(context, networkQueue, 0);
            tcpConnection->GetSocket();
        } else {
            logger->Error("Client failed to connect!\n" + errorCode.message());
        }

    }
}

void NetworkTCPClient::Disconnect() {
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

void NetworkTCPClient::ProcessMessageQueue() {
    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
    }
}
