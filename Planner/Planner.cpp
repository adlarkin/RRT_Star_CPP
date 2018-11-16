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

    this->root = new RobotState(nullptr, this->start);  // the root state has no parent
    this->allStates.insert(root);

    // NOT WORRYING ABOUT CHECKING FOR DUPLICATE LOCATIONS RIGHT NOW
//    // ensure that the start and end are different
//    while (this->start == this->end) {
//        this->end = Location(maxIterations);
//    }
//    this->allLocations.insert(this->start);
//    this->allLocations.insert(this->end);

    rtree.add(root);
    drawer.updateScreen();  // this opens up an openGL screen with a black background
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, GREEN);
    drawer.drawCircle(end, BLUE);

    drawer.drawLine(start, end);
    drawer.drawRectangle(.3f, start, .1f);
    drawer.updateScreen();

    // wait half a second before showing the next line
    std::chrono::milliseconds waitTime(500);
    std::this_thread::sleep_for(waitTime);

    drawer.drawLine(Location(maxIterations),
            Location(maxIterations));
    drawer.updateScreen();

    // sometimes, the end BoostPoint is in the rectangle
    // redrawing the end BoostPoint to make sure it's not off the screen (this is for testing)
    drawer.drawCircle(end, BLUE);
    drawer.updateScreen();

//    std::cout << "Start: " << start.getXCoord() << " , " << start.getYCoord() << std::endl;
//    std::cout << "End: " << end.getXCoord() << " , " << end.getYCoord() << std::endl;

    int iterations = 0;
    while (allStates.size() < maxIterations) {
        // todo: write the rrt* code here (use rTree?)
        // todo: no obstacles first. add obstacles after the planner works w/o them
        break;
    }
}

Planner::~Planner() {
    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}
