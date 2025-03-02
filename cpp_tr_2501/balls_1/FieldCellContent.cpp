#include <iostream>
#include "FieldCellContent.hpp"

void FieldCellContent::draw(RenderType renderType) {
    std::cout << renderToText(renderType);
}