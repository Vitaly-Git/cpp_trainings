#include <iostream>
#include "BallCell.hpp"

std::string BallCell::renderToText(RenderType renderType) {
    if (renderType == RenderType::TERMINAL){
        return "O";
    } else if (renderType == RenderType::HTML){
        return "<b> O </b>";
    } else {
        return "";
    }
}