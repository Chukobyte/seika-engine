#include "network_tcp_server.h"

std::vector<char> NetworkTCPServer::networkBuffer(20 * 1024);

NetworkTCPServer::NetworkTCPServer(asio::io_context &context, int port) : context(context), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    logger = Logger::GetInstance();
}

void NetworkTCPServer::Start() {
    logger->Debug("Starting server accepting connections!");

    asio::ip::tcp::socket socket(context);
//    acceptor.accept(socket);

    auto acceptHandler = [](const asio::error_code& errorCode) {
        if (!errorCode) {
            std::cout << "New connection established" << std::endl;
        }
    };

//    acceptor.accept(socket);
    acceptor.async_accept(socket, acceptHandler);

    logger->Debug("Server accepting connections!");

    std::thread threadContext = std::thread([&]() {
        context.run();
    });

//    context.run();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20000ms);


    context.stop();
    if (threadContext.joinable()) {
        threadContext.join();
    }
}
