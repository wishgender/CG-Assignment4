//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= bullet.cpp

#include "bullet.hpp"
#include <cmath>
#include <GL/glut.h>
#include "globalVars.hpp"
#include "drawScene.hpp"

Bullet::Bullet(float startX, float startY, float startZ, float dX, float dZ, float spd)
    : x(startX), y(startY), z(startZ), dirX(dX), dirZ(dZ), speed(spd), active(true) {
}

void Bullet::update() {
    if (!active) return;
    x += dirX * speed;
    z += dirZ * speed;
}

void Bullet::draw() const {
    if (!active) return;

    glPushMatrix();

    //= Move bullet to its position
    glTranslatef(x, y-1, z);

    //= Rotate bullet
    float angle = atan2(dirX, dirZ) * 180.0f / PI;
    glRotatef(angle, 0, 1, 0);

    //= Fix the model’s built-in rotation
    glRotatef(90, 0, 1, 0);

    //= Scale to visible size
    glScaled(5.0, 5.0, 5.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gunMetal);
    //= Render depending on object flag
    bulletModel ? renderNode(bullet->mRootNode, bullet) : glutSolidSphere(0.04, 12, 12);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

bool Bullet::isActive() const {
    return active;
}

void Bullet::deactivate() {
    active = false;
}

float Bullet::getX() const {
    return x;
}

float Bullet::getZ() const {
    return z;
}
