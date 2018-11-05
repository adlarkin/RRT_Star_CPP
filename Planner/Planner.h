//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include <unordered_set>
#include "../State/RobotState.h"
#include "../State/Location.h"
#include "../State/Coordinate.h"
#include "../Utils/ObjHashes.cpp"
#include "../Visualization/ShapeDrawer.h"

// needed for rTree
// boost must be installed in order for this to work:
// https://www.boost.org/doc/libs/1_68_0/more/getting_started/index.html
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<box, unsigned> value;

class Planner {
public:
    virtual ~Planner();

    Planner(int numPoints, float epsilon);
    void findBestPath();

private:
    Coordinate makeRandomCoordinate();

    RobotState* root;
    int maxIterations;
    float epsilon;
    Location start;
    Location end;

    ShapeDrawer drawer;

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::unordered_set<RobotState*> allStates;
    std::unordered_set<Location> allLocations;
};


#endif //RRT_PROJECT_PLANNER_H