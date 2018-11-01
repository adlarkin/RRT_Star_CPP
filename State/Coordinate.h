//
// Created by adlarkin on 10/31/18.
//

#ifndef RRT_PROJECT_COORDINATE_H
#define RRT_PROJECT_COORDINATE_H


class Coordinate {
public:
    Coordinate(int id, float pos);

    bool operator==(const Coordinate &rhs) const;
    bool operator!=(const Coordinate &rhs) const;

    int getId() const;

    void setId(int id);

    float getPos() const;

    void setPos(float pos);

private:
    int id;
    float pos;
};


#endif //RRT_PROJECT_COORDINATE_H