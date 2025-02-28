#include <iostream>
#include <vector>

class FieldCellContent{
public:    
    virtual void draw() = 0;
};

enum class BallColor{
    Red,
    Green,
    Blue,
    Yellow
};

enum class BallType{
    Ball
};

class Ball:public FieldCellContent{
    BallColor color;
    BallType type;
public:    
    void draw() override;    
};

void Ball::draw(){

}


class FieldCell{
    bool IsEmpty = true;
    FieldCellContent* content = nullptr;
};

class Field{
public:    
    Field(Field &other) = delete;
    void operator=(const Field) = delete;
    static Field* get(){
        if (field_ == nullptr)
            field_ = new Field();
        return field_; 
    }
    void createEmpty(int64_t width, int64_t height){
        width_ = width;
        height_ = height;
        cells.clear();
        cells.reserve(width_*height_);
    }
    void Draw(){
        for(int64_t h = 0; h < height_; ++h){
            for(int64_t w = 0; w < width_; ++w){
                std::cout << "O";
            }
            std::cout << "\n";
        }
    }

private:    
    Field(){};
    static Field* field_;

    int64_t width_;
    int64_t height_;
    std::vector<FieldCell> cells;

};
Field* Field::field_ = nullptr;
 
int main(){
    Field* field = Field::get();

    std::cout << Field::get() << std::endl;
    
    field->createEmpty(8, 8);

    std::cout << Field::get() << std::endl;
}