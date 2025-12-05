#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= color.hpp

//= Dependencies =//
#include <GL/glut.h>
#include <iostream>
#include <vector>

//= color class declaration
class Color {
public:
    Color(); //= default constructor
    Color(const Color&); //= copy constructor
    Color(int, int, int); //= value constructor

    ~Color(); //= destructor
    void swap(Color&); //=Constant time swap

    GLfloat* getValues() const; //=Returns the color values as an array of GLfloats

    //=Overloaded at operator
    GLfloat operator[](int target) const;

    //=Overloaded assignment operator
    Color& operator= (Color);

    //=Overloaded equality operator
    bool operator==(const Color) const;

    //=Only used for debugging
    friend std::ostream& operator<<(std::ostream&, const Color& rhs); //=Overloaded output operator
private:
    //= pointer to GLfloat values
    GLfloat* values;
};

//=Overloaded inequality operator
bool operator!=(const Color lhs, const Color& rhs);

//=== COLOR CONSTANTS ===//

extern const Color
RED, ORANGE, YELLOW, LIME, AQUA, BLUE, FUCHSIA, SILVER, WHITE,
MAROON, BROWN, OLIVE, GREEN, TEAL, NAVY, PURPLE, GRAY, BLACK,
PINK, VIOLET, AQUAMARINE, CHARTREUSE;

//= text Colors
extern const Color
TEXT_COLOR_1, TEXT_COLOR_2, TEXT_COLOR_3;

//= collider colors
extern const Color
NO_COLLISION_COLOR, ROBOT_PLAYER_COLLISON, ROBOT_BULLET_COLLISION;

//= robot head Colors
extern const Color
HeadNeutralHue, HeadNeutralEdgeHue,
HeadHappyHue, HeadHappyEdgeHue,
HeadSadHue, HeadSadEdgeHue,
HeadAngryHue, HeadAngryEdgeHue,
HeadScaredHue, HeadScaredEdgeHue,
HeadEmbarrassedHue, HeadEmbarrassedEdgeHue,
HeadLoveHue, HeadLoveEdgeHue,
HeadDisgustHue, HeadDisgustEdgeHue;

//= robot body Colors
extern const Color
BodyIndigoHue, BodyIndigoEdgeHue,
BodyPinkHue, BodyPinkEdgeHue,
BodyGreenHue, BodyGreenEdgeHue,
BodyBlueHue, BodyBlueEdgeHue,
BodyYellowHue, BodyYellowEdgeHue;

//= color vectors
extern std::vector<Color> HeadHues, HeadEdgeHues, BodyHues, BodyEdgeHues;

//= world colors
extern const Color GroundHue, SkyBlue, SkyPink, SkyLavender;
