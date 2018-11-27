//
// Created by adlarkin on 11/9/18.
//

#include "MyRtree.h"

void MyRtree::add(RobotState *state) {
    rTree.insert(Value(state->getBoostLocation(), state));
    std::cout << "Add called. Size of the rTree is " << rTree.size() << std::endl;
}

void MyRtree::remove(RobotState *state) {
    rTree.remove(Value(state->getBoostLocation(), state));
    std::cout << "Remove called. Size of the rTree is " << rTree.size() << std::endl;
}
