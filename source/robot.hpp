#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= robot.hpp
//= class header for Humanoid Robot

//= Dependencies =//
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "position.hpp"
#include "color.hpp"


//= Humanoid Robot class definition
class Robot {
public:
    Robot(); //= default constructor
    Robot(const Robot&); //= copy constructor
    Robot(Point, const Color&, const Color&, const Color&); //= value constructor

    ~Robot(); //= destructor
    void    swap(Robot&); //= constant time swap

    Robot& operator=         (Robot); //= overloaded assignment operator
    bool    operator==        (const Robot&) const; //= overloaded equality operator
    bool    operator!=        (const Robot&) const; //= overloaded inequality operator

    //= setter functions
    void    setBulletCollision(bool);
    void    setPlayerCollision(bool);
    void    setArmAngle(float);
    void    setLegAngle(float);
    void    setYindex(GLdouble);
    void    setColliderColor(const Color&); //=Collider Color setter
    void    setBodyColor(const Color&); //=Body Color setter
    void    setHeadColor(const Color&); //=Head Color Setter
    void    setPosition(Point&);
    void    setTarget(const Point& target);

    //= getter functions
    bool      getBulletCollision() const;
    bool      getPlayerCollision() const;
    bool      dying() const;
    float     getAlpha() const;
    float     getArmAngle() const;
    float     getLegAngle() const;
    GLdouble  getYindex() const;
    Color     getColliderColor() const;
    Color     getBodyColor() const;
    Color     getHeadColor() const;
    Point     getPosition() const;
    bool      getIsMoving() const;
    bool      getBeenShot() const;

    //= death functions
    void kill(); //= trigger death
    void updateDeath(); //= death animation

    //= walking functions
    void    updateMovement();

    //= Template function for drawing vertex mode with different shapes
    template<typename Func, typename... Args>
    void drawVertices(Func func, Args... args) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(6.0f);
        func(args...);   // call the shape with arguments
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //= Drawing functions
    void drawHead(); //= draw head
    void drawTorso(); //= draw torso
    void drawArm(float, float); //= draw arms
    void drawLeg(float, float); //= draw legs
    void drawRobot(); //= draw full robot

private:
    bool bulletCollision, playerCollision; //= collision flags

    bool beenShot; //= has the robot been shot?
    bool isDead; //= is the robot dead (dying)
    float deathTimer; //= time since death (used with death animation)
    float alpha; //= transparency for fade animation

    float armAngle; //= angle of arms
    float legAngle; //= angle of legs
    GLdouble yIndex; //= y-index of robot
    
    Color* colliderColor; //= pointer to robot collider color
    Color* bodyColor; //= pointer to robot body color
    Color* bodyEdgeColor; //= pointer to robot body edge color
    Color* headColor; //= pointer to robot head color
    Color* headEdgeColor; //= pointer to robot head edge color
    
    Point position; //= XY coordinates representing robot location
    Point startPosition;
    Point targetPosition; //= location currently walking to
    bool isMoving; //= currently walking?
    float moveProgress; //= value for smooth movement
    float facingAngle;//= current facing direction (radians)
    float desiredAngle; //= angle to turn towards
};
void drawTexturedCube(float);
void drawTexturedOctahedron(float);
