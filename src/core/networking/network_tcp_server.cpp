#include "network_tcp_server.h"

std::vector<char> NetworkTCPServer::networkBuffer(20 * 1024);

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
}

void NetworkTCPServer::Start() {
    logger->Debug("Server accepting connections!");

    std::thread threadContext = std::thread([&]() {
        context.run();
    });

    AcceptConnections();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20000ms);


    context.stop();
    if (threadContext.joinable()) {
        threadContext.join();
    }
}

void NetworkTCPServer::AcceptConnections() {
    TCPConnection *tcpConnection = new TCPConnection(context);

    auto acceptHandler = [](const asio::error_code& errorCode) {
        if (!errorCode) {
//            tcpConnection->Start();
            std::cout << "New connection established" << std::endl;
        }
    };

    acceptor.async_accept(tcpConnection->GetSocket(), acceptHandler);
}

void NetworkTCPServer::HandleAccept(const asio::error_code &errorCode) {
    if (!errorCode) {
        std::cout << "New connection established" << std::endl;
    }
}
