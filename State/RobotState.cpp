//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location) :
        parent(parent), location(location) {
    this->cost = 0;
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
