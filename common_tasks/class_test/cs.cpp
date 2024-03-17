#include <iostream>

class Figure{
    public:
        Figure(){
            ;
        }
        ~Figure() noexcept(false){
            throw std::runtime_error("class creation error");
        }
    private:
        int dims=0;
};


int main(){

    Figure* fig;

    try{
        fig = new Figure();
        delete fig;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}