#include <string>
#include <iostream>
#include "Planner/Planner.h"
#include "Planner/DistancePlanner.h"
#include "Planner/EnergyPlanner.h"
#include "Utils/StringParser.h"

enum PlannerType {DISTANCE, ENERGY};

// TODO find out how to see which included libraries are unused? (code cleanup)

int main(int argc, char** argv) {
    // define program inputs (from the commandLine)
    int x_winPos, y_winPos, winWidth, winHeight, neighborhoodSize;
    size_t numPoints;
    auto testSeed = (unsigned int)time(nullptr);
    double epsilon, knnNeighborhoodRadiusFactor;
    PlannerType plannerType;

    // parse the command line inputs and initialize the variables
    int minNumArgs = 10;
    int maxNumArgs = 11;
    try {
        if ((argc < minNumArgs) || (argc > maxNumArgs)) {
            throw argc;
        }
        StringParser parser;
        x_winPos = parser.parseInt(argv[1]);
        y_winPos = parser.parseInt(argv[2]);
        winWidth = parser.parseInt(argv[3]);
        winHeight = parser.parseInt(argv[4]);
        numPoints = parser.parseSizeT(argv[5]);
        epsilon = parser.parseDouble(argv[6]);
        std::string inputType = parser.toLowerCase(argv[7]);
        if (inputType == "energy") {
            plannerType = ENERGY;
        } else if (inputType == "distance") {
            plannerType = DISTANCE;
        } else {
            throw inputType;
        }
        neighborhoodSize = parser.parseInt(argv[8]);
        knnNeighborhoodRadiusFactor = parser.parseDouble(argv[9]);
        if (argc == maxNumArgs) {
            testSeed = (unsigned int)parser.parseInt(argv[10]);
            std::cout << "using the INPUT seed, " << testSeed << "..." << std::endl;
        } else {
            std::cout << "using a RANDOM seed, " << testSeed << "..." << std::endl;
        }
    } catch (int invalidNumOfParams) {
        std::cerr << "Invalid number of arguments passed in. ";
        std::cerr << "You passed in " << argc << " argument(s)." << std::endl;
        std::cerr << "Must have " << minNumArgs << " (or " << maxNumArgs << ") arguments passed in:" << std::endl;
        std::cerr << "executable x_winPos y_winPos winWidth winHeight numPoints epsilon plannerType ";
        std::cerr << "neighborhoodSize knnNeighborhoodRadiusFactor testSeed" << std::endl;
        std::cerr << "(the 'testSeed' parameter is optional)" << std::endl;
        return 1;
    } catch (std::string &invalidPlannerType) {
        std::cerr << "invalid planner type was passed in" << std::endl;
        std::cerr << "you passed in '" << invalidPlannerType << "' (in lowercase)" << std::endl;
        std::cerr << "you must pass in either 'distance' or 'energy'" << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "some other error occurred!" << std::endl;
        return 1;
    }

    std::string title = "RRT* Planner";
    WindowParamsDTO screenParams(winWidth, winHeight, x_winPos, y_winPos, title);

    // need this to generate random locations throughout the program
    srand(testSeed);

    // run the planner
    Planner* planner;
    switch (plannerType) {
        case ENERGY:
            std::cout << "using the ENERGY planner..." << std::endl;
            planner = new EnergyPlanner(screenParams, numPoints, epsilon, neighborhoodSize,
                    knnNeighborhoodRadiusFactor);
            break;
        default:
            std::cout << "using the DISTANCE planner..." << std::endl;
            planner = new DistancePlanner(screenParams, numPoints, epsilon, neighborhoodSize,
                    knnNeighborhoodRadiusFactor);
            break;
    }
    planner->findBestPath();

    delete planner;
    planner = nullptr;

    return 0;
}
