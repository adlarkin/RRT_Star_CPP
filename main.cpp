#include <GL/glut.h>
#include <string>
#include "Planner/Planner.h"

int main(int argc, char** argv)
{
    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    // define program inputs
    int winWidth = 900;
    int winHeight = 700;
    int x_winPos = 400;
    int y_winPos = 150;
    int numPoints = 5000;
    float epsilon = 5.0;

    // set up the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(x_winPos, y_winPos);
    glutCreateWindow("RRT* Planner");
    glClear(GL_COLOR_BUFFER_BIT);

    // run the planner
    Planner planner = Planner(numPoints, epsilon);
    planner.print();

    // keep the display open
    // closes when the user clicks the GUI's 'x' button
    glutMainLoop();
    return 0;
}