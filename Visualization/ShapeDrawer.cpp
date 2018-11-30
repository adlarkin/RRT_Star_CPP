//
// Created by adlarkin on 11/5/18.
//

#include <GL/gl.h>
#include <math.h>
#include "ShapeDrawer.h"

#define PI 3.14159265359

ShapeDrawer::ShapeDrawer(float radius) : radius(radius) {}

void ShapeDrawer::drawCircle(Location center, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    for (int theta = 0; theta < 360; ++theta) {
        glVertex2f(center.getXCoord() + (float)(cos(theta*PI/180)*radius),
                   center.getYCoord() + (float)(sin(theta*PI/180)*radius));
    }
    glEnd();
}

void ShapeDrawer::drawRectangle(float width, Location topLeft, float height, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    glVertex2f(topLeft.getXCoord(), topLeft.getYCoord());
    glVertex2f(topLeft.getXCoord() + width, topLeft.getYCoord());
    glVertex2f(topLeft.getXCoord() + width, topLeft.getYCoord() - height);
    glVertex2f(topLeft.getXCoord(), topLeft.getYCoord() - height);
    glEnd();
}

void ShapeDrawer::drawLine(Location start, Location end, Color color) {
    glBegin(GL_LINES);
    setDrawingColor(color);
    glVertex2f(start.getXCoord(), start.getYCoord());
    glVertex2f(end.getXCoord(), end.getYCoord());
    glEnd();
}

void ShapeDrawer::updateScreen() {
    glFlush();
}

void ShapeDrawer::setDrawingColor(Color color) {
    glColor3f(colorMap[color].at(0), colorMap[color].at(1), colorMap[color].at(2));
}
