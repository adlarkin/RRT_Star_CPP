//
// Created by adlarkin on 11/5/18.
//

#include <GL/gl.h>
#include <math.h>
#include "ShapeDrawer.h"

#define PI 3.14159265359

void ShapeDrawer::drawCircle(Location center, Color color, double radius) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    for (int theta = 0; theta < 360; ++theta) {
        glVertex2f((float)(center.getXCoord() + (cos(theta*PI/180)*radius)),
                   (float)(center.getYCoord() + (sin(theta*PI/180)*radius)));
    }
    glEnd();
}

void ShapeDrawer::drawRectangle(double width, Location topLeft, double height, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    glVertex2f((float)topLeft.getXCoord(), (float)topLeft.getYCoord());
    glVertex2f((float)(topLeft.getXCoord() + width), (float)topLeft.getYCoord());
    glVertex2f((float)(topLeft.getXCoord() + width), (float)(topLeft.getYCoord() - height));
    glVertex2f((float)topLeft.getXCoord(), (float)(topLeft.getYCoord() - height));
    glEnd();
}

void ShapeDrawer::drawLine(Location start, Location end, Color color) {
    glBegin(GL_LINES);
    setDrawingColor(color);
    glVertex2f((float)start.getXCoord(), (float)start.getYCoord());
    glVertex2f((float)end.getXCoord(), (float)end.getYCoord());
    glEnd();
}

void ShapeDrawer::updateScreen() {
    glFlush();
}

void ShapeDrawer::setDrawingColor(Color color) {
    glColor3f(colorMap[color].at(0), colorMap[color].at(1), colorMap[color].at(2));
}
