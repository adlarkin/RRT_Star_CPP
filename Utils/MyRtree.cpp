//
// Created by adlarkin on 11/9/18.
//

#include "MyRtree.h"

void MyRtree::add(RobotState *state) {
    rTree.insert(Value(state->getBoostLocation(), state));
//    std::cout << "Add called. Size of the rTree is " << rTree.size() << std::endl;
}

void MyRtree::remove(RobotState *state) {
    rTree.remove(Value(state->getBoostLocation(), state));
//    std::cout << "Remove called. Size of the rTree is " << rTree.size() << std::endl;
}

RobotState *MyRtree::getNearestElement(Location location) {
    std::vector<Value> rTreeQueryResults;
    rTree.query(bgi::nearest(location.getBoostPoint(), 1), back_inserter(rTreeQueryResults));
    return rTreeQueryResults[0].second;
}

size_t MyRtree::getSize() {
    return rTree.size();
}

//shared_ptr<EnergyNode> RrtPlanner::getNearestNode(Coord coord) {
//    vector<RtreeValue> rtreeQueryResults;
//    myRtree.query(bgi::nearest(coord.getBoostPoint(), 1), back_inserter(rtreeQueryResults));
//
//    return rtreeQueryResults[0].second; // return the nearest node
//}
