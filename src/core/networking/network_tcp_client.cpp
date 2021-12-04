#include "network_tcp_client.h"
#include "../global_dependencies.h"
#include "../signal_manager.h"

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
        connection = networkConnectionContext->NewTCPConnection(context, networkQueue, NetworkConnectionHostType::CLIENT);
        connection->GetSocket().connect(endpoint, errorCode);

        if (!errorCode) {
//            logger->Debug("Connected to server successfully!");
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "connected_to_server");
            connection->StartReadingNetworkMessages();
        } else {
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "connection_to_server_failed");
//            logger->Error("Client failed to connect!\n" + errorCode.message());
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
    context.poll();

    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        if (!networkMessage.message.empty() && networkMessage.message != "\n" && networkMessage.message != "\r\n" && networkMessage.message != " ") {
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "message_received", PythonSignalArguments::GetStringSignalArgument(networkMessage.message));
        }
    }
}

void NetworkTCPClient::SendMessageToServer(const std::string &message) {
    if (connection) {
        connection->SendNetworkMessage(message);
    }
}