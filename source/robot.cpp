//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= robot.cpp
//= class definition for Humanoid Robot

//= Dependencies =//
#include "robot.hpp"
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "globalVars.hpp"

//=============================================================================
//=Constructors, destructor, & swap

  //=Default Constructor
Robot::Robot() {
    bulletCollision = false;
    playerCollision = false;

    beenShot = false;
    isDead = false;
    deathTimer = 0.0f;
    alpha = 1.0f;

    armAngle = 0.0f;
    legAngle = 0.0f;
    yIndex = 0.00;

    setColliderColor(NO_COLLISION_COLOR);
    setBodyColor(BodyIndigoHue);
    setHeadColor(HeadNeutralHue);
    
    position = Point{ 0, 0 };
    targetPosition = position;
    startPosition = position;
    isMoving = false;
    moveProgress = 0.0f;
    facingAngle = 0.0f;
    desiredAngle = 0.0f;
};

//=Copy Constructor
Robot::Robot(const Robot& input) {
    bulletCollision = input.bulletCollision;
    playerCollision = input.playerCollision;
   
    isDead = input.isDead;
    deathTimer = input.deathTimer;
    alpha = input.alpha;

    armAngle = input.armAngle;
    legAngle = input.legAngle;
    yIndex = input.yIndex;

    setColliderColor(*input.colliderColor);
    setBodyColor(*input.bodyColor);
    setHeadColor(*input.headColor);

    position = input.position;
    targetPosition = input.targetPosition;
    isMoving = input.isMoving;
    moveProgress = input.moveProgress;
    facingAngle = input.facingAngle;
    desiredAngle = input.desiredAngle;
    startPosition = input.startPosition;
}

//=Values Constructor
Robot::Robot(Point pos, const Color& body, const Color& head, const Color& collider) {
    bulletCollision = false;
    playerCollision = false;

    beenShot = false;
    isDead = false;
    deathTimer = 0.0f;
    alpha = 1.0f;

    armAngle = 0.0f;
    legAngle = 0.0f;
    yIndex = 0.00;

    //=set colors
    setColliderColor(NO_COLLISION_COLOR);
    setBodyColor(body);
    setHeadColor(head);

    //=set position
    position = pos;
    startPosition = position;
    targetPosition = position;
    isMoving = false;
    moveProgress = 0.0f;
    facingAngle = 0.0f;
    desiredAngle = 0.0f;
}

//=Destructor
Robot::~Robot() {
    delete colliderColor, bodyColor, bodyEdgeColor, headColor, headEdgeColor;
}

//=Constant time swap
void Robot::swap(Robot& rhs) {
    Robot* temp = this;

    bulletCollision = rhs.bulletCollision;
    rhs.bulletCollision = temp->bulletCollision;

    playerCollision = rhs.playerCollision;
    rhs.playerCollision = temp->playerCollision;

    isDead = rhs.isDead;
    rhs.isDead = temp->isDead;

    deathTimer = rhs.deathTimer;
    rhs.deathTimer = temp->deathTimer;

    alpha = rhs.alpha;
    rhs.alpha = temp->alpha;

    armAngle = rhs.armAngle;
    rhs.armAngle = temp->armAngle;

    legAngle = rhs.legAngle;
    rhs.legAngle = temp->legAngle;

    yIndex = rhs.yIndex;
    rhs.yIndex = temp->yIndex;

    colliderColor = rhs.colliderColor;
    rhs.colliderColor = temp->colliderColor;

    bodyColor = rhs.bodyColor;
    rhs.bodyColor = temp->bodyColor;

    bodyEdgeColor = rhs.bodyEdgeColor;
    rhs.bodyEdgeColor = temp->bodyEdgeColor;

    headColor = rhs.headColor;
    rhs.headColor = temp->headColor;

    headEdgeColor = rhs.headEdgeColor;
    rhs.headEdgeColor = temp->headEdgeColor;

    position = rhs.position;
    rhs.position = temp->position;

    targetPosition = rhs.targetPosition;
    rhs.targetPosition = temp->targetPosition;

    isMoving = rhs.isMoving;
    rhs.isMoving = temp->isMoving;

    moveProgress = rhs.moveProgress;
    rhs.moveProgress = temp->moveProgress;

    facingAngle = rhs.facingAngle;
    rhs.facingAngle = temp->facingAngle;
}

//=============================================================================
//=Overloaded operators

  //=Overloaded assignment operator
Robot& Robot::operator=(Robot rhs) {
    if (*this != rhs) {
        this->swap(rhs);
    }
    return *this;
}

//=Overloaded equality operator
bool Robot::operator==(const Robot& rhs) const {
    if (
        (bulletCollision != rhs.bulletCollision)
        || (playerCollision != rhs.playerCollision)
        || (isDead != rhs.isDead)
        || (deathTimer != rhs.deathTimer)
        || (alpha != rhs.alpha)
        || (armAngle != rhs.armAngle)
        || (legAngle != rhs.legAngle)
        || (yIndex != rhs.yIndex)
        || (*colliderColor != *rhs.colliderColor)
        || (*bodyColor != *rhs.bodyColor)
        || (*bodyEdgeColor != *rhs.bodyEdgeColor)
        || (*headColor != *rhs.headColor)
        || (*headEdgeColor != *rhs.headEdgeColor)
        || (position.x != rhs.position.x 
            || position.y != rhs.position.y)
        || (targetPosition.x != rhs.targetPosition.x
            || targetPosition.y != rhs.targetPosition.y)
        || (isMoving != rhs.isMoving)
        || (moveProgress != rhs.moveProgress)
        || (facingAngle != rhs.facingAngle)
    ) return false;

    return true;
}

//=Overloaded inequality operator
bool Robot::operator!=(const Robot& rhs) const {
    if (!(*this == rhs)) return true;
    else return false;
}

//=============================================================================
//=Setters

//=Bullet collision setter
void Robot::setBulletCollision(bool collide) {
    bulletCollision = collide;
}

//=Player collision setter
void Robot::setPlayerCollision(bool collide) {
    playerCollision = collide;
}
  
//=Collider Color setter
void Robot::setColliderColor(const Color& collider) {
    colliderColor = new Color(collider);
}

//=Body Color setter
void Robot::setBodyColor(const Color& body) {
    const Color* newBodyColor = new Color(body);

    if (*newBodyColor == BodyIndigoHue) {
        bodyColor = new Color(BodyIndigoHue);
        bodyEdgeColor = new Color(BodyIndigoEdgeHue);
    }
    else if (*newBodyColor == BodyPinkHue) {
        bodyColor = new Color(BodyPinkHue);
        bodyEdgeColor = new Color(BodyPinkEdgeHue);
    }
    else if (*newBodyColor == BodyGreenHue) {
        bodyColor = new Color(BodyGreenHue);
        bodyEdgeColor = new Color(BodyGreenEdgeHue);
    }
    else if (*newBodyColor == BodyBlueHue) {
        bodyColor = new Color(BodyBlueHue);
        bodyEdgeColor = new Color(BodyBlueEdgeHue);
    }
    else if (*newBodyColor == BodyYellowHue) {
        bodyColor = new Color(BodyYellowHue);
        bodyEdgeColor = new Color(BodyYellowEdgeHue);
    }
}

//=Head Color Setter
void Robot::setHeadColor(const Color& head) {
    const Color* newHeadColor = new Color(head);

    if (*newHeadColor == HeadNeutralHue) {
        headColor = new Color(HeadNeutralHue);
        headEdgeColor = new Color(HeadNeutralEdgeHue);
    }
    else if (*newHeadColor == HeadHappyHue) {
        headColor = new Color(HeadHappyHue);
        headEdgeColor = new Color(HeadHappyEdgeHue);
    }
    else if (*newHeadColor == HeadSadHue) {
        headColor = new Color(HeadSadHue);
        headEdgeColor = new Color(HeadSadEdgeHue);
    }
    else if (*newHeadColor == HeadAngryHue) {
        headColor = new Color(HeadAngryHue);
        headEdgeColor = new Color(HeadAngryEdgeHue);
    }
    else if (*newHeadColor == HeadScaredHue) {
        headColor = new Color(HeadScaredHue);
        headEdgeColor = new Color(HeadScaredEdgeHue);
    }
    else if (*newHeadColor == HeadEmbarrassedHue) {
        headColor = new Color(HeadEmbarrassedHue);
        headEdgeColor = new Color(HeadEmbarrassedEdgeHue);
    }
    else if (*newHeadColor == HeadLoveHue) {
        headColor = new Color(HeadLoveHue);
        headEdgeColor = new Color(HeadLoveEdgeHue);
    }
    else if (*newHeadColor == HeadDisgustHue) {
        headColor = new Color(HeadDisgustHue);
        headEdgeColor = new Color(HeadDisgustEdgeHue);
    }
}

//=Position setter
void Robot::setPosition(Point& newPos) {
    position = newPos;
}

//=Arm angle setter
void Robot::setArmAngle(float input) {
    armAngle = input;
}

//=Leg angle setter
void Robot::setLegAngle(float input) {
    legAngle = input;
}

//=Y index setter
void Robot::setYindex(GLdouble newY) {
    yIndex = newY;
}

//=Target position setter
void Robot::setTarget(const Point& target) {
    if (target.x == position.x && target.y == position.y) return;
    
    //startPosition = position;
    targetPosition = target;
    //isMoving = true;
    moveProgress = 0.0f;

    //= calculate facing angle based on direction
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    desiredAngle = atan2(dy, dx); //= in radians
}

//=============================================================================
//=Getters

//=Collider color getter
Color Robot::getColliderColor() const {
    return *colliderColor;
}

//=Body color getter
Color Robot::getBodyColor() const {
    return *bodyColor;
}

//=Head color getter
Color Robot::getHeadColor() const {
    return *headColor;
}

//=Position getter
Point Robot::getPosition() const {
    return position;
}

//=Arm angle getter
float Robot::getArmAngle() const {
    return armAngle;
}

//=Leg angle getter
float Robot::getLegAngle() const {
    return legAngle;
}

//=Y index getter
GLdouble Robot::getYindex() const {
    return yIndex;
}

//=Bullet collision getter
bool Robot::getBulletCollision() const {
    return bulletCollision;
}

//=Player collision getter
bool Robot::getPlayerCollision() const {
    return playerCollision;
}

//=Transparency value getter
float Robot::getAlpha() const {
    return alpha;
}

bool Robot::getIsMoving() const {
    return isMoving;
}

//=Death flag getter
bool Robot::dying() const {
    return (deathTimer < 0.0f);
}

bool Robot::getBeenShot() const {
    return beenShot;
}

//=Trigger death
void Robot::kill() {
    if (isDead || beenShot) return;
    beenShot = true;
    isDead = true;
    deathTimer = 0.0f;
    alpha = 1.0f;
    setColliderColor(ROBOT_BULLET_COLLISION);
}

//=Death animation
void Robot::updateDeath() {
    if (!isDead) return;

    deathTimer += 0.05f; //= advance timer

    //= fall and fade
    if (deathTimer < 3.0f) {
        yIndex -= 0.1f; //= slowly fall
        armAngle += 10.0f; //= spin/flail arms
        legAngle -= 10.0f; //= spin/flail legs
        alpha = std::max(0.0f, 1.0f - (deathTimer / 3.0f)); //=fade out
    }
    else {
        //= mark as ready for removal
        isDead = false;
        deathTimer = -1.0f;
    }
}

//= Movement animation
void Robot::updateMovement() {
    float angleDiff = desiredAngle - facingAngle;

    while (angleDiff >  PI) angleDiff -= 2 * PI;
    while (angleDiff < -PI) angleDiff += 2 * PI;
    
    if (fabs(angleDiff) > 0.05f) {
        facingAngle += (angleDiff * 0.15f);
        return;
    }

    if (!isMoving) {
        isMoving = true;
        startPosition = position;
    }

    moveProgress += 0.01f;
    
    if (moveProgress >= 1.0f) {
        moveProgress = 1.0f;
        isMoving = false;
        position = targetPosition;
        armAngle = legAngle = 0.0f;
        return;
    }

    //= interpolation between current position and target
    position.x = startPosition.x + (targetPosition.x - startPosition.x) * moveProgress;
    position.y = startPosition.y + (targetPosition.y - startPosition.y) * moveProgress;

    armAngle = sin(moveProgress * PI * 4) * 15.0f;
    legAngle = cos(moveProgress * PI * 4) * 15.0f;

}

//= Helper function to draw the octahedron head
void Robot::drawHead() {
    glPushMatrix();


    //= Place the head above the torso
    glTranslatef(0.0f, 2.8f, 0.0f);

    //= Proportion of the head is taller than it is wide
    glScalef(0.7f, 1.3f, 0.7f);

    glColor4f(headColor->getValues()[0], headColor->getValues()[1], headColor->getValues()[2], alpha);

    //= set up texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, headTexture);

    //= Model Modes

    if (shapeMode == SOLID) {
        //= draw the solid shape
        drawTexturedOctahedron(1.0f);
        //= set the edge color so the shape can be discerned
        glColor4f(headEdgeColor->getValues()[0], headEdgeColor->getValues()[1], headEdgeColor->getValues()[2], alpha);
        //= Draw the wire outline on top 
        glutWireOctahedron();
    }
    else if (shapeMode == WIRE) {
        //= Wire Mode- Just draw the wireframe
        //= no white wireframe requirement
        glColor4f(headEdgeColor->getValues()[0], headEdgeColor->getValues()[1], headEdgeColor->getValues()[2], alpha);
        glutWireOctahedron();
    }
    else if (shapeMode == VERTICES) {
        //= Draw only the vertices
        glColor4f(headEdgeColor->getValues()[0], headEdgeColor->getValues()[1], headEdgeColor->getValues()[2], alpha);
        drawVertices(glutSolidOctahedron);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//= Helper function to draw the robot's torso
void Robot::drawTorso() {
    glPushMatrix();
    glTranslated(0, -0.5, 0);
    glScalef(2.0f, 4.0f, 0.8f);

    //= set color
    glColor4f(bodyColor->getValues()[0], bodyColor->getValues()[1], bodyColor->getValues()[2], alpha);
    
    //= set up texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);

    //= Model Modes
    if (shapeMode == SOLID) {

        //= draw the solid shape
        drawTexturedCube(1.0f);
        //= set edge color
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        //= draw wire outline on top
        glutWireCube(1.0);
    }
    else if (shapeMode == WIRE) {
        //= no white wireframe requirement
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        //= draw the wireframe
        glutWireCube(1.0);
    }
    else if (shapeMode == VERTICES) {
        //= draw only the vertices
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        drawVertices(glutSolidCube, 1.00);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//= Helper function to draw the robot's arms
void Robot::drawArm(float offset, float angle) {
    glPushMatrix();
    glTranslatef(offset, 0.8f, 0.0f); //= offset left/right

    glRotatef(angle, 1, 0, 0);
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(0.6f, 4.7f, 0.6f);

    //= use arm color
    glColor4f(bodyColor->getValues()[0], bodyColor->getValues()[1], bodyColor->getValues()[2], alpha);

    //= set up texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);

    //= model modes
    if (shapeMode == SOLID) {
        //= draw solid shape
        drawTexturedCube(1.0f);
        //= set edge color
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        //= draw wire outline on top
        glutWireCube(1.0);
    }
    else if (shapeMode == WIRE) {
        //= no white wireframe requirement
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        glutWireCube(1.0);
    }
    else if (shapeMode == VERTICES) {
        //= draw only the vertices
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        drawVertices(glutSolidCube, 1.00);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//= Helper function to draw the robot's legs
void Robot::drawLeg(float offset, float angle) {
    glPushMatrix();
    glRotatef(angle, 1, 0, 0);
    glTranslatef(offset, -5.25f, 0.0f); // offset left/right below torso
    glScalef(0.8f, 5.5f, 0.8f);

    //= use legs color
    glColor4f(bodyColor->getValues()[0], bodyColor->getValues()[1], bodyColor->getValues()[2], alpha);

    //= set up texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);

    //= Model modes
    if (shapeMode == SOLID) {
        //= draw solid shape
        drawTexturedCube(1.0f);
        
        //= set edge color
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        //= draw wire outline on top
        glutWireCube(1.0);
    }
    else if (shapeMode == WIRE) {
        //= no white wireframe requirement
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        //= draw wireframe
        glutWireCube(1.0);
    }
    else if (shapeMode == VERTICES) {
        //= draw only the vertices
        glColor4f(bodyEdgeColor->getValues()[0], bodyEdgeColor->getValues()[1], bodyEdgeColor->getValues()[2], alpha);
        drawVertices(glutSolidCube, 1.00);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//= Helper function to draw the entire robot
void Robot::drawRobot() {
    if (deathTimer < 0) return;
    //= push a new matrix
    glPushMatrix();

    glEnable(GL_BLEND); //= enable blend for fade-out transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    


    //= translate to current position
    glTranslated(position.x, getYindex() + 8.0, position.y);
    //= rotate based on the spin angle
    glRotatef(facingAngle * 180.0f / PI, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    if (showColliders) {
        glPushMatrix();
        glColor4f(colliderColor->getValues()[0], colliderColor->getValues()[1], colliderColor->getValues()[2], alpha);
        glTranslated(0.0, -2.0, 0.0);
        glutWireSphere(robotRadius, 8, 8);
        glPopMatrix();
    }

    //= draw the torso first so translations can be based around it
    drawTorso();
    //= draw the head
    drawHead();

    //= push a matrix for drawing the first arm
    glPushMatrix();
    //= rotate the arm out slightly for a more interesting default stance
    glRotatef(5, 0, 0, 1);
    //= draw the arm, passing the offset and the angle
    drawArm(1.5f, armAngle);
    //= pop the matrix
    glPopMatrix();

    //= push a matrix for drawing the other arm
    glPushMatrix();
    //= rotate the arm out in the opposite direction of the first arm
    glRotatef(-5, 0, 0, 1);
    //= draw the arm, passing the offset and the angle
    drawArm(-1.5f, -armAngle);
    //= pop the matrix
    glPopMatrix();

    //= draw the first leg, passing the offset and the angle
    drawLeg(0.6f, legAngle);
    //= draw the other leg, passing the offset and the angle
    drawLeg(-0.6f, -legAngle);

    glDisable(GL_BLEND);

    //= pop the matrix
    glPopMatrix();
}

//= function to draw cubes for texturing (since glut cube functions don't include texture coords)
void drawTexturedCube(float size) {
    float s = size / 2.0f;

    glBegin(GL_QUADS);

    // Front (+Z)
    glTexCoord2f(0, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, s);

    // Back (−Z)
    glTexCoord2f(0, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, -s);

    // Left (−X)
    glTexCoord2f(0, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);

    // Right (+X)
    glTexCoord2f(0, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, s);

    // Top (+Y)
    glTexCoord2f(0, 0); glVertex3f(-s, s, s);
    glTexCoord2f(1, 0); glVertex3f(s, s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);

    // Bottom (−Y)
    glTexCoord2f(0, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(s, -s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, -s, s);

    glEnd();
}

//= function to draw octahedrons for texturing (since glut functions don't include texture coords)
void drawTexturedOctahedron(float size) {
    float s = size;

    glBegin(GL_TRIANGLES);

    // Top four faces
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, 0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, s);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(s, 0, 0);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(s, 0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -s);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, 0, 0);

    // Bottom four faces
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, -s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, 0, 0);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, -s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(s, 0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, s);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, -s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -s);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(s, 0, 0);

    glTexCoord2f(0.5f, 1.0f); glVertex3f(0, -s, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, 0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -s);

    glEnd();
}
