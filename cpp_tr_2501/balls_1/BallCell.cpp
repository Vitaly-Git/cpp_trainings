#include <iostream>
#include "BallCell.hpp"


void BallCell::renderToText(RenderType renderType) {

    if (renderType == RenderType::TERMINAL){
        std::cout << "O";
    } else if (renderType == RenderType::HTML){
        std::cout << "<b> O </b>";
    }

}

void BallCell::draw(RenderType renderType) {
    std::cout << renderToText(renderType);
}