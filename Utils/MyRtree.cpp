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
    std::vector<Value> queryResults;
    rTree.query(bgi::nearest(getBoostLocation(location), 1), back_inserter(queryResults));
    return queryResults[0].second;
}

std::vector<RobotState *> MyRtree::getNeighborhoodElements(Location center, double neighborhoodRadius) {
    std::vector<Value> queryResults;
    // user-defined unary predicate is needed to query the rTree...
    // https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/spatial_indexes/queries.html
    rTree.query(bgi::satisfies([&](Value const& v) {
        return bg::distance(v.first, getBoostLocation(center)) <= neighborhoodRadius; }),
             std::back_inserter(queryResults));
    std::vector<RobotState*> neighboringStates;
    for (auto pair : queryResults) {
        neighboringStates.push_back(pair.second);
    }
    return neighboringStates;
}

size_t MyRtree::getSize() {
    return rTree.size();
}

BoostPoint MyRtree::getBoostLocation(Location location) {
    return BoostPoint{location.getXCoord(), location.getYCoord()};
}
