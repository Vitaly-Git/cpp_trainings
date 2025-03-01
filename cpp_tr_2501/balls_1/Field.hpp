#ifndef _Field_
#define _Field_

#include <iostream>
#include <vector>
#include "FieldCell.hpp"
#include "EmptyCell.hpp"
#include "FieldCellContent.hpp"

class Field{
public:    
    Field(Field &other) = delete;
    void operator=(const Field) = delete;
    static Field* get();
    void createEmpty(int64_t width, int64_t height);
    void fillCell(int64_t x, int64_t y, FieldCellContent* CellContent);
    void draw();

private:    
    Field(){};
    static Field* field_;

    int64_t width_;
    int64_t height_;
    std::vector<FieldCell> cells_;

};

#endif