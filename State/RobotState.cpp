//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location) :
        parent(parent),
        location(location)
        {}

RobotState *RobotState::getParent() const {
    return parent;
}

const Location &RobotState::getLocation() const {
    return location;
}

double RobotState::getCost() const {
    return cost;
}

void RobotState::setCost(double cost) {
    RobotState::cost = cost;
}

void RobotState::addNeighbor(RobotState* neighborState) {
    neighbors.push_back(neighborState);
}

void RobotState::updateParent(RobotState *diffParent, double updatedCost) {
    this->parent = diffParent;
    this->cost = updatedCost;
}

bool RobotState::operator==(const RobotState &rhs) const {
    return this->location == rhs.location;
}

bool RobotState::operator!=(const RobotState &rhs) const {
    return !(rhs == *this);
}
