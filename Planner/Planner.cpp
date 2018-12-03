//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include <set>
#include <chrono>
#include <thread>

// initializer lists init objects based on the order they're declared in the .h file
// sets must be initialized first in order for makeUniqueLocation() to work
Planner::Planner(int numPoints, float epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeUniqueLocation()),
        end(makeUniqueLocation()),
        // the constructor for the shape drawer takes in a radius (for drawing circles)
        drawer(.0125) {
    this->root = createNewState(nullptr, this->start);  // the root state has no parent
    drawer.updateScreen();  // this opens up an openGL screen with a black background
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, GREEN);
    drawer.drawCircle(end, BLUE);
    drawer.updateScreen();

//    randomTestCode();   // todo: delete this later

//    int iterations = 0;
    while (allStates.size() < maxIterations) {
        // todo: write the rrt* code here (use rTree?)
        // todo: no obstacles first. add obstacles after the planner works w/o them
        Location sampledLoc = makeUniqueLocation();
        RobotState* nearest = rTree.getNearestElement(sampledLoc);
//        std::cout << "generated location is" << sampledLoc.getXCoord() << ", " << sampledLoc.getYCoord();
//        std::cout << std::endl << "rTree nearest query location is " << nearest->getLocation().getXCoord();
//        std::cout << ", " << nearest->getLocation().getYCoord() << std::endl;
        if (euclideanDistance(nearest->getLocation(), sampledLoc) > epsilon) {
            sampledLoc = makeLocationWithinEpsilon(nearest, sampledLoc);
        }
        // todo: the rest of loop (making a new state, making connections, updating animation)
        break;
    }
}

Location Planner::makeUniqueLocation() {
    Location location(maxIterations);
    while (allLocations.count(location)) {
        location = Location(maxIterations);
    }
    allLocations.insert(location);
    return location;
}

Location Planner::makeLocationWithinEpsilon(RobotState *nearest, Location location) {
    allLocations.erase(location);
    // todo: make a new location based off of nearest, add it to allLocations, return it
    // (this probably requires another constructor for location that takes in x,y)
    double yDiff = location.getYCoord() - nearest->getLocation().getYCoord();
    double xDiff = location.getXCoord() - nearest->getLocation().getXCoord();
    double theta = atan2(yDiff, xDiff);    // in radians
    double xCoord = epsilon * cos(theta);
    double yCoord = epsilon * sin(theta);
    // todo: how to make the new xID and yID given a coord? (usually, the coord comes from the ID)
    return Location(0);
}

RobotState *Planner::createNewState(RobotState *parent, Location location) {
    auto nextState = new RobotState(parent, location);
    allStates.push_back(nextState);
    rTree.add(nextState);
    return nextState;
}

double Planner::euclideanDistance(Location start, Location end) {
    double xDiff = end.getXCoord() - start.getXCoord();
    double yDiff = end.getYCoord() - start.getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
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

    drawer.drawLine(makeUniqueLocation(), makeUniqueLocation());
    drawer.updateScreen();

    // sometimes, the end point is in the rectangle
    // redrawing the end point to make sure it's not off the screen (this is for testing)
    drawer.drawCircle(end, BLUE);
    drawer.updateScreen();

    double testCost = cost(root, createNewState(nullptr, this->end));
    std::cout << "Cost from start to end is " << testCost << std::endl;
    std::cout << "size of allStates vector is " << allStates.size() << std::endl;
    std::cout << "size of allLocations set is " << allLocations.size() << std::endl;
}
