#include "network_tcp_server.h"
#include "../global_dependencies.h"

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
    networkContext = GD::GetContainer()->networkContext;
}

void NetworkTCPServer::Start() {
    context.restart();
    logger->Debug("Server accepting connections!");

    AcceptConnections();

    threadContext = std::thread([&]() {
        context.run();
    });

    // TODO: should be place in main loop (without sleep of course)
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10000ms);

    ProcessMessageQueue();
}

void NetworkTCPServer::Stop() {}

void NetworkTCPServer::ProcessMessageQueue(unsigned int maxMessages) {
    context.stop();
    if (threadContext.joinable()) {
        threadContext.join();
    }

    unsigned int messageCount = 0;
    while (messageCount < maxMessages && !networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        if (!networkMessage.message.empty() && networkMessage.message != "\n" && networkMessage.message != "\r\n" && networkMessage.message != " ") {
            std::cout << "Queued Message: \n'" << networkMessage.message << "'\n" << std::endl;
        }
        messageCount++;
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
