#ifndef _EmptyCell_
#define _EmptyCell_

#include <iostream>
#include "FieldCellContent.hpp"

class EmptyCell : public FieldCellContent {
public:
    std::string renderToText(RenderType renderType = RenderType::TERMINAL) override;
};

#endif