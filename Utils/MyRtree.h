//
// Created by adlarkin on 11/9/18.
//

#ifndef RRT_STAR_CPP_MYRTREE_H
#define RRT_STAR_CPP_MYRTREE_H

// boost must be installed in order for this to work (view README for download info)
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "../State/Location.h"
#include "../State/RobotState.h"

// setting up the rTree so that it can be wrapped for simplicity
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
typedef bg::model::point<double, 2, boost::geometry::cs::cartesian> BoostPoint;
typedef std::pair<BoostPoint, RobotState*> Value;
// need to override the rTree equality operator (used when removing from rTree)
struct equal_to {
    bool operator()(Value const& v1, Value const& v2) const {
        return bg::equals(v1.first, v2.first) &&
            v1.second == v2.second;
    }
};
typedef bgi::rtree<Value, bgi::rstar<16>, bgi::indexable<Value>, equal_to> Rtree;

class MyRtree {
public:
    void add(RobotState *state);
    void remove(RobotState *state);
    RobotState* getNearestElement(Location location);
    std::vector<RobotState*> getNeighboringElements(Location center, double neighborhoodRadius);
    std::vector<RobotState *> getKNearestNeighbors(Location center, int k, double neighborhoodRadius);
    size_t getSize();
private:
    BoostPoint getBoostLocation(Location location);

    Rtree rTree;
};


#endif //RRT_STAR_CPP_MYRTREE_H
