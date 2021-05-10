#include "network_tcp_client.h"
#include "../global_dependencies.h"

NetworkTCPClient::NetworkTCPClient(asio::io_context &context, const std::string &ipAddress, int port) : context(context), socket(context), ipAddress(ipAddress), port(port) {
    networkConnectionContext = GD::GetContainer()->networkConnectionContext;
    logger = Logger::GetInstance();
}

NetworkTCPClient::~NetworkTCPClient() {
    Disconnect();
}

void NetworkTCPClient::Connect() {
    if (!connection) {
        asio::error_code errorCode;
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ipAddress.c_str(), errorCode), port);
        connection = networkConnectionContext->NewTCPConnection(context, networkQueue, NetworkConnectionHostType_CLIENT, 1);
        connection->GetSocket().connect(endpoint, errorCode);

        if (!errorCode) {
            logger->Debug("Connected to server successfully!");
            connection->StartReadingNetworkMessages();
        } else {
            logger->Error("Client failed to connect!\n" + errorCode.message());
        }

    }
}

void NetworkTCPClient::Disconnect() {
    if (connection) {
        context.stop();
        delete connection;
        connection = nullptr;
    }
}

void NetworkTCPClient::ProcessMessageQueue() {
    context.poll();

    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        if (!networkMessage.message.empty() && networkMessage.message != "\n" && networkMessage.message != "\r\n" && networkMessage.message != " ") {
            std::cout << "[Client] Queued Message: '" << networkMessage.message << "'\n" << std::endl;
        }
    }
}
