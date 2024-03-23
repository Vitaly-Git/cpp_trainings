#include <iostream>

class Figure{
    public:
        Figure(){
            ;
        }
        ~Figure() noexcept(false){
            throw std::runtime_error("class creation error");
        }
        std::string comment;
    private:
        int dims=0;
};

struct FigureStruct{
    std::string comment;
};

int main(){

    Figure* fig;

    try{
        fig = new Figure();
        delete fig;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }

    delete fig;

    // fig = new Figure("Test");

    // FigureStruct* fg = new FigureStruct("Qube");


    return 0;
}