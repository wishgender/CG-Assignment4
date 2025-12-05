#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= bullet.hpp

//= Dependencies =//
#include <GL/glut.h>
#include "position.hpp"

class Bullet {
public:
    Bullet(float startX, float startY, float startZ, float dirX, float dirZ, float spd);

    void update();
    void draw() const;
    bool isActive() const;
    void deactivate();
    float getX() const;
    float getZ() const;

private:
    float x, y, z;   // position in 3D space
    float dirX, dirZ;
    float speed;
    bool active;
};
