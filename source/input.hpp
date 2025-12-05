#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= menus.hpp

//= Dependencies =//
#include <GL/glut.h>
#include "globalVars.hpp"
#include <iostream>

static float aspectRatio;
extern GLint LMB, MMB, RMB;

void displayControls();

void KeyboardInputCallback(unsigned char key, int x, int y);

void ProcessSpecialKeys(int, int, int);

void changeBulletSpeed();

void recomputeOrientation();

void MouseCallback(int, int, int, int);

void MouseMotion(int, int);

bool canMove(const Point&);

void ReshapeDisplay(int, int);

void ResetGame();

void GameMenu();

void drawPauseMenu();
