//
// Created by adlarkin on 11/5/18.
//

#ifndef RRT_STAR_CPP_SHAPEDRAWER_H
#define RRT_STAR_CPP_SHAPEDRAWER_H


#include <map>
#include <vector>
#include "../State/Location.h"
#include "WindowParamsDTO.h"

enum Color {WHITE, BLACK, GREY, RED, GREEN, BLUE, LIGHT_BLUE, PINK};

#define DEFAULT_WIDTH 1.0f

class Drawer {
public:
    explicit Drawer(const WindowParamsDTO &screenParams);

    void drawCircle(const Location &center, Color color, double radius);
    void drawRectangle(double width, const Location &topLeft, double height, Color color);
    void drawLine(const Location &start, const Location &end, Color color, float lineWidth = DEFAULT_WIDTH);
    void eraseLine(const Location &start, const Location &end, float lineWidth = DEFAULT_WIDTH);
    void updateScreen();
    void clearScreen();

    void keepScreenOpen();
    void deleteScreen();    // todo: maybe make a destructor & call this there instead of having another class call it

private:
    void initScreen(const WindowParamsDTO &screenParams);
    void setDrawingColor(Color color);

    std::map<Color, std::vector<float> > colorMap {
            {WHITE, {1.0f, 1.0f, 1.0f}},
            {BLACK, {0.0f, 0.0f, 0.0f}},
            {GREY, {.35f, .35f, .35f}},
            {RED, {1.0f, 0.0f, 0.0f}},
            {GREEN, {0.0f, 0.9f, 0.0f}},
            {BLUE, {0.0f, 0.1f, 1.0f}},
            {LIGHT_BLUE, {0.0f, 0.55f, 1.0f}},
            {PINK, {0.8f, 0.5f, 0.65f}}
    };
    int windowID;
};


#endif //RRT_STAR_CPP_SHAPEDRAWER_H