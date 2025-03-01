#ifndef _BallCell_
#define _BallCell_

#include "FieldCellContent.hpp"

enum class BallCellColor {
    Red,
    Green,
    Blue,
    Yellow
};

enum class BallCellType {
    Ball
};

class BallCell : public FieldCellContent {
    BallCellColor color;
    BallCellType type;
public:
    void draw(RenderType renderType = RenderType::TERMINAL) override;
    void renderToText(RenderType renderType = RenderType::TERMINAL) override;
};

#endif