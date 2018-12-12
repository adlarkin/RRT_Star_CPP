//
// Created by adlarkin on 11/5/18.
//

#include <GL/gl.h>
#include <math.h>
#include <GL/glut.h>
#include "ShapeDrawer.h"

#define PI 3.14159265359
//ShapeDrawer::ShapeDrawer(std::string title, int winHeight, int winWidth, int x_winPos, int y_winPos) {
//    // this lets the user know the min/max values for lineWidth (drawLine() method)
//    // lineWidth depends on computer drivers, so if the values are restricted, this will let the user know
//    GLfloat LineRange[2];
//    glGetFloatv(GL_LINE_WIDTH_RANGE,LineRange);
//    std::cout << "Minimum Line Width " << LineRange[0] << " -- ";
//    std::cout << "Maximum Line Width " << LineRange[1] << std::endl;
//
//    initScreen(title, winHeight, winWidth, x_winPos, y_winPos);
//}
//
//void ShapeDrawer::initScreen(std::string title, int winHeight, int winWidth, int x_winPos, int y_winPos) {
//    // need to make fake command-line arguments since we don't take anything in from the command line
//    char fakeParam[] = "fake";
//    char *fakeargv[] = { fakeParam, nullptr };
//    int fakeargc = 1;
//
//    glutInit( &fakeargc, fakeargv );
//    glutInitDisplayMode(GLUT_SINGLE);
//    glutInitWindowSize(winWidth, winHeight);
//    glutInitWindowPosition(x_winPos, y_winPos);;
//    windowID = glutCreateWindow(title.c_str());
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    // todo: call update screen here (to set it to all black)?
//}

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

void ShapeDrawer::drawLine(Location start, Location end, Color color, float lineWidth) {
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    setDrawingColor(color);
    glVertex2f((float)start.getXCoord(), (float)start.getYCoord());
    glVertex2f((float)end.getXCoord(), (float)end.getYCoord());
    glEnd();
}

void ShapeDrawer::updateScreen() {
    glFlush();
}

//void ShapeDrawer::keepScreenOpen() {
//    glutMainLoop();
//}
//
//void ShapeDrawer::deleteScreen() {
//    glutDestroyWindow(windowID);
//}

void ShapeDrawer::setDrawingColor(Color color) {
    glColor3f(colorMap[color].at(0), colorMap[color].at(1), colorMap[color].at(2));
}
