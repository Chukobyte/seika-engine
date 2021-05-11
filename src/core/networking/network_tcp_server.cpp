#include "network_tcp_server.h"
#include "../global_dependencies.h"
#include "../signal_manager.h"

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
    networkConnectionContext = GD::GetContainer()->networkConnectionContext;
}

void NetworkTCPServer::Start() {
    AcceptConnections();
}

void NetworkTCPServer::Stop() {
    networkConnectionContext->RemoveAllConnection();
}

void NetworkTCPServer::ProcessMessageQueue() {
    context.poll();

    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        if (!networkMessage.message.empty() && networkMessage.message != "\n" && networkMessage.message != "\r\n" && networkMessage.message != " ") {
//            std::cout << "[SERVER] Queued Message: '" << networkMessage.message << "'\n" << std::endl;
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "message_received", PythonSignalArguments::GetStringSignalArgument(networkMessage.message));
        }
    }

    // Check client connections
}

void NetworkTCPServer::AcceptConnections() {
    TCPConnection *tcpConnection = networkConnectionContext->NewTCPConnection(context, networkQueue, NetworkConnectionHostType_SERVER, 0);
    auto handleAcceptFunction = [this, tcpConnection](const asio::error_code &errorCode) {
        if (!errorCode) {
//            logger->Debug("New connection established!");
//            tcpConnection->SendNetworkMessage("[FROM SERVER] Hello from server!");
            tcpConnection->StartReadingNetworkMessages();
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "peer_connected");
        } else {
            logger->Error("Error establishing connection: " + errorCode.message() + "\nError Code: " + std::to_string(errorCode.value()));
            networkConnectionContext->RemoveTCPConnection(tcpConnection);
        }
        AcceptConnections();
    };
    acceptor.async_accept(tcpConnection->GetSocket(), handleAcceptFunction);
}
void NetworkTCPServer::SendMessageToAllClients(const std::string &message) {
    networkConnectionContext->SendMessageToAllConnections(message);
}
