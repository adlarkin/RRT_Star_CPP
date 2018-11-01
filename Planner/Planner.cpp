//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include "../State/Coordinate.h"
#include <set>
#include <chrono>
#include <thread>

Planner::Planner(int numPoints, float epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeRandomCoordinate(), makeRandomCoordinate()),
        end(makeRandomCoordinate(), makeRandomCoordinate()) {

    this->root = new RobotState(nullptr, this->start);  // the root state has no parent

    this->allStates.insert(root);
    this->allLocations.insert(&this->start);
    this->allLocations.insert(&this->end);
}

void Planner::print() {

    // draw the start and end points
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    float r = .02;
    glVertex2f(start.xPosition()-r, start.yPosition());
    glVertex2f(start.xPosition(), start.yPosition()-r);
    glVertex2f(start.xPosition()+r, start.yPosition());
    glVertex2f(start.xPosition(), start.yPosition()+r);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(end.xPosition()-r, end.yPosition());
    glVertex2f(end.xPosition(), end.yPosition()-r);
    glVertex2f(end.xPosition()+r, end.yPosition());
    glVertex2f(end.xPosition(), end.yPosition()+r);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(start.xPosition(), start.yPosition());
    glVertex2f(end.xPosition(), end.yPosition());
    glEnd();
    glFlush();

    // wait half a second before showing the next line
    std::chrono::milliseconds waitTime(500);
    std::this_thread::sleep_for(waitTime);

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, .5);
    glEnd();
    glFlush();

    std::cout << start.xPosition() << ", " << start.yPosition() << std::endl;
    std::cout << end.xPosition() << ", " << end.yPosition() << std::endl << std::endl << std::endl;

    std::cout << start.xID() << ", " << start.yID() << std::endl;
    std::cout << end.xID() << ", " << end.yID() << std::endl;
}

Coordinate Planner::makeRandomCoordinate() {
    int pointRange = 2 * this->maxIterations;

    // make a number between 0 and pointRange, exclusive
    // this number is the id of the coordinate
    // (using int IDs to compare with other coordinates for duplicates)
    int id = rand() % pointRange;

    /*
     * turn this number into a float between -1 and 1 (needed for openGL)
     * this is done the following way:
     * 1) divide id by pointRange
     *    this will give a float between 0 and 1
     * 2) multiply this new float by 2 to get a float between 0 and 2
     * 3) subtract 1 from it to get a float between -1 and 1
     */
    float pos = (((float)id / pointRange) * 2) - 1;

    return Coordinate{id, pos};
}

Planner::~Planner() {
    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}