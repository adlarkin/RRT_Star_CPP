//
// Created by adlarkin on 11/9/18.
//

#include "MyRtree.h"

void MyRtree::add(RobotState *state) {
    rTree.insert(Value(getBoostLocation(state->getLocation()), state));
//    std::cout << "Add called. Size of the rTree is " << rTree.size() << std::endl;
}

void MyRtree::remove(RobotState *state) {
    rTree.remove(Value(getBoostLocation(state->getLocation()), state));
//    std::cout << "Remove called. Size of the rTree is " << rTree.size() << std::endl;
}

RobotState *MyRtree::getNearestElement(Location location) {
    std::vector<Value> rTreeQueryResults;
    rTree.query(bgi::nearest(getBoostLocation(location), 1), back_inserter(rTreeQueryResults));
    return rTreeQueryResults[0].second;
}

size_t MyRtree::getSize() {
    return rTree.size();
}

BoostPoint MyRtree::getBoostLocation(Location location) {
    return BoostPoint{location.getXCoord(), location.getYCoord()};
}
