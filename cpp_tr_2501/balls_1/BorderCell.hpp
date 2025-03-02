#ifndef _BorderCell_
#define _BorderCell_

#include <iostream>
#include "FieldCellContent.hpp"

class BorderCell : public FieldCellContent {
public:
    std::string renderToText(RenderType renderType = RenderType::TERMINAL) override;
};

#endif