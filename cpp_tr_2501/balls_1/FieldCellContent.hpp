#ifndef _FieldCellContent_
#define _FieldCellContent_

#include <iostream>
#include "RenderType.hpp"

class FieldCellContent {
public:
    virtual std::string renderToText(RenderType renderType = RenderType::TERMINAL) = 0;  
    void draw(RenderType renderType = RenderType::TERMINAL);
};

#endif