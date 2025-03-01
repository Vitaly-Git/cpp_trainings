#ifndef _EmptyCell_
#define _EmptyCell_

#include "FieldCellContent.hpp"

class EmptyCell : public FieldCellContent {
public:
    void draw(RenderType renderType = RenderType::TERMINAL) override;
    void renderToText(RenderType renderType = RenderType::TERMINAL) override;
};

#endif