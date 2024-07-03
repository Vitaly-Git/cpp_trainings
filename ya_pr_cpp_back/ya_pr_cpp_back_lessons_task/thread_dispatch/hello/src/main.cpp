#include <iostream>
#include <chrono>
#include <syncstream>
#include <boost/asio.hpp>
#include <memory> // Содержит классы std::shared_ptr и std::enable_shared_from_this
#include <thread>
#include <atomic>

namespace net = boost::asio;
namespace sys = boost::system;
using namespace std::literals;
using namespace std::chrono;
using Timer = net::steady_timer;
namespace ph = std::placeholders;

int main() {
    net::io_context io;

    net::post(io, [&io] {  // (1)
        std::cout << 'A';
        net::post(io, [] {  // (2)
            std::cout << 'B';
        });
        std::cout << 'C';
    });

    net::dispatch(io, [&io] {  // (3)
        std::cout << 'D';
        net::post(io, [] {  // (4)
            std::cout << 'E';
        });
        net::defer(io, [] {  // (5)
            std::cout << 'F';
        });
        net::dispatch(io, [] {  // (6)
            std::cout << 'G';
        });
        std::cout << 'H';
    });

    std::cout << 'I';
    io.run();
    std::cout << 'J';
}