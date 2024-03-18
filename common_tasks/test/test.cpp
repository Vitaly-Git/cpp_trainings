#include <iostream>
#include <vector>
#include <thread>

class B {
public:
    virtual std::string f() const {
        return "B::f";
    }

    std::string g() const {
        return "B::g";
    }

    void print() const {
        std::cout << f() << std::endl;
        std::cout << g() << std::endl;
    }
};

class C : public B {
public:
    virtual std::string f() const {
        return "C::f";
    }

    std::string g() const {
        return "C::g";
    }
};

int main() {
//     B b;
//     C c;
//     B& c_link = c;

//     std::cout << b.f() << std::endl;
//     std::cout << b.g() << std::endl;
//     std::cout << c_link.f() << std::endl;
//     std::cout << c_link.g() << std::endl;
//     c_link.print();

    //   const int * x1;

    //*x1 = 50;

    // int* x1;

    // int** const x2 = &x1;

    // auto y =  *x2; 

    // int x = 3;
    // int y = 5;
    // std::cout << y / x << std::endl;

    std::vector<int> v = {1, 2, 3};
    std::cout << v[10] << std::endl;


    int x = 10;
    auto l1 = [=]() mutable {
        std::cout << x;
        x = 15;
    };
    auto l2 = [=]() mutable {
        std::cout << x;
        x = 16;
    };
    std::thread t1(l1);
    std::thread t2(l2);
    t1.join();
    t2.join(); 

    std::cout << x;

}