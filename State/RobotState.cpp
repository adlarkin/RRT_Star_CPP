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
    neighbors.insert(neighborState);
}

void RobotState::removeNeighbor(RobotState *exNeighbor) {
    neighbors.erase(exNeighbor);
}

void RobotState::updateParent(RobotState *diffParent, double updatedCost) {
    this->parent->removeNeighbor(this);
    this->parent = diffParent;
    diffParent->addNeighbor(this);
    this->cost = updatedCost;
}

const std::unordered_set<RobotState *> &RobotState::getNeighbors() const {
    return neighbors;
}

bool RobotState::operator==(const RobotState &rhs) const {
    return this->location == rhs.location;
}

bool RobotState::operator!=(const RobotState &rhs) const {
    return !(rhs == *this);
}
