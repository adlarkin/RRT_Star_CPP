//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_ROBOTSTATE_H
#define RRT_PROJECT_ROBOTSTATE_H

#include <set>
#include "Location.h"

class RobotState {
public:
    RobotState(RobotState *parent, const Location &location, size_t id);
    BoostPoint getBoostLocation();
    const Location &getLocation() const;
    int getCost() const;
    void setCost(int cost);

    bool operator==(const RobotState &rhs) const;
    bool operator!=(const RobotState &rhs) const;
private:
    RobotState* parent;
    std::set<RobotState*> neighbors;
    Location location;
    int cost;
    size_t id;
};


#endif //RRT_PROJECT_ROBOTSTATE_H