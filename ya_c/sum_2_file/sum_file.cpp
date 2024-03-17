#include <iostream>
#include <fstream>

int main(){

    std::ifstream fileToRead;
    std::ofstream fileToWrite;

    fileToRead.open("input.txt");
    fileToWrite.open("output.txt");

    int64_t a = 0;
    int64_t b = 0;

    fileToRead >> a >> b;
    fileToWrite << a + b;

    return 0;
}