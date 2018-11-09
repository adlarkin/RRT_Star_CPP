#include <GL/glut.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Planner/Planner.h"

int main(int argc, char** argv) {
    // define program inputs
    int winWidth = 900;
    int winHeight = 700;
    int x_winPos = 400;
    int y_winPos = 150;
    int numPoints = 5000;
    float epsilon = 5.0;

    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    // set up the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(x_winPos, y_winPos);
    glutCreateWindow("RRT* Planner");
    glClear(GL_COLOR_BUFFER_BIT);

    // run the planner
    Planner planner(numPoints, epsilon);
    planner.findBestPath();

    // keep the display open
    // closes when the user clicks the GUI's 'x' button
    glutMainLoop(); // todo: comment this line out if you want to test with valgrind

    return 0;
}