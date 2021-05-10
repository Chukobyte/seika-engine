#include "network_tcp_server.h"
#include "../global_dependencies.h"

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
    networkContext = GD::GetContainer()->networkContext;
}

void NetworkTCPServer::Start() {
    context.restart();
    logger->Debug("Server started!");

    AcceptConnections();
}

void NetworkTCPServer::Stop() {
    context.stop();
}

void NetworkTCPServer::ProcessMessageQueue() {
    context.poll();

    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        if (!networkMessage.message.empty() && networkMessage.message != "\n" && networkMessage.message != "\r\n" && networkMessage.message != " ") {
            std::cout << "[SERVER] Queued Message: \n'" << networkMessage.message << "'\n" << std::endl;
        }
    }
}

void NetworkTCPServer::AcceptConnections() {
    TCPConnection *tcpConnection = networkContext->NewTCPConnection(context, networkQueue, NetworkConnectionHostType_SERVER, 0);
    auto handleAcceptFunction = [this, tcpConnection](const asio::error_code &errorCode) {
        if (!errorCode) {
            // TODO: Emit signal for new connection
            logger->Debug("New connection established!");
            tcpConnection->SendNetworkMessage("[FROM SERVER] Hello from server!");
            tcpConnection->StartReadingNetworkMessages();
        } else {
            logger->Error("Error establishing connection: " + errorCode.message() + "\nError Code: " + std::to_string(errorCode.value()));
            networkContext->RemoveTCPConnection(tcpConnection);
        }
        AcceptConnections();
    };
    acceptor.async_accept(tcpConnection->GetSocket(), handleAcceptFunction);
}
