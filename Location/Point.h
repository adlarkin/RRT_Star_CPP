//
// Created by adlarkin on 11/16/18.
//

#ifndef RRT_STAR_CPP_POINT_H
#define RRT_STAR_CPP_POINT_H


class Point {
public:
    Point(int ID, double coordinate);
    Point(const Point &p2);

    int getID() const;

    void setID(int ID);

    double getCoordinate() const;

    void setCoordinate(double coordinate);

private:
    int ID; // for obstacle hashing
    double coordinate;
};


#endif //RRT_STAR_CPP_POINT_H
