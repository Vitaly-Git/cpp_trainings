#include <boost/json.hpp>

// Этот заголовочный файл надо подключить в одном и только одном .cpp-файле программы
#include <boost/json/src.hpp>
#include <iostream>
#include <string>

namespace json = boost::json;
using namespace std::literals;

int main() {
    auto json_str = R"({"name": "Harry Potter"})";
    auto value = json::parse(json_str);
    std::cout << value.as_object().at("name") << std::endl; // Harry Potter
    std::cout << json::serialize(value) << std::endl; // {"name": "Harry Potter"}
}