//
// Created by adlarkin on 11/9/18.
//

#ifndef RRT_STAR_CPP_MYRTREE_H
#define RRT_STAR_CPP_MYRTREE_H

// boost must be installed in order for this to work:
// https://www.boost.org/doc/libs/1_68_0/more/getting_started/index.html
#include <boost/geometry.hpp>
//#include <boost/geometry/geometries/point.hpp>
//#include <boost/geometry/geometries/box.hpp
#include <boost/geometry/index/rtree.hpp>
#include "../State/Location.h"      // defines 'BoostPoint'
#include "../State/RobotState.h"    // defines 'RobotState'

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
//typedef bg::model::BoostPoint<float, 2, bg::cs::cartesian> BoostPoint;
//typedef bg::model::box<BoostPoint> box;
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
private:
    Rtree rTree;
};


#endif //RRT_STAR_CPP_MYRTREE_H
