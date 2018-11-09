//
// Created by adlarkin on 11/9/18.
//

#include "MyRtree.h"

void MyRtree::add(RobotState *state) {
    rtree.insert(Value(state->getBoostLocation(), state));
}
