//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= input.cpp

//= Dependencies =//
#include "input.hpp"
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <miniaudio.h>
#include "drawScene.hpp"
#include "globalVars.hpp"
#include "robot.hpp"
#include "grid.hpp"
#include "bullet.hpp"


int LMB = 0; int MMB = 0; int RMB = 0;

//= Key Inputs =//

//= checks for wire/solid, clear/showing models, & axes display toggle
void KeyboardInputCallback(unsigned char key, int x, int y) {
    //std::cout << "Keyboard Input - Key [" << key << "]" << std::endl;
    if (!gameOver) {
        key = tolower(key);
        switch (key)
        {
        case 'a':
            showAxes = !showAxes; //= only modify axes if models are being rendered
            break;
        case 'b':
            changeBulletSpeed();
            break;
        case 'c':  //= toggle collider display
            showColliders = !showColliders;
            break;
        case 'l': //= toggle between directional light & point light
            directionalLight = !directionalLight;
            break;
        case 'm': //= toggle movement
            movementToggle = !movementToggle;
            if (movementToggle) glutTimerFunc(16, moveEnemiesTimer, 0);
            break;
        case 'o':
            bulletModel = !bulletModel;
            break;
        case 'p':
            shapeMode = VERTICES; //= only modify models if being rendered
            break;
        case 's': //= solid mode
            shapeMode = SOLID; //= only modify if models are being rendered
            break;
        case 'w':
            shapeMode = WIRE; //= only if models are being rendered
            break;
        case ' ':
            float speedValue;
            switch (bulletSpeed) {
            case SLOW:    speedValue = 0.3f; break;
            case FAST:    speedValue = 0.6f; break;
            case EXTREME: speedValue = 1.0f; break;
            }

            bullets.emplace_back(CAMERA_X, CAMERA_Y, CAMERA_Z, lx, lz, speedValue);
            if (soundOn) ma_engine_play_sound(&engine, "./resources/sounds/gunfire.wav", NULL); //= play gunfire sound
            break;
        }
        glutPostRedisplay();
    }
    if (!paused && key == 27) {       //= ESC key menu
        paused = !paused;
        soundOn = !soundOn;
        soundOn ? ma_sound_start(&bgm) : ma_sound_stop(&bgm);
        movementToggle = !movementToggle;
        return;
    }
    if (paused) {
        if (key == '\r' || key == '\n') {  //= Enter key
            if (menuSelection == 0) { //= Resume
                soundOn = !soundOn;
                soundOn ? ma_sound_start(&bgm) : ma_sound_stop(&bgm);
                movementToggle = true;
                paused = false;
            }
            else if (menuSelection == 1) {//= new game
                soundOn = !soundOn;
                if (soundOn) {
                    ma_sound_seek_to_second(&bgm, 0);
                    ma_sound_start(&bgm);
                }
                else ma_sound_stop(&bgm);
                movementToggle = !movementToggle;
                ResetGame();
                paused = false;
            }
            else if (menuSelection == 2) { //= Quit
                exit(0);
            }
        }
    }
}


//= processes input of the arrow keys and function keys
void ProcessSpecialKeys(int key, int xx, int yy) {
    //= debug output
    //std::cout << "Keyboard Input - Key [" << key << "]" << std::endl;
    if (!gameOver) {
        float fraction = 0.3f; //= fraction for adjusting left-right turning
        Point newPos;
        switch (key) {
        case GLUT_KEY_F2:
            //= F2 toggles the main viewport between the first-person
            //= view and bird's-eye view cameras
            birdsEyeIsMain = !birdsEyeIsMain;
            break;
        case GLUT_KEY_F3:
            //= toggle sound on/off
            soundOn = !soundOn;
            if (soundOn) {
                ma_sound_start(&bgm);
            }
            else ma_sound_stop(&bgm);
            break;
        case GLUT_KEY_F4:
            //= toggle shading mode
            gouraudShading = !gouraudShading; 

            break;
        case GLUT_KEY_LEFT:
            //= left arrow turns first person camera left
            firstPersonAngle -= 0.05f;
            lx = sin(firstPersonAngle);
            lz = -cos(firstPersonAngle);
            break;
        case GLUT_KEY_RIGHT:
            //= right arrow turns first person camera right
            firstPersonAngle += 0.05f;
            lx = sin(firstPersonAngle);
            lz = -cos(firstPersonAngle);
            break;
        case GLUT_KEY_UP:
            newPos = { CAMERA_X + lx * fraction, CAMERA_Z + lz * fraction };
            //= up arrow moves first person camera forward
            if (canMove(newPos)) {
                CAMERA_X = newPos.x;
                CAMERA_Z = newPos.y;
            }
            break;
        case GLUT_KEY_DOWN:
            newPos = { CAMERA_X - lx * fraction, CAMERA_Z - lz * fraction };
            //= down arrow moves first person camera backward
            if (canMove(newPos)) {
                CAMERA_X = newPos.x;
                CAMERA_Z = newPos.y;
            }
            break;
        }
    }
    if (key == GLUT_KEY_F1) { //= outside of game over conditional, so that you are always able to exit full screen mode
        //= F1 toggles full screen mode
        toggleFullscreen = !toggleFullscreen;
        if (toggleFullscreen) glutFullScreen();
        else glutReshapeWindow(DEFAULT_W, DEFAULT_H);
    }
    if (paused) {
        if (key == GLUT_KEY_DOWN) {       // move down
            menuSelection++;
            if (menuSelection < 0) menuSelection = 2;
        }
        else if (key == GLUT_KEY_UP) {  // move up
            menuSelection--;
            if (menuSelection > 1) menuSelection = 0;
        }
    }
}

