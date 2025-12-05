#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= grid.hpp

//= Dependencies =//
#include <iostream>
#include <vector>
#include "position.hpp"

enum gridSpace { EMPTY, ROBOT, PLAYER };

bool collision(const Point&, const Point&, const float&, const float&);

class Grid {
public:
    Grid();//= default constructor
    Grid(const Grid&); //= copy constructor
    Grid(const Point&); //= Spawn Point Constructor
    
    ~Grid(); //= destructor
    //void swap(Grid&);

    //Grid& operator=(Grid);
    friend std::ostream& operator<<(std::ostream& out, const Grid& rhs);
    Point operator[](int target) const;

    void setGridSpace(gridSpace, int, int);
    size_t getPosSize() { return enemyPos.size(); }
    
    bool isValidPoint(const Point&);
    void progressGrid();

    std::vector<std::vector<gridSpace>> initGrid();
    bool placeEnemies(int, int, int);
    void resetGrid();
private:
    bool enemiesPlaced;
    std::vector<Point> enemyPos; //= vector of enemy positions
    std::vector<std::vector<gridSpace>> gameGrid; //= 2D vector of grid spaces
};

