//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location, size_t cost) :
        parent(parent),
        location(location),
        cost(cost) {}

BoostPoint RobotState::getBoostLocation() {
    return location.getBoostPoint();
}

const Location &RobotState::getLocation() const {
    return location;
}

size_t RobotState::getCost() const {
    return cost;
}

void RobotState::setCost(size_t cost) {
    RobotState::cost = cost;
}

bool RobotState::operator==(const RobotState &rhs) const {
    return this->location == rhs.location;
}

bool RobotState::operator!=(const RobotState &rhs) const {
    return !(rhs == *this);
}
