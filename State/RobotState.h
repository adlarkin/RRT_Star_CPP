//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_ROBOTSTATE_H
#define RRT_PROJECT_ROBOTSTATE_H

#include <set>
#include "Location.h"

class RobotState {
public:
    RobotState(RobotState *parent, const Location &location, size_t cost = 0);
    BoostPoint getBoostLocation();
    const Location &getLocation() const;
    size_t getCost() const;
    void setCost(size_t cost);

    bool operator==(const RobotState &rhs) const;
    bool operator!=(const RobotState &rhs) const;
private:
    RobotState* parent;
    std::vector<RobotState*> neighbors;
    Location location;
    size_t cost;
};


#endif //RRT_PROJECT_ROBOTSTATE_H