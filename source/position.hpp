#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= position.hpp

//= Dependencies =//
#include <ostream>
#include <vector>
#include <cstdlib>
#include <GL/glut.h>

//= a simple (x, y) coordinate pair
//struct Point { GLdouble x, y; };
struct Point {
    float x, y;
};
//= functions

std::ostream& operator<<(std::ostream& out, const Point& rhs);

bool isValid(const Point&, const std::vector<Point>&, int);

bool placePoints(std::vector<Point>&, int, int, int);
