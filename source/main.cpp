//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= main.cpp

//= 9mm Pistol by Quaternius [CC-BY] (https://creativecommons.org/licenses/by/3.0/) via Poly Pizza (https://poly.pizza/m/BoZWhFdsj4)

#define STB_IMAGE_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION

//= Dependencies =//
#include <iostream>
#include <array>
#include <GL/glut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <miniaudio.h>
#include "utils.hpp"
#include "robot.hpp"
#include "color.hpp"
#include "globalVars.hpp"
#include "input.hpp"
#include "drawScene.hpp"


//= declare functions ahead
void MyDisplay(void);
void ReshapeDisplay(int, int);


//= main program function
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //= RGBA mode, depth mode, double buffer mode
    
    //= Init Window
    glutInitWindowSize(DEFAULT_W, DEFAULT_H); //= window size
    glutInitWindowPosition(0, 0); //= window position
    int window = glutCreateWindow("Lazuli Rogers | Robot Hunter");

    //= init lighting & shading
    initLightShade();
    //= init all textures
    initTextures();
    

    //= init sound engine
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        return -1;
    }
    //= init background music
    if (ma_sound_init_from_file(&engine, "./resources/sounds/DanceMusic.wav",
        MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC,
        NULL, NULL, &bgm) != MA_SUCCESS) {
        return -1;
    }
    ma_sound_set_looping(&bgm, MA_TRUE);
    if (soundOn) ma_sound_start(&bgm);

    //= depth functions
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST); //= enable depth test 

    //= display functions
    glutDisplayFunc(MyDisplay); //= call the display function
    glutReshapeFunc(ReshapeDisplay); //= call the resizing function
    glutIdleFunc(MyDisplay); //= set the display function as the idle function
    
    //= init input functions
    glutKeyboardFunc(KeyboardInputCallback); //= keyboard input function
    glutSpecialFunc(ProcessSpecialKeys); //= special key input function
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotion);

    //= init timer functions
    glutTimerFunc(16, bulletTimer, 0);
    glutTimerFunc(1000, gameTimer, 0);

    //= init main display loop
    glutMainLoop();
    ma_engine_uninit(&engine);
    return 1;
}

void MyDisplay(void) {
    //= set main viewport background color
    glClearColor(SkyBlue[0], SkyBlue[1], SkyBlue[2], 0);
    //= clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //= set viewport
    glViewport(0, 0, WINDOW_W, WINDOW_H);
   if (!paused) {
    if (gouraudShading) glShadeModel(GL_SMOOTH);
    else glShadeModel(GL_FLAT);

    //= draw main viewport
    if (!birdsEyeIsMain) { //= if birds-eye view is NOT currently in the main viewport, draw first person view
        glLoadIdentity();
        applyLighting();
        glPushMatrix();
        drawFirstPerson();
        glPopMatrix();
    }
    else { //= if birds-eye view is currently in the main viewport, draw it there
        glLoadIdentity();
        applyLighting();
        glPushMatrix();
        drawBirdsEye();
        glPopMatrix();
    }

    //= draw mini-viewport borders
    drawViewportBorder(
        0, WINDOW_H - float(WINDOW_H) * INFO_RATIO, //= x, y
        WINDOW_W, WINDOW_H * INFO_RATIO, //= width, height
        0.0f, 1.0f, 0.0f //= border color r, g, b
    );
    drawViewportBorder(
        WINDOW_W - WINDOW_W * ESV_RATIO, WINDOW_H - (WINDOW_H * ESV_RATIO + WINDOW_H * INFO_RATIO), //= x, y
        WINDOW_W * ESV_RATIO, WINDOW_H * ESV_RATIO, //= width, height
        1.0f, 0.0f, 0.0f //= border color r, g, b
    );

    //= draw mini-viewports
    glEnable(GL_SCISSOR_TEST);
    //= use scissor mode to cut out the location of the smaller viewport, preventing overlap
    glScissor(0, WINDOW_H - WINDOW_H * INFO_RATIO, WINDOW_W, WINDOW_H * INFO_RATIO);
    glClearColor(SILVER[0], SILVER[1], SILVER[2], 1); //= set sky color to pink
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //= clear color and depth buffers
    glDisable(GL_SCISSOR_TEST); //= make sure to disable scissor mode!
    drawGameInfoView(); //= call rear view drawing function


    glEnable(GL_SCISSOR_TEST);
    //= use scissor mode to cut out the location of the smaller viewport, preventing overlap
    glScissor(WINDOW_W - WINDOW_W * ESV_RATIO, WINDOW_H - (WINDOW_H * ESV_RATIO + WINDOW_H * INFO_RATIO), WINDOW_W * ESV_RATIO, WINDOW_H * ESV_RATIO);
    glClearColor(SkyLavender[0], SkyLavender[1], SkyLavender[2], 0); //= set sky color to lavender
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //= clear color and depth buffers
    glDisable(GL_SCISSOR_TEST); //= make sure to disable scissor mode!

    //= set viewport position and size
    glViewport(WINDOW_W - WINDOW_W * ESV_RATIO, WINDOW_H - (WINDOW_H * ESV_RATIO + WINDOW_H * INFO_RATIO), WINDOW_W * ESV_RATIO, WINDOW_H * ESV_RATIO);
    glMatrixMode(GL_PROJECTION); //= projection mode 
    glLoadIdentity(); //= load identity matrix
    gluPerspective(60.0, (double)(WINDOW_W / 2) / (WINDOW_H / 2), 0.1, 500.0); //= adjust perspective
    glMatrixMode(GL_MODELVIEW); //= back to model mode

    if (!birdsEyeIsMain) {
        glLoadIdentity();
        applyLighting();
        glPushMatrix();
        drawBirdsEye();
        glPopMatrix();
    } //= if the bird's-eye view is not in the main viewport, draw it here
    else {
        glLoadIdentity();
        applyLighting();
        glPushMatrix();
        drawFirstPerson();
        glPopMatrix();
    } //= if the bird's eye view is in the main viewport, draw the first-person view here
}
   else {
    glLoadIdentity();
    glPushMatrix();
    //glViewport(0, 0, WINDOW_W, WINDOW_H);
    drawPauseMenu();
    glPopMatrix();
    }

    //= swap buffers
    glutSwapBuffers();
}



