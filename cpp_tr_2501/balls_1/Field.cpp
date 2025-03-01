#include "Field.hpp"



Field* Field::field_ = nullptr;

Field* Field::get(){
    if (field_ == nullptr)
        field_ = new Field();
    return field_; 
}

void Field::createEmpty(int64_t width, int64_t height){
    width_ = width;
    height_ = height;

    for(auto item : cells_){
        delete(item.content);
    }

    cells_.clear();
    cells_.reserve(width_*height_);
    for(int64_t h = 0; h < height_; ++h){
        for(int64_t w = 0; w < width_; ++w){
            int64_t cellIdx = width_*h + w;
            cells_[cellIdx].content = new EmptyCell();
        }
    }        
}

void Field::fillCell(int64_t x, int64_t y, FieldCellContent* CellContent){
    int64_t cellIdx = width_*y + x;
    delete(cells_[cellIdx].content);
    cells_[cellIdx].content = CellContent;
}

void Field::draw(){
    for(int64_t h = 0; h < height_; ++h){
        for(int64_t w = 0; w < width_; ++w){
            int64_t cellIdx = width_*h + w;
            cells_[cellIdx].content->draw();
        }
        std::cout << "\n";
    }
}