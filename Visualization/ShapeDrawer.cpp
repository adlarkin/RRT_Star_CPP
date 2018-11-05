//
// Created by adlarkin on 11/5/18.
//

#include <GL/gl.h>
#include <math.h>
#include "ShapeDrawer.h"

#define PI 3.14159265

ShapeDrawer::ShapeDrawer(float radius) : radius(radius) {}

void ShapeDrawer::drawCircle(Location center, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    for (int theta = 0; theta < 360; ++theta) {
        glVertex2f(center.xPosition() + (float)cos(theta*PI/180)*radius,
                   center.yPosition() + (float)sin(theta*PI/180)*radius);
    }
    glEnd();
}

void ShapeDrawer::drawRectangle(float width, Location topLeft, float height, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    glVertex2f(topLeft.xPosition(), topLeft.yPosition());
    glVertex2f(topLeft.xPosition() + width, topLeft.yPosition());
    glVertex2f(topLeft.xPosition() + width, topLeft.yPosition() - height);
    glVertex2f(topLeft.xPosition(), topLeft.yPosition() - height);
    glEnd();
}

void ShapeDrawer::drawLine(Location start, Location end, Color color) {
    glBegin(GL_LINES);
    setDrawingColor(color);
    glVertex2f(start.xPosition(), start.yPosition());
    glVertex2f(end.xPosition(), end.yPosition());
    glEnd();
}

void ShapeDrawer::setDrawingColor(Color color) {
    glColor3f(colorMap[color].at(0), colorMap[color].at(1), colorMap[color].at(2));
}