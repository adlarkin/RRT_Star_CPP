//
// Created by adlarkin on 11/16/18.
//

#ifndef RRT_STAR_CPP_POINT_H
#define RRT_STAR_CPP_POINT_H


class Point {
public:
    Point(int ID, float coordinate);
    Point(const Point &p2);

    int getID() const;

    void setID(int ID);

    float getCoordinate() const;

    void setCoordinate(float coordinate);

private:
    int ID; // for obstacle hash
    float coordinate;
};


#endif //RRT_STAR_CPP_POINT_H
