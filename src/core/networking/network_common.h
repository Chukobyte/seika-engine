#ifndef NETWORK_COMMON_H
#define NETWORK_COMMON_H

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

//#ifdef _WIN32
//#define _WIN32_WINNT 0x0A00
//#endif

#define ASIO_STANDALONE
//#define ASIO_ENABLE_HANDLER_TRACKING
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "../utils/logger.h"

#endif //NETWORK_COMMON_H
