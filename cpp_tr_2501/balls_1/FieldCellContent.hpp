#ifndef _FieldCellContent_
#define _FieldCellContent_

#include "RenderType.hpp"

class FieldCellContent {
public:
    virtual void draw(RenderType renderType = RenderType::TERMINAL) = 0;
    virtual void renderToText(RenderType renderType = RenderType::TERMINAL): std::String = 0;  
};

#endif