//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_ROBOTSTATE_H
#define RRT_PROJECT_ROBOTSTATE_H

#include <set>
#include "Location.h"

class RobotState {
public:
    RobotState(RobotState *parent, const Location &location);
    RobotState *getParent() const;
    const Location &getLocation() const;
    double getCost() const;
    void setCost(double cost);
    void addNeighbor(RobotState* neighborState);
    void updateParent(RobotState *diffParent, double updatedCost);
    const std::vector<RobotState *> &getNeighbors() const;

    bool operator==(const RobotState &rhs) const;
    bool operator!=(const RobotState &rhs) const;
private:
    RobotState* parent;
    std::vector<RobotState*> neighbors;
    Location location;
    double cost;
};


#endif //RRT_PROJECT_ROBOTSTATE_H