//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include <set>
#include <chrono>
#include <thread>

#define RADIUS .0085
#define START_COLOR GREEN
#define END_COLOR RED
#define LINE_COLOR WHITE
#define PATH_COLOR LIGHT_BLUE

// initializer lists init objects based on the order they're declared in the .h file
// sets must be initialized first in order for makeUniqueLocation() to work
Planner::Planner(int numPoints, double epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeUniqueLocation()),
        end(makeUniqueLocation()),
        drawer() {
    this->root = createNewState(nullptr, this->start);  // the root state has no parent
    drawer.updateScreen();  // this opens up an openGL screen with a black background
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, START_COLOR, RADIUS);
    drawer.drawCircle(end, END_COLOR, RADIUS);
    drawer.updateScreen();
    pauseAnimation(500);    // let the user see the start and end points

    while (allStates.size() < maxIterations) {
        Location sampledLoc = makeUniqueLocation();
        RobotState* nearest = rTree.getNearestElement(sampledLoc);
        if (euclideanDistance(nearest->getLocation(), sampledLoc) > epsilon) {
            sampledLoc = makeLocationWithinEpsilon(nearest, sampledLoc);
        }
        RobotState* nextState = createNewState(nearest, sampledLoc);
        drawer.drawLine(nearest->getLocation(), nextState->getLocation(), LINE_COLOR);
        drawer.updateScreen();
        if (foundPath(nextState)) {
            displayPath(nextState);
            break;
        }
    }
}

double Planner::euclideanDistance(Location start, Location end) {
    double xDiff = end.getXCoord() - start.getXCoord();
    double yDiff = end.getYCoord() - start.getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
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
    allLocations.erase(location);   // remove the location outside of epsilon since it's not valid
    double yDiff = location.getYCoord() - nearest->getLocation().getYCoord();
    double xDiff = location.getXCoord() - nearest->getLocation().getXCoord();
    double theta = atan2(yDiff, xDiff);    // in radians
    double xCoord = nearest->getLocation().getXCoord() + (epsilon * cos(theta));
    double yCoord = nearest->getLocation().getYCoord() + (epsilon * sin(theta));
    Location updatedLocation(xCoord, yCoord, maxIterations);
    allLocations.insert(updatedLocation);
    return updatedLocation;
}

RobotState *Planner::createNewState(RobotState *parent, Location location) {
    auto nextState = new RobotState(parent, location);
    // the root state has a cost of 0
    nextState->setCost(0);
    // if nextState is not the root state, adjust the cost accordingly
    if (parent != nullptr) {
        nextState->setCost(parent->getCost() + cost(parent, nextState));
        parent->addNeighbor(nextState);
    }
    allStates.push_back(nextState);
    rTree.add(nextState);
    return nextState;
}

bool Planner::foundPath(RobotState *mostRecentState) {
    if (euclideanDistance(mostRecentState->getLocation(), end) <= epsilon) {
        return true;
    }
    return false;
}

void Planner::displayPath(RobotState *lastState) {
    while (lastState != root) {
        RobotState* next = lastState->getParent();
        drawer.drawLine(lastState->getLocation(), next->getLocation(), PATH_COLOR, 5.0f);
        lastState = next;
    }
    // redraw the start/end points so that the path doesn't display over them
    drawer.drawCircle(start, START_COLOR, RADIUS);
    drawer.drawCircle(end, END_COLOR, RADIUS);
    drawer.updateScreen();
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
