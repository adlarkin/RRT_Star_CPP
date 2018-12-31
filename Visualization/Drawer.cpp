//
// Created by adlarkin on 11/5/18.
//

#include <GL/gl.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "Drawer.h"

#define PI 3.14159265359

Drawer::Drawer(WindowParamsDTO screenParams) {
    // this lets the user know the min/max values for lineWidth (used in the drawLine() method)
    // lineWidth depends on computer drivers, so if the values are restricted, this will let the user know
    GLfloat LineRange[2];
    glGetFloatv(GL_LINE_WIDTH_RANGE,LineRange);
    std::cout << "Minimum Line Width " << LineRange[0] << " -- ";
    std::cout << "Maximum Line Width " << LineRange[1] << std::endl;

    initScreen(screenParams);
}

void Drawer::initScreen(WindowParamsDTO screenParams) {
    // need to make fake command-line arguments since we don't take anything in from the command line
    char fakeParam[] = "fake";
    char *fakeArgv[] = { fakeParam, nullptr };
    int fakeArgc = 1;

    glutInit( &fakeArgc, fakeArgv );
    glutInitDisplayMode(GLUT_DOUBLE);   // double buffer works well with dedicated graphics cards
    glutInitWindowSize(screenParams.getWinWidth(), screenParams.getWinHeight());
    glutInitWindowPosition(screenParams.getX_winPos(), screenParams.getY_winPos());
    windowID = glutCreateWindow(screenParams.getTitle().c_str());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    updateScreen(); // displaying a blank, all black window now that everything has been set up
}

void Drawer::drawCircle(Location center, Color color, double radius) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    for (int theta = 0; theta < 360; ++theta) {
        glVertex2f((float)(center.getXCoord() + (cos(theta*PI/180)*radius)),
                   (float)(center.getYCoord() + (sin(theta*PI/180)*radius)));
    }
    glEnd();
}

void Drawer::drawRectangle(double width, Location topLeft, double height, Color color) {
    glBegin(GL_POLYGON);
    setDrawingColor(color);
    glVertex2f((float)topLeft.getXCoord(), (float)topLeft.getYCoord());
    glVertex2f((float)(topLeft.getXCoord() + width), (float)topLeft.getYCoord());
    glVertex2f((float)(topLeft.getXCoord() + width), (float)(topLeft.getYCoord() - height));
    glVertex2f((float)topLeft.getXCoord(), (float)(topLeft.getYCoord() - height));
    glEnd();
}

void Drawer::drawLine(Location start, Location end, Color color, float lineWidth) {
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    setDrawingColor(color);
    glVertex2f((float)start.getXCoord(), (float)start.getYCoord());
    glVertex2f((float)end.getXCoord(), (float)end.getYCoord());
    glEnd();
}

void Drawer::updateScreen() {
    // doing this instead of glFlush()/glFinish() since a double duffer implementation is used (see link in README)
    glutSwapBuffers();
}

void Drawer::clearScreen() {
    // resetting the screen to be blank and black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    updateScreen();
}

void Drawer::keepScreenOpen() {
    glutMainLoop();
}

void Drawer::deleteScreen() {
    glutDestroyWindow(windowID);
}

void Drawer::setDrawingColor(Color color) {
    glColor3f(colorMap[color].at(0), colorMap[color].at(1), colorMap[color].at(2));
}
