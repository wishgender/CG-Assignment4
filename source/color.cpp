//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= color.cpp

//= Dependencies =//
#include "color.hpp"
#include <GL/glut.h>
#include <iostream>
#include <vector>

//=============================================================================
//=Constructors, destructor, & swap

  //=Default Constructor
Color::Color() {
    values = new GLfloat[3]{ 255, 255, 255 };
};

//=Copy Constructor
Color::Color(const Color& inputColor) {
    values = new GLfloat[3];
    for (int i = 0; i < 3; i++) {
        values[i] = inputColor.values[i];
    }
};

//=Value Constructor
Color::Color(int r, int g, int b) {
    values = new GLfloat[3];
    values[0] = GLfloat(r);
    values[1] = GLfloat(g);
    values[2] = GLfloat(b);
}

//=Destructor
Color::~Color() {
    delete[] values;
};

//=Constant time swap
void Color::swap(Color& rhs) {
    GLfloat* temp = values;
    values = rhs.values;
    rhs.values = temp;
};

//=Returns the color values as an array of GLfloats
GLfloat* Color::getValues() const {
    GLfloat* ret = new GLfloat[3];
    for (int i = 0; i < 3; i++) {
        ret[i] = (values[i] / 255);
    }
    return ret;
}

//=Overloaded at operator
GLfloat Color::operator[](int target) const {
    //=returns an error if out of bounds
    if (target > 3 || target < 0) std::cerr << "\noperator[] (const) out of bounds error\n", exit(3);
    //=otherwise returns the element of str at index target, converted to a useable GLfloat value
    else return (values[target] / GLfloat(255));
};

//=Overloaded assignment operator
Color& Color::operator=(Color rhs) {
    if (*this != rhs) {
        this->swap(rhs);
    }
    return *this;
};

//=Overloaded equality operator
bool Color::operator==(const Color rhs) const {
    if (values)
    for (int i = 0; i < 3; i++) {
        if (values[i] != rhs.values[i]) return false;
    }
    return true;
};

//=Overloaded inequality operator
bool operator!=(const Color lhs, const Color& rhs) {
    if (!(lhs == rhs)) return true;
    else return false;
};

//=Overloaded output operator
//=Only used for debugging
std::ostream& operator<<(std::ostream& out, const Color& rhs) {
    out << "R: " << rhs.values[0] << " G: " << rhs.values[1] << " B: " << rhs.values[2] << std::endl;
    return out;
}

//=== COLOR CONSTANTS ===//

const Color
RED = { 255, 0, 0 }, ORANGE = { 255, 165, 0 }, YELLOW = { 255, 255, 0 },
LIME = { 0, 255, 0 }, AQUA = { 0, 255, 255 }, BLUE = { 0, 0, 255 },
FUCHSIA = { 255, 0, 255 }, SILVER = { 191, 191, 191 }, WHITE = { 255, 255, 255 },
MAROON = { 127, 0, 0 }, BROWN = { 165, 42, 42 }, OLIVE = { 127, 127, 0 },
GREEN = { 0, 127, 0 }, TEAL = { 0, 127, 127 }, NAVY = { 0, 0, 127 },
PURPLE = { 127, 0, 127 }, GRAY = { 127, 127, 127 }, BLACK = { 0, 0, 0 },
PINK = { 255, 0, 127 }, VIOLET = { 127, 0, 255 }, AQUAMARINE = { 0, 255, 127 },
CHARTREUSE = { 127, 255, 0 };


//= text color
const Color TEXT_COLOR_1 = FUCHSIA, TEXT_COLOR_2 = BLACK, TEXT_COLOR_3 = WHITE;

//= collider colors
const Color NO_COLLISION_COLOR = AQUA, ROBOT_PLAYER_COLLISION = RED, ROBOT_BULLET_COLLISION = LIME;

Color playerCollider = NO_COLLISION_COLOR;


//= all robot colors have a slightly darker edge color to make it
//= easier to distinguish the edges of shapes

//= robot head colors
const Color
HeadNeutralHue = { 174, 174, 174 }, HeadNeutralEdgeHue = { 124, 124, 124 },
HeadHappyHue = { 250, 255, 96 }, HeadHappyEdgeHue = { 200, 205, 46 },
HeadSadHue = { 0, 49, 205 }, HeadSadEdgeHue = { 0, 0, 155 },
HeadAngryHue = { 245, 39, 39 }, HeadAngryEdgeHue = { 195, 0, 0 },
HeadScaredHue = { 141, 0, 255 }, HeadScaredEdgeHue = { 91, 0, 205 },
HeadEmbarrassedHue = { 255, 147, 28 }, HeadEmbarrassedEdgeHue = { 205, 97, 0 },
HeadLoveHue = { 255, 89, 175 }, HeadLoveEdgeHue = { 205, 39, 125 },
HeadDisgustHue = { 76, 246, 94 }, HeadDisgustEdgeHue = { 26, 196, 44 };

//= robot body colors
const Color
BodyIndigoHue = { 124, 110, 255 }, BodyIndigoEdgeHue = { 74, 60, 205 },
BodyPinkHue = { 255, 103, 193 }, BodyPinkEdgeHue = { 205, 53, 143 },
BodyGreenHue = { 202, 255, 102 }, BodyGreenEdgeHue = { 152, 205, 52 },
BodyBlueHue = { 75, 243, 224 }, BodyBlueEdgeHue = { 63, 191, 177 },
BodyYellowHue = { 240, 219, 79 }, BodyYellowEdgeHue = { 161, 147, 55 };

//= color vectors
std::vector<Color>
HeadHues = { HeadHappyHue, HeadAngryHue, HeadSadHue, HeadNeutralHue, HeadScaredHue, HeadEmbarrassedHue, HeadLoveHue, HeadDisgustHue },
HeadEdgeHues = { HeadHappyEdgeHue, HeadAngryEdgeHue, HeadSadEdgeHue, HeadNeutralEdgeHue, HeadScaredEdgeHue, HeadEmbarrassedEdgeHue, HeadLoveEdgeHue, HeadDisgustEdgeHue },
BodyHues = { BodyIndigoHue, BodyPinkHue, BodyGreenHue, BodyBlueHue, BodyYellowHue },
BodyEdgeHues = { BodyIndigoEdgeHue, BodyPinkEdgeHue, BodyGreenEdgeHue, BodyBlueEdgeHue, BodyYellowEdgeHue };

//= world colors
const Color
GroundHue = { 24, 68, 22 }, SkyBlue = { 147, 231, 255 },
SkyPink = { 255, 199, 233 }, SkyLavender = { 220, 180, 250 };

