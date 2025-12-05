#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= globalVars.hpp

//= pi constant
#define PI 3.141592f

//= Dependencies =//
#include <string>
#include <vector>
#include <GL/freeglut.h>
#include <miniaudio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//=== WINDOW VARIABLES ===//

//= default width & height
extern const int DEFAULT_W, DEFAULT_H;
//= window width
extern int WINDOW_W;
//= window height
extern int WINDOW_H;
//= fullscreen toggle
extern bool toggleFullscreen;

//=== VIEWPORT VARIABLES ===//

//= show bird's-eye view in the main viewport
extern bool birdsEyeIsMain;
//= viewport height ratio for main view
extern const float MAIN_VIEW_RATIO;
//= viewport size ratio for bird's eye view
extern const float ESV_RATIO;
//= viewport height ratio for game info
extern const float INFO_RATIO;

//=== GAME VARIABLES ===//

//= paused flag
extern bool paused;
//= menu selection
extern int menuSelection;
//= miniaudio sound engine
extern ma_engine engine;
//= BG music
extern ma_sound bgm;
//= sound flag
extern bool soundOn;
//= game over flag
extern bool gameOver;
//= score
extern int gameScore;
//= maximum size for vector of robots
extern const int MAX_ROBOTS;
//= number of robots killed
extern int robotsKilled;
//= game timer flag
extern bool isGameTimerActive;
//= time limit (in seconds)
extern const int TIME_LIMIT;
//=time left (in seconds)
extern int timeLeft;
//= bullet speed options
enum ProjectileSpeed { SLOW, FAST, EXTREME };
//= current bullet speed
extern ProjectileSpeed bulletSpeed;

#include "color.hpp"
extern Color playerCollider;

//=== TEXT DISPLAY VARIABLES ===//

//= title text
extern const char* TITLE_TEXT;
//= controls text
extern const char* CONTROLS_TEXT_1;
extern const char* CONTROLS_TEXT_2;
extern const char* CONTROLS_TEXT_3;
extern const char* CONTROLS_TEXT_4;
extern const char* CONTROLS_TEXT_5;
//= instruction text
extern const char* MISSION_TEXT;
//= game over text
extern const char* GAME_OVER_TEXT;
//= mission success text
extern const char* SUCCESS_TEXT;
//= mission fail text
extern const char* FAIL_TEXT;
//= game score text
extern const char* SCORE_TEXT;
//= time left text
extern const char* TIME_LEFT_TEXT;
//= bullet speed text
extern const char* BULLET_SPEED_TEXT;
//= slow speed text
extern const char* SLOW_TEXT;
//= fast speed text
extern const char* FAST_TEXT;
//= extreme speed text
extern const char* EXTREME_TEXT;
//= vector of speed texts
extern const std::vector<const char*> TEXT_VEC;


//=== CAMERA VARIABLES ===//

//= last known mouse location
extern int MOUSE_X, MOUSE_Y; 

extern float
lx, lz, //= camera direction
firstPersonAngle, //= first-person view angle
CAMERA_X, CAMERA_Y, CAMERA_Z, //= first-person XYZ camera position
ESV_X, ESV_Y, ESV_Z, //= bird's-eye view XYZ camera position
ESV_THETA, ESV_PHI, ESV_RADIUS; //= spherical camera coords

//=== DISPLAY MODE VARIABLES ===//

//= vertex display mode
extern bool vertexMode;
//= wireframe display mode
extern bool wireModels;
//= display colliders?
extern bool showColliders;
//= display axes?
extern bool showAxes;
//= use bullet model flag
extern bool bulletModel;
//= render mode enum
enum RenderMode { SOLID, WIRE, VERTICES };
//= declare display mode variable
extern RenderMode shapeMode;

//=== TEXTURE VARIABLES ===//

//= shading mode flag
extern bool gouraudShading;
//= Assimp importers
static Assimp::Importer pistolImporter;
static Assimp::Importer bulletImporter;
//= Assimp scenes
extern const aiScene* pistol;
extern const aiScene* bullet;
//= textures
extern GLuint skyTexture;
extern GLuint gunMetal;
extern GLuint headTexture;
extern GLuint bodyTexture;
extern GLuint groundColor;

//=== LIGHTING VARIABLES ===//

//= directional sunlight
extern GLfloat sunAmbient[], sunDiffuse[], sunSpecular[], sunDirection[];

//= bulb point light
extern GLfloat bulbAmbient[], bulbDiffuse[], bulbSpecular[], bulbPosition[];

//= directional/point light toggle
extern bool directionalLight;

//=== ROBOT VARIABLES ===//

#include "robot.hpp"
//= declare robot vector
extern std::vector<Robot*> bots;
//= radii for collision spheres
extern const double playerRadius, robotRadius;
//= number of possible retries when placing bots
extern const int MAX_RETRIES;
//= size of the grid to place robots
extern const int GRID_SIZE;

#include "grid.hpp"
extern Grid gameField;

//= boolean variable indicating if points were placed successfully
extern bool success;
//= is the movement timer active?
extern bool isMoveTimerActive;
//= are the robots moving?
extern bool movementToggle;

#include "bullet.hpp"
extern std::vector<Bullet> bullets;
