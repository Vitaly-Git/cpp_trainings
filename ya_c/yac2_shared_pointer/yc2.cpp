#include <iostream>
#include <memory>
// #include <type_traits>
#include <vector>
 
// struct C
// {
//     // constructors needed (until C++20)
//     C(int i) : i(i) {}
//     C(int i, float f) : i(i), f(f) {}
//     int i;
//     float f{};
// };
 
class Duck{
    public:
        std::string name;
        bool quack(){
            return true;
        }
};

int main()
{
    Duck *d = new Duck();

    typedef int32_t *int32_ptr;

    int32_t * intPtr = (int32_t *)calloc(sizeof(int32_t),1);
    *intPtr = 1;

    int32_t * i = new int32_t[5];
    *i = 1;
    *(i+2) = 2;
    *(i+3) = 3;
    *(i+4) = 4;
    *(i+5) = 5;

    Duck * dPtr1 = new Duck();
    dPtr1->name = "Kria 1";

    auto dPtr2 = std::make_shared<Duck>();
    dPtr2->name = "123";
    std::cout << dPtr2.use_count() << std::endl;

    auto dPtr3 = dPtr2;
    std::cout << dPtr2.use_count() << std::endl;
    std::cout << dPtr3.use_count() << std::endl;
    dPtr3.reset();

    std::cout << dPtr2.use_count() << std::endl;
    std::cout << dPtr3.use_count() << std::endl;
    dPtr3 = dPtr2;
    std::cout << dPtr2.use_count() << std::endl;
    std::cout << dPtr3.use_count() << std::endl;

    auto sp1 = std::make_shared<Duck>;
    auto sp3 = std::make_shared<int32_t>;
    auto sp2 = std::make_shared<Duck>;    
    auto sp4 = std::make_shared<int32_t>(5);
    *sp4 = 2;
    // *sp3.swap(new int32_t(1), *sp3);

    auto sp5 = std::make_shared<int>(150);
    *sp5 = 100;

}