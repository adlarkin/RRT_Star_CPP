#include <GL/glut.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Planner/Planner.h"

// methods for testing
void testLocationDuplicates();

int main(int argc, char** argv) {
    // define program inputs
    int winWidth = 900;
    int winHeight = 700;
    int x_winPos = 400;
    int y_winPos = 150;
    int numPoints = 5000;
    float epsilon = 5.0;
    bool runTests = false;

    // needed this to generate random locations throughout the program
    srand(time(nullptr));

    if (runTests) {
        testLocationDuplicates();
    }

    // set up the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(x_winPos, y_winPos);
    glutCreateWindow("RRT* Planner");
    glClear(GL_COLOR_BUFFER_BIT);

    // run the planner
    Planner planner(numPoints, epsilon);
    planner.findBestPath();

    // keep the display open
    // closes when the user clicks the GUI's 'x' button
    glutMainLoop(); // todo: comment this line out if you want to test with valgrind

    return 0;
}


void testLocationDuplicates() {
    std::unordered_set<Location> locations;
    assert(locations.empty());

    // try to make 2 Location objects using duplicate coordinate pairs
    // only one of the objects should be added
    Coordinate c1(1, 2.5f);
    Coordinate c2(1, 2.5f);
    Location l(c1, c2);
    locations.insert(l);
    assert(locations.size() == 1);
    Coordinate c3(1, 2.5f);
    Coordinate c4(1, 2.5f);
    Location l2(c3, c4);
    locations.insert(l2);
    assert(locations.size() == 1);

    // add in a new Location object that is not a duplicate
    Coordinate c5(1, 2.0f);
    Coordinate c6(2, 2.5f);
    Location l3(c5, c6);
    locations.insert(l3);
    assert(locations.size() == 2);
}