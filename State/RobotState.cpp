//
// Created by adlarkin on 10/29/18.
//

#include "RobotState.h"

RobotState::RobotState(RobotState *parent, const Location &location) :
        parent(parent), location(location) {
    this->cost = 0;
}