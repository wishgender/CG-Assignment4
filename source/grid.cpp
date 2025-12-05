//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= grid.cpp

//= Dependencies =//
#include "grid.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include "globalVars.hpp"
#include "position.hpp"

enum Direction { NORTH, SOUTH, EAST, WEST };

std::vector<Direction> getRandomDirections() {
    std::vector<Direction> dirs = { NORTH, SOUTH, EAST, WEST };
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(dirs.begin(), dirs.end(), g);
    return dirs;
}

Grid::Grid() {
    gameGrid = initGrid(); //= initialize an empty grid
    setGridSpace(PLAYER, GRID_SIZE / 2, GRID_SIZE / 2); //= place player in the middle
    do {
        enemiesPlaced = placeEnemies(5, 6, 500);
    } while (enemiesPlaced == false);
}

Grid::Grid(const Grid& rhs) {
    enemiesPlaced = rhs.enemiesPlaced;
    enemyPos = rhs.enemyPos;
    gameGrid = rhs.gameGrid;
}

Grid::Grid(const Point& playerSpawn) {
    gameGrid = initGrid(); //= initialize an empty grid
    setGridSpace(PLAYER, playerSpawn.x, playerSpawn.y); //= place player at provided pos
    do {
        enemiesPlaced = placeEnemies(5, 6, 500);
    } while (enemiesPlaced == false);
}

Grid::~Grid() {

}

std::ostream& operator<<(std::ostream& out, const Grid& rhs) {
    for (int i = 0; i < GRID_SIZE; i++) {
        out << "| ";
        for (int j = 0; j < GRID_SIZE; j++) {
            out << rhs.gameGrid[i][j] << " | ";
        }
        out << '\n';
    }
    return out;
}

Point Grid::operator[](int target) const {
    if (target > MAX_ROBOTS || target < 0) std::cerr << "\noperator[] (const) out of bounds error\n", exit(3);
    else return (enemyPos[target]);
}

void Grid::setGridSpace(gridSpace value, int x, int y) {
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) { //= ensure coords are within vector bounds
        gameGrid[x][y] = value;
    }
}

std::vector<std::vector<gridSpace>> Grid::initGrid() {
    //= initialize a 2D gridSpace vector of size GRID_SIZE x GRID_SIZE where all gridSpaces are EMPTY
    std::vector<std::vector<gridSpace>> gameGrid(GRID_SIZE, std::vector<gridSpace>(GRID_SIZE, EMPTY));
    return gameGrid;
}

bool collision(const Point& p1, const Point& p2, const float& r1, const float& r2) {
    float distance = sqrt(
        ((p1.x - p2.x) * (p1.x - p2.x)) +
        ((p1.y - p2.y) * (p1.y - p2.y))
    );
    if (distance <= (r1 + r2)) {
        //std::cout << "Collision detected between points:\n\t"
        //    << p1 << "\tand " << p2 << std::endl;
        return true;
    }
    else return false;
}

bool Grid::isValidPoint(const Point& p) {
    Point player  = { CAMERA_X, CAMERA_Z };
    if (collision(p, player, robotRadius, playerRadius)) return false;
    for (const auto& q : enemyPos) {
        if (collision(p, q, robotRadius, robotRadius)) return false;
    }
    return true;
}

bool Grid::placeEnemies(int count, int minDist, int maxRetries) {
    //= set seed for pseudo-random number generation
    srand(std::time(nullptr));
    //srand(1);

    if (enemyPos.size() == count) return true; //= all five points have been placed, return true

    int retries = 0;
    while (retries++ < maxRetries) {
        int newX = std::rand() % GRID_SIZE;
        int newY = std::rand() % GRID_SIZE;
        Point p = { newX - (GRID_SIZE / 2), newY - (GRID_SIZE / 2) };
        if (isValidPoint(p)) { //= if the new point is valid
            enemyPos.push_back(p); //= add the new point to the stack
            if (placeEnemies(count, minDist, maxRetries)) return true; //= recurse
            enemyPos.pop_back(); //= backtrack
        }
    }
    return false; //= return false if point fails to be placed
}

void Grid::progressGrid() {
    if (movementToggle) {
        for (size_t i = 0; i < enemyPos.size() && i < bots.size(); ++i) {
            // Skip robots that are still walking
            if (bots[i]->getIsMoving()) continue;

            Point p = enemyPos[i];
            Point nextPos = p;
            std::vector<Direction> dirs = getRandomDirections();

            for (Direction dir : dirs) {
                Point candidate = p;
                switch (dir) {
                case NORTH: candidate.y += 1.5; break;
                case SOUTH: candidate.y -= 1.5; break;
                case EAST:  candidate.x += 1.5; break;
                case WEST:  candidate.x -= 1.5; break;
                }

                if (fabs(candidate.x) >= float(GRID_SIZE / 2) || fabs(candidate.y) >= float(GRID_SIZE / 2))
                    continue;
                if ((collision(p, { CAMERA_X, CAMERA_Z }, robotRadius, playerRadius))) continue;

                nextPos = candidate;
                break;
            }

            enemyPos[i] = nextPos; // keep grid tracking current location
            bots[i]->setTarget(nextPos);
        }
    }
}

void Grid::resetGrid() {
    while (!enemyPos.empty()) enemyPos.pop_back();
    for (auto i = 0; i < gameGrid.size(); i++) {
        while (!gameGrid[i].empty()) gameGrid[i].pop_back();
    }
    while (!gameGrid.empty()) gameGrid.pop_back();
    enemiesPlaced = false;
}
