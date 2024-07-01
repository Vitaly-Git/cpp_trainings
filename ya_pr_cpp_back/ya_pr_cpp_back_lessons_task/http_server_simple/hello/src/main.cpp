// Подключим библиотеку Boost.Optional, чтобы убедиться, что Boost подключен успешно
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

namespace net = boost::asio;
using tcp = net::ip::tcp;
using namespace std::literals;

int main() {

    // Контекст для выполнения синхронных и асинхронных операций ввода/вывода
    net::io_context ioc;

    const auto address = net::ip::make_address("0.0.0.0");
    constexpr unsigned short port = 8080;

    // Объект, позволяющий принимать tcp-подключения к сокету
    tcp::acceptor acceptor(ioc, {address, port});

    std::cout << "Waiting for socket connection"sv << std::endl;
    tcp::socket socket(ioc);
    acceptor.accept(socket);
    std::cout << "Connection received"sv << std::endl;

    constexpr std::string_view response
        = "HTTP/1.1 200 OK\r\n"sv
          "Content-Type: text/plain\r\n\r\n"sv
          "Hello"sv;
    net::write(socket, net::buffer(response));

}