void recomputeOrientation() {
    ESV_X = ESV_RADIUS * sinf(ESV_THETA) * sinf(ESV_PHI);
    ESV_Y = ESV_RADIUS * cosf(ESV_PHI);
    ESV_Z = ESV_RADIUS * cosf(ESV_THETA) * sinf(ESV_PHI);
    glutPostRedisplay();
}

void MouseCallback(int button, int state, int thisX, int thisY) {
    if (birdsEyeIsMain) {
        if (button == GLUT_LEFT_BUTTON) {
            LMB = state;
        }
        else if (button == 3 ) {
            MMB = state;
            if (!MMB) ESV_RADIUS += 1.0;
            if (ESV_RADIUS > 80.0) ESV_RADIUS = 80.0;
        }
        else if (button == 4) {
            MMB = state;
            if (!state) ESV_RADIUS -= 1.0;
            if (ESV_RADIUS < 10.0) ESV_RADIUS = 10.0;
        }
        MOUSE_X = thisX;
        MOUSE_Y = thisY;
    }
    recomputeOrientation();
}

void MouseMotion(int x, int y) {
    if (birdsEyeIsMain) {
        if (LMB == GLUT_DOWN) {
            ESV_THETA += (MOUSE_X - x) * 0.005;
            ESV_PHI += (MOUSE_Y - y) * 0.005;

            if (ESV_PHI <= 0) ESV_PHI = 0.0f + 0.001f;
            if (ESV_PHI >= PI) ESV_PHI = PI - 0.001f;
            recomputeOrientation();
        }
        MOUSE_X = x;
        MOUSE_Y = y;
    }
}

void changeBulletSpeed() {
    switch (bulletSpeed) {
    case SLOW:
        bulletSpeed = FAST;
        break;
    case FAST:
        bulletSpeed = EXTREME;
        break;
    case EXTREME:
        bulletSpeed = SLOW;
        break;
    }
}

bool canMove(const Point& newPos) {
    for (const auto& b : bots) {
        if (!(b->dying()) && (collision(newPos, b->getPosition(), playerRadius, robotRadius))) {
            b->setColliderColor(RED);
            return false;
        }
    }
    return true;
}

//= Display resizing function
void ReshapeDisplay(int w, int h) {
    if (h == 0) h = 1; //= No dividing by zero
    float ratio = w * 1.0f / h;
    WINDOW_W = w; //= set window width
    WINDOW_H = h; //= set window height

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ResetGame() {
    while (!bots.empty()) bots.pop_back();
    
    lx = 0.0f; lz = -1.0f; firstPersonAngle = 0.0f;
    CAMERA_X = 0.0f; CAMERA_Z = 0.0f; CAMERA_Y = 9.0f;
    ESV_X = 0; ESV_Y = 30; ESV_Z = 0;
    ESV_THETA = 0.001f; ESV_PHI = 0.001f; ESV_RADIUS = 30.0f;

    gameField.resetGrid();
    robotsKilled = 0;
    gameOver = false;
    timeLeft = TIME_LIMIT;
    success = false;
    bulletSpeed = SLOW;
    movementToggle = false;
    isMoveTimerActive = false;
    isGameTimerActive = true;
    glutTimerFunc(1000, gameTimer, 0);
}
void drawPauseMenu() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Dark overlay
    glColor4f(0, 0, 0, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();

    //= Menu items
    const char* items[] = { "Resume", "New Game", "Quit" };
    int itemCount = 3;

    for (int i = 0; i < itemCount; i++) {
        if (i == menuSelection)
            glColor3f(1.0f, 1.0f, 0.2f);  //= highlight
        else
            glColor3f(1.0f, 1.0f, 1.0f);

        glRasterPos2f(360, 400 - i * 40);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)items[i]);
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
