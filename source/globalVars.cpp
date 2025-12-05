//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= globalVars.cpp

//= Dependencies =//
#include "globalVars.hpp"

//=== WINDOW VARIABLES ===//

//= default width & height
const int DEFAULT_W = 960, DEFAULT_H = 540;
//= window width
int WINDOW_W = DEFAULT_W;
//= window height
int WINDOW_H = DEFAULT_H;
//= fullscreen toggle
bool toggleFullscreen = false;

//=== VIEWPORT VARIABLES ===//

//= show bird's-eye view in the main viewport
bool birdsEyeIsMain = false;
//= viewport size ratio for bird's eye viewport
const float ESV_RATIO = 0.25;
//= viewport height ratio for main viewport
const float MAIN_VIEW_RATIO = 0.875;
//= viewport height ratio for game info viewport
const float INFO_RATIO = 0.125;

//=== GAME VARIABLES ===//

//= paused flag
bool paused = false;
//= menu selection
int menuSelection = 0;
//= miniaudio sound engine
ma_engine engine;
//= BG music
ma_sound bgm;
//= sound flag
bool soundOn = true;
//= game over flag
bool gameOver = false;
//= score
int gameScore = 0;
//= maximum size for vector of robots
const int MAX_ROBOTS = 10;
//= number of robots killed
int robotsKilled = 0;
//= game timer flag
bool isGameTimerActive;
//= time limit (in seconds)
const int TIME_LIMIT = 30;
//= time left (in seconds)
int timeLeft = TIME_LIMIT;
//= current bullet speed
ProjectileSpeed bulletSpeed = SLOW;

//=== TEXT DISPLAY VARIABLES ===//

//= title text
const char* TITLE_TEXT = "Robot Hunter Game";
//= controls text
const char* CONTROLS_TEXT_1 = " a = toggle axes display      b = change bullet speed        c  = toggle colliders";
const char* CONTROLS_TEXT_2 = " l = toggle lighting mode     m = toggle robot movement      o  = toggle bullet model";
const char* CONTROLS_TEXT_3 = " p = toggle vertex-only mode  s = toggle solid mode          w  = toggle wireframe mode";
const char* CONTROLS_TEXT_4 = "F1 = toggle full-screen      F2 = toggle first-person view and bird's-eye view";
const char* CONTROLS_TEXT_5 = "F3 = toggle sound            F4 = toggle shading mode  Spacebar = fire bullet";
const char* CONTROLS_TEXT_6 = "ARROWS: left = turn left    right = turn right    up = move forward    down = move backward";
//= instruction text
const char* MISSION_TEXT = "MISSION: DESTROY ALL ROBOTS IN 30 SECONDS!";
//= game over text
const char* GAME_OVER_TEXT = "TIME'S UP!";
//= mission success text
const char* SUCCESS_TEXT = "MISSION COMPLETE!";
//= mission fail text
const char* FAIL_TEXT = "MISSION FAIL!";
//= game score text
const char* SCORE_TEXT = "Robots killed : %d / %d";
//= time left text
const char* TIME_LEFT_TEXT = "Time left : %d / %d";
//= bullet speed text
const char* BULLET_SPEED_TEXT = "Bullet speed : %s";
//= slow speed text
const char* SLOW_TEXT = "SLOW";
//= fast speed text
const char* FAST_TEXT = "FAST";
//= extreme speed text
const char* EXTREME_TEXT = "EXTREME";
//= vector of speed texts
const std::vector<const char*> TEXT_VEC = { SLOW_TEXT, FAST_TEXT, EXTREME_TEXT };

//=== CAMERA VARIABLES ===//

//= last known mouse location
int MOUSE_X = WINDOW_W / 2, MOUSE_Y = WINDOW_H / 2;
//= camera direction
float lx = 0.0f, lz = -1.0f;
//= first-person view angle
float firstPersonAngle = 0.0f;
//= XYZ camera position
float CAMERA_X = 0.0f, CAMERA_Z = 0.0f, CAMERA_Y = 9.0f;
//= bird's eye view camera position
float ESV_X = 0, ESV_Y = 30, ESV_Z = 0;
//= bird's eye view angles
float ESV_THETA = 0.001f, ESV_PHI = 0.001f;
//= bird's eye view radius
float ESV_RADIUS = 30.0f;

//=== DISPLAY MODE VARIABLES ===//

//= vertex display mode
bool vertexMode = false;
//= wireframe display mode
bool wireModels = false;
//= display colliders?
bool showColliders = false;
//= display axes?
bool showAxes = true;
//= use bullet model flag
bool bulletModel = false;
//= display mode
RenderMode shapeMode = SOLID;

//=== TEXTURE VARIABLES ===//

//= shading mode flag
bool gouraudShading = false;
//= assimp scenes
const aiScene* pistol = pistolImporter.ReadFile("./resources/models/Pistol_02.obj",
    aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);
const aiScene* bullet = bulletImporter.ReadFile("./resources/models/Bullet.obj",
    aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

//=== LIGHTING VARIABLES ===//

//= Directional sunlight
//=   w = 0 -> directional
GLfloat sunAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f }, sunDiffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f },
sunSpecular[] = { 1.0f, 1.0f, 0.9f, 1.0f }, sunDirection[] = { -0.3f, -1.0f, -0.3f, 0.0f };

//= Bulb point light
//=   w = 1 -> point light
GLfloat bulbAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f }, bulbDiffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f },
bulbSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }, bulbPosition[] = { 0.0f, 3.0f, 0.0f, 1.0f };

bool directionalLight = true;

//=== ROBOT VARIABLES ===//

//= declare the bots vector
std::vector<Robot*> bots;
//= radii for collision spheres
const double
playerRadius = 2,
robotRadius = 4;
//= number of possible retries when placing bots
const int MAX_RETRIES = 500;
//= size of the grid to place robots
const int GRID_SIZE = 75;

//= game grid
Grid gameField;

//= robot position points placed?
bool success = gameField.placeEnemies(MAX_ROBOTS, robotRadius * 2, MAX_RETRIES);
//= is the movement timer active?
bool isMoveTimerActive = false;
//= are the robots moving?
bool movementToggle = false;

std::vector<Bullet> bullets;
