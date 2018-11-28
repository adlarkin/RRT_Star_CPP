//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include <set>
#include <chrono>
#include <thread>

Planner::Planner(int numPoints, float epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(maxIterations),
        end(maxIterations),
        // the constructor for the shape drawer takes in a radius (for drawing circles)
        drawer(.0125) {

    this->root = createNewState(nullptr, this->start);  // the root state has no parent

    // NOT WORRYING ABOUT CHECKING FOR DUPLICATE LOCATIONS RIGHT NOW
//    // ensure that the start and end are different
//    while (this->start == this->end) {
//        this->end = Location(maxIterations);
//    }
//    this->allLocations.insert(this->start);
//    this->allLocations.insert(this->end);

    drawer.updateScreen();  // this opens up an openGL screen with a black background
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, GREEN);
    drawer.drawCircle(end, BLUE);

    randomTestCode();   // todo: delete this later

    int iterations = 0;
    while (allStates.size() < maxIterations) {
        // todo: write the rrt* code here (use rTree?)
        // todo: no obstacles first. add obstacles after the planner works w/o them
        break;
    }
}

RobotState *Planner::createNewState(RobotState *parent, Location location) {
    // size of allStates BEFORE the state creation is the ID of the newly created robot state
    // (ID starts at 0)
    auto nextState = new RobotState(parent, location, allStates.size());
    allStates.insert(nextState);
    rTree.add(nextState);
    return nextState;
}

void Planner::pauseAnimation(int milliSec) {
    // wait for a num. of milliseconds before doing the next thing
    std::chrono::milliseconds waitTime(milliSec);
    std::this_thread::sleep_for(waitTime);
}

Planner::~Planner() {
    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}

void Planner::randomTestCode() {
    drawer.drawLine(start, end);
    drawer.drawRectangle(.3f, start, .1f);
    drawer.updateScreen();

    pauseAnimation(500);

    drawer.drawLine(Location(maxIterations), Location(maxIterations));
    drawer.updateScreen();

    // sometimes, the end point is in the rectangle
    // redrawing the end point to make sure it's not off the screen (this is for testing)
    drawer.drawCircle(end, BLUE);
    drawer.updateScreen();

    double testCost = cost(root, createNewState(nullptr, this->end));
    std::cout << "Cost from start to end is ";
    std:: cout << testCost << std::endl;

//    std::cout << "Start: " << start.getXCoord() << " , " << start.getYCoord() << std::endl;
//    std::cout << "End: " << end.getXCoord() << " , " << end.getYCoord() << std::endl;

    // testing the r tree
}
