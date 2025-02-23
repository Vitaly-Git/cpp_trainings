#include <iostream>
#include <vector>

enum class BallColor{
    Red,
    Green,
    Blue,
    Yellow
};

enum class BallType{
    Ball
};

class Ball{
    BallColor color;
    BallType type;
};

class Field{
public:    
    Field(Field &other) = delete;
    void operator=(const Field) = delete;
    static Field* GetField(){
        if (field_ == nullptr)
            field_ = new Field();
        return field_; 
    }
    void CreateField(int64_t width, int64_t height){
        width_ = width;
        height_ = height;
        balls.clear();
        balls.reserve(width_*height_);
    }

private:    
    Field(){};
    static Field* field_;

    int64_t width_;
    int64_t height_;
    std::vector<Ball> balls;

};
Field* Field::field_ = nullptr;
 
int main(){
    Field* field = Field::GetField();

    std::cout << Field::GetField() << std::endl;
    
    field->CreateField(8, 8);

    std::cout << Field::GetField() << std::endl;
}