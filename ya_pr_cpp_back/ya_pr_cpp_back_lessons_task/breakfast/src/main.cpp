// Подключаем заголовочный файл <sdkddkver.h> в системе Windows,
// чтобы избежать предупреждения о неизвестной версии Platform SDK,
// когда используем заголовочные файлы библиотеки Boost.Asio
#ifdef WIN32
#include <sdkddkver.h>
#endif

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

// #define SYNC
// #define ASYNC
#define ASYNC_SMART

namespace net = boost::asio;
namespace sys = boost::system;
using namespace std::chrono;
using namespace std::literals;

void syncBreakfast();
void asyncBreakfast();
void asyncSmartBreakfast();

int main() {

  #ifdef SYNC
    syncBreakfast();
  #endif

  #ifdef ASYNC
    asyncBreakfast();
  #endif

  #ifdef ASYNC_SMART
    asyncSmartBreakfast();
  #endif

}

void syncBreakfast() {

   // Контекст для выполнения операций ввода-вывода.
   // Другие классы библиотеки выполняют с его помощью операции ввода-вывода
   net::io_context io;

   // Замеряем время начала программы
   const auto start_time = steady_clock::now();

   {
        // Устанавливаем таймер на 5 секунд
        net::steady_timer t(io, 5s);
        // Варим кофе, пока не истечёт таймер
        std::cout << "Brew coffee"sv << std::endl;
        t.wait();
  
      // Кофе сварен, переливаем его в чашку
        std::cout << "Pour coffee in the cup"sv << std::endl;
    }

    // Жарим яичницу 3 секунды
    {
        std::cout << "Fry eggs"sv << std::endl;
        net::steady_timer t(io, 3s);
        t.wait();
        std::cout << "Put eggs onto the plate" << std::endl;
    }

    const auto cook_duration = duration<double>(steady_clock::now() - start_time);
    std::cout << "Breakfast has been cooked in "sv << cook_duration.count() << "s"sv << std::endl;
    std::cout << "Enjoy your meal"sv << std::endl;
}

void asyncBreakfast(){


   // Контекст для выполнения операций ввода-вывода.
   // Другие классы библиотеки выполняют с его помощью операции ввода-вывода
   net::io_context io;

   // Замеряем время начала программы
   const auto start_time = steady_clock::now();

    // Жарим яичницу 3 секунды
    {
        net::steady_timer t(io, 3s);
        std::cout << "Fry eggs"sv << std::endl;
        t.async_wait([](sys::error_code ec) {
            if (ec) {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Put eggs onto the plate"sv << std::endl;
        });
    }

    // Варим кофе 5 секунд
    {
        net::steady_timer t(io, 5s);
        std::cout << "Brew coffee"sv << std::endl;
        t.async_wait([](sys::error_code ec) {
            // Эта функция будет вызвана асинхронно.
            // Код ошибки позволит узнать, успешно ли завершилось ожидание
            if (ec) {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Pour coffee in the cup"sv << std::endl;
        });
    }

    // Запускаем обработку асинхронных операций
    try {
        std::cout << "Run asynchronous operations"sv << std::endl;
        io.run();
        const auto cook_duration = duration<double>(steady_clock::now() - start_time);
        std::cout << "Breakfast has been cooked in "sv << cook_duration.count() << "s"sv << std::endl;
        std::cout << "Enjoy your meal"sv << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } 
}

void asyncSmartBreakfast(){

   // Контекст для выполнения операций ввода-вывода.
   // Другие классы библиотеки выполняют с его помощью операции ввода-вывода
   net::io_context io;

   // Замеряем время начала программы
   const auto start_time = steady_clock::now();

    // Жарим яичницу 3 секунды
    {
        auto t = std::make_shared<net::steady_timer>(io, 3s);
        std::cout << "Fry eggs"sv << std::endl;
        // Захват переменной t внутри лямбда-функции продлит время жизни таймера
        // до тех пор, пока не будет вызван обработчик.
        t->async_wait([t](sys::error_code ec) {
            if (ec) {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Put eggs onto the plate. Thread id: "sv << std::this_thread::get_id()
                      << std::endl;
        });
    }

    // Варим кофе 5 секунд
    {
        auto t = std::make_shared<net::steady_timer>(io, 5s);
        std::cout << "Brew coffee"sv << std::endl;
        t->async_wait([t](sys::error_code ec) {
            if (ec) {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Pour coffee in the cup. Thread id: "sv << std::this_thread::get_id()
                      << std::endl;
        });
    }

    // Запускаем обработку асинхронных операций
    try {
        std::cout << "Run asynchronous operations"sv << std::endl;
        io.run();
        const auto cook_duration = duration<double>(steady_clock::now() - start_time);
        std::cout << "Breakfast has been cooked in "sv << cook_duration.count() << "s"sv << std::endl;
        std::cout << "Thread id: "sv << std::this_thread::get_id() << std::endl;
        std::cout << "Enjoy your meal"sv << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}