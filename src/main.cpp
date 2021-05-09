#include <iostream>
#include <asio.hpp>
#include "core/networking/network_tcp_server.h"

template <typename Timer>
class AsyncWaitFunctor {
  public:
    AsyncWaitFunctor(Timer& timer): timer(timer) {}

    template <typename WaitHandler>
    auto operator()(WaitHandler handler) {
        return timer.async_wait(handler);
    }

  private:
    Timer& timer;
};

/// @brief Auxiliary factory function for binding a timer.
template <typename Timer>
AsyncWaitFunctor<Timer> BindAsyncWait(Timer& timer, int &count) {
    count++;
    return AsyncWaitFunctor<Timer>(timer);
}

void TestBind(asio::io_context &context) {
    int count = 0;
    asio::steady_timer timer(context, asio::chrono::seconds(1));

    auto handler = [](const asio::error_code& errorCode) {
        std::cout << "in handler" << std::endl;
    };

    auto func = BindAsyncWait(timer, count);
    func(handler);

    context.run();

    std::cout << "Final count is " << count << std::endl;
}

int main() {
    asio::io_context context;

//    TestBind(context);

    NetworkTCPServer *server = new NetworkTCPServer(context, 55555);
    server->Start();

    return 0;
}
