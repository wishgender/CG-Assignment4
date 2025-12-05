#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= drawScene.hpp

//= Dependencies =//
#include <vector>
#include <string>
#include <GL/glut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "globalVars.hpp"
#include "robot.hpp"
#include "position.hpp"


//= declare functions
std::vector<Robot*> getBots();
void drawString(float, float, void*, const char*);
void displayControls();
void drawAxes();
void drawGround();
void drawFirstPerson();
void drawGameInfoView();
void drawBirdsEye();
void drawViewportBorder(int x, int y, int width, int height, float r, float g, float b);
void bulletTimer(int);
void moveEnemiesTimer(int);
void gameTimer(int);
void renderSkyTexture();
void renderNode(aiNode*, const aiScene*);
void applyLighting();
