#include <GL/glut.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Planner/Planner.h"
#include "Planner/DistancePlanner.h"
#include "Planner/EnergyPlanner.h"

enum PlannerType {DISTANCE, ENERGY};

int main(int argc, char** argv) {
    // define program inputs
    int winWidth = 1500;
    int winHeight = 1200;
    int x_winPos = 850;
    int y_winPos = 200;
    int numPoints = 5000;
    float epsilon = 5.0;
    PlannerType type = DISTANCE;

    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    // set up the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(x_winPos, y_winPos);
    int windowID = glutCreateWindow("RRT* Planner");
    glClear(GL_COLOR_BUFFER_BIT);

    // run the planner
    Planner* planner;
    switch (type) {
        case ENERGY:
            planner = new EnergyPlanner(numPoints, epsilon);
            break;
        default:
            planner = new DistancePlanner(numPoints, epsilon);
            break;
    }
    planner->findBestPath();
    delete planner;
    planner = nullptr;

    // keep the display open
    // closes when the user clicks the GUI's 'x' button
    glutMainLoop();

    glutDestroyWindow(windowID);

    return 0;
}