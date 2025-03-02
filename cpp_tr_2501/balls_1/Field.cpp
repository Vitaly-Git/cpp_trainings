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

            if (IsBorderCell(h, 0, height_) or  IsBorderCell(w, 0, width_)) {
                cells_[cellIdx].content = new BorderCell();
            } else {
                cells_[cellIdx].content = new EmptyCell();
            }

            
        }
    }        
}

void Field::fillCell(int64_t x, int64_t y, FieldCellContent* CellContent){
    int64_t cellIdx = width_*y + x;
    delete(cells_[cellIdx].content);
    cells_[cellIdx].content = CellContent;
}

void Field::draw(RenderType renderType){
    for(int64_t h = 0; h < height_; ++h){
        for(int64_t w = 0; w < width_; ++w){
            int64_t cellIdx = width_*h + w;
            cells_[cellIdx].content->draw(renderType);
        }
        std::cout << "\n";
    }
}

bool IsBorderCell(int64_t currentVal, int64_t cornerVal1, int64_t cornerVal2)(
    return currentVal == cornerVal1 or currentVal == cornerVal1
)