//
// Created by ashton on 12/21/18.
//

#ifndef RRT_STAR_CPP_WINDOWPARAMSDTO_H
#define RRT_STAR_CPP_WINDOWPARAMSDTO_H

#include <string>

class WindowParamsDTO {
public:
    WindowParamsDTO(int winWidth, int winHeight, int x_winPos, int y_winPos, const std::string &title);
    int getWinWidth() const;
    int getWinHeight() const;
    int getX_winPos() const;
    int getY_winPos() const;
    const std::string &getTitle() const;

private:
    int winWidth;
    int winHeight;
    int x_winPos;
    int y_winPos;
    std::string title;
};


#endif //RRT_STAR_CPP_WINDOWPARAMSDTO_H
