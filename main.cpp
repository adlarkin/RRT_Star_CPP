//#include <GL/glut.h>
#include <string>
#include <iostream>
//#include <assert.h>
#include "Planner/Planner.h"
#include "Planner/DistancePlanner.h"
#include "Planner/EnergyPlanner.h"

enum PlannerType {DISTANCE, ENERGY};

// TODO find out how to see which included libraries are unused? (code cleanup)

int main(int argc, char** argv) {
    // define program inputs (from the commandLine)
    // todo: figure out how to turn strings to ints in c++
    // todo: make all variables below command line arguments
    int winWidth = 1500;
    int winHeight = 1200;
    int x_winPos = 850;
    int y_winPos = 200;
    std::string title = "RRT* Planner";
    PlannerType type = DISTANCE;
    WindowParamsDTO screenParams(winWidth, winHeight, x_winPos, y_winPos, title);
    int numPoints = 5000;
    double epsilon = .025;

    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    // run the planner
    Planner* planner;
    switch (type) {
        case ENERGY:
            planner = new EnergyPlanner(screenParams, numPoints, epsilon);
            break;
        default:
            planner = new DistancePlanner(screenParams, numPoints, epsilon);
            break;
    }
    planner->findBestPath();

    delete planner;
    planner = nullptr;
    return 0;
}