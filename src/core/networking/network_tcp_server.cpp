#include "network_tcp_server.h"
#include "../global_dependencies.h"

//std::vector<char> NetworkTCPServer::networkBuffer(20 * 1024);

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
    networkContext = GD::GetContainer()->networkContext;
}

void NetworkTCPServer::Start() {
    logger->Debug("Server accepting connections!");

    std::thread threadContext = std::thread([&]() {
        context.run();
    });

    AcceptConnections();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10000ms);

    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
        std::cout << "Queue Messages: \n" << networkMessage.message << std::endl;
    }

    context.stop();
    if (threadContext.joinable()) {
        threadContext.join();
    }
}

void NetworkTCPServer::AcceptConnections() {
    TCPConnection *tcpConnection = networkContext->NewTCPConnection(context, networkQueue, 0);
    auto handleAcceptFunction = [this, tcpConnection](const asio::error_code &errorCode) {
        if (!errorCode) {
            logger->Debug("New connection established!");
            tcpConnection->Start();
        } else {
            logger->Error("Error establishing connection: " + errorCode.message() + "\nError Code: " + std::to_string(errorCode.value()));
            networkContext->RemoveTCPConnection(tcpConnection);
        }
        AcceptConnections();
    };
    acceptor.async_accept(tcpConnection->GetSocket(), handleAcceptFunction);
}
