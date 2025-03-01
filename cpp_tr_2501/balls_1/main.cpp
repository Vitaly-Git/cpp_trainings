#include <iostream>
#include "FieldCellContent.hpp"
#include "EmptyCell.hpp"
#include "BallCell.hpp"
#include "FieldCell.hpp"
#include "Field.hpp"

 
int main(){
    Field* field = Field::get();

    std::cout << Field::get() << std::endl;
    
    field->createEmpty(8, 8);
    field->fillCell(3, 3, new BallCell());
    field->draw();

    std::cout << Field::get() << std::endl;
}