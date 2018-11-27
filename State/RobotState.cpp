//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location, size_t id) :
        parent(parent), location(location) {
    this->cost = 0;
    this->id = id;
}

BoostPoint RobotState::getBoostLocation() {
    return location.getBoostPoint();
}

const Location &RobotState::getLocation() const {
    return location;
}

int RobotState::getCost() const {
    return cost;
}

void RobotState::setCost(int cost) {
    RobotState::cost = cost;
}

bool RobotState::operator==(const RobotState &rhs) const {
    return id == rhs.id;
}

bool RobotState::operator!=(const RobotState &rhs) const {
    return !(rhs == *this);
}
