//
// Created by adlarkin on 11/5/18.
//

#ifndef RRT_STAR_CPP_SHAPEDRAWER_H
#define RRT_STAR_CPP_SHAPEDRAWER_H


#include <map>
#include <vector>
#include "../State/Location.h"

enum Color {WHITE, BLACK, RED, GREEN, BLUE};

class ShapeDrawer {
public:
    explicit ShapeDrawer(float radius);

    void drawCircle(Location center, Color color);
    void drawRectangle(float width, Location topLeft, float height, Color color = WHITE);
    void drawLine(Location start, Location end, Color color = WHITE);
    void updateScreen();

private:
    void setDrawingColor(Color color);

    double radius;
    std::map<Color, std::vector<float> > colorMap {
            {WHITE, {1.0f, 1.0f, 1.0f}},
            {BLACK, {0.0f, 0.0f, 0.0f}},
            {RED, {1.0f, 0.0f, 0.0f}},
            {GREEN, {0.0f, 1.0f, 0.0f}},
            {BLUE, {0.0f, 0.0f, 1.0f}}
    };
};


#endif //RRT_STAR_CPP_SHAPEDRAWER_H