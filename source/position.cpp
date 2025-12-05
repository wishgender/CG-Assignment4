//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= position.hpp

//= Dependencies =//
#include "position.hpp"
#include <vector>
#include <iostream>
#include <ctime>


//= validation function
//= Returns TRUE if the point can be placed, FALSE if the point cannot be placed
bool isValid(const Point& p, const std::vector<Point>& points, int minDist) {
  for (const auto& q : points) {
    //= calculate distance between points
    int dx = p.x - q.x;
    int dy = p.y - q.y;
    if (dx * dx + dy * dy < minDist * minDist) //= if the distance is less than the minimum distance
      return false; //= return false
  }
  return true; //= return true only after having checked every point in the vector
}

//= function to place points in the vector
//= Returns TRUE when all points are able to be placed
//= Arguments: 
//= std::vector<Point>& points : vector of points, 
//= int count : total points needed,
//= int minDist : minimum distance between points,
//= int maxRetries : maximum retries (for avoiding infinite recursion)
bool placePoints(std::vector<Point>& points, int count, int minDist, int maxRetries) {
  //= set seed for pseudo-random number generation
  srand(std::time(nullptr));
  //srand(1);

  if (points.size() == count) return true; //= all five points have been placed, return true

  int retries = 0;
  while (retries++ < maxRetries) {
    Point p = { std::rand() % 36, std::rand() % 36 };
    if (isValid(p, points, minDist)) { //= if the new point is valid
      points.push_back(p); //= add the new point to the stack
      if (placePoints(points, count, minDist, maxRetries)) return true; //= recurse
      points.pop_back(); //= backtrack
    }
  }
  return false; //= return false if point fails to be placed
}

std::ostream& operator<<(std::ostream& out, const Point& rhs) {
    out << "{ X: " << rhs.x << ", Y: " << rhs.y << " }";
    return out;
}
