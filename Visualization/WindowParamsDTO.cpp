//
// Created by ashton on 12/21/18.
//

#include "WindowParamsDTO.h"

WindowParamsDTO::WindowParamsDTO(int winWidth, int winHeight, int x_winPos, int y_winPos, std::string title) :
    winWidth(winWidth),
    winHeight(winHeight),
    x_winPos(x_winPos),
    y_winPos(y_winPos),
    title(title)
    {}

int WindowParamsDTO::getWinWidth() const {
    return winWidth;
}

int WindowParamsDTO::getWinHeight() const {
    return winHeight;
}

int WindowParamsDTO::getX_winPos() const {
    return x_winPos;
}

int WindowParamsDTO::getY_winPos() const {
    return y_winPos;
}

const std::string &WindowParamsDTO::getTitle() const {
    return title;
}
