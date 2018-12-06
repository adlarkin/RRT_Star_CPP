//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location) :
        parent(parent),
        location(location)
        {}

BoostPoint RobotState::getBoostLocation() {
    return location.getBoostPoint();
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

bool RobotState::operator==(const RobotState &rhs) const {
    return this->location == rhs.location;
}

bool RobotState::operator!=(const RobotState &rhs) const {
    return !(rhs == *this);
}

void RobotState::addNeighbor(RobotState* neighborState) {
    neighbors.push_back(neighborState);
}
