//#include <GL/glut.h>
#include <string>
#include <iostream>
//#include <assert.h>
#include "Planner/Planner.h"
#include "Planner/DistancePlanner.h"
#include "Planner/EnergyPlanner.h"
#include "Utils/StringParser.h"

enum PlannerType {DISTANCE, ENERGY};

// TODO find out how to see which included libraries are unused? (code cleanup)

int main(int argc, char** argv) {
    // define program inputs (from the commandLine)
    int x_winPos, y_winPos, winWidth, winHeight, numPoints;
    double epsilon;
    PlannerType plannerType;

    // parse the command line inputs and initialize the variables
    try {
        if (argc != 8) {
            throw argc;
        }
        StringParser parser;
        x_winPos = parser.parseInt(argv[1]);
        y_winPos = parser.parseInt(argv[2]);
        winWidth = parser.parseInt(argv[3]);
        winHeight = parser.parseInt(argv[4]);
        numPoints = parser.parseInt(argv[5]);
        epsilon = parser.parseDouble(argv[6]);
        std::string inputType = parser.toLowerCase(argv[7]);
        if (inputType == "energy") {
            plannerType = ENERGY;
        } else {
            plannerType = DISTANCE;
        }
    } catch (int invalidNumOfParams) {
        std::cerr << "Invalid number of arguments passed in. ";
        std::cerr << "You passed in " << argc << " argument(s)." << std::endl;
        std::cerr << "Must have 8 arguments passed in ";
        std::cerr << "(executable x_winPos y_winPos winWidth winHeight numPoints epsilon plannerType).";
        std::cerr << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "some other error occurred!" << std::endl;
        return 1;
    }

    std::string title = "RRT* Planner";
    WindowParamsDTO screenParams(winWidth, winHeight, x_winPos, y_winPos, title);

    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    // run the planner
    Planner* planner;
    switch (plannerType) {
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
