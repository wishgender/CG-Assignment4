//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= drawScene.cpp

//= Dependencies =//
#include "drawScene.hpp"
#include <GL/glut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <stb_image.h>
#include "grid.hpp"
#include "input.hpp"

char displayText[100];



//= function to get bots
std::vector<Robot*> getBots() {
    return bots;
}

//= helper function for initializing the bots
template<typename T>
void refillVec(std::vector<T>& empty, std::vector<T> full) {
    for (auto i = 0; i < full.size(); i++) {
        empty.push_back(full[i]);
    }
}

void drawString(float posX, float posY, void* font, const char* string) {
    glRasterPos2f(posX, posY);
    for (char* c = (char*)string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void displayControls() {
    snprintf(displayText, sizeof(displayText), CONTROLS_TEXT_5);
    glColor3f(BLACK[0], BLACK[1], BLACK[2]);
    drawString(-1.9f, -1.3f, GLUT_BITMAP_HELVETICA_10, displayText);
    snprintf(displayText, sizeof(displayText), CONTROLS_TEXT_4);
    glColor3f(BLACK[0], BLACK[1], BLACK[2]);
    drawString(-1.9f, -0.725f, GLUT_BITMAP_HELVETICA_10, displayText);
    snprintf(displayText, sizeof(displayText), CONTROLS_TEXT_3);
    glColor3f(BLACK[0], BLACK[1], BLACK[2]);
    drawString(-1.9f, -0.15f, GLUT_BITMAP_HELVETICA_10, displayText);
    snprintf(displayText, sizeof(displayText), CONTROLS_TEXT_2);
    glColor3f(BLACK[0], BLACK[1], BLACK[2]);
    drawString(-1.9f, 0.425f, GLUT_BITMAP_HELVETICA_10, displayText);
    snprintf(displayText, sizeof(displayText), CONTROLS_TEXT_1);
    glColor3f(BLACK[0], BLACK[1], BLACK[2]);
    drawString(-1.9f, 1.0f, GLUT_BITMAP_HELVETICA_10, displayText);
}

//= draw the axes
void drawAxes() {
    glBegin(GL_LINES);
    // x axis
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(50, 0, 0);
    // y axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 50, 0);
    // z axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 50);
    glEnd();
}

//= draw the ground
void drawGround() {
    glMatrixMode(GL_MODELVIEW);

    if (shapeMode == WIRE) { //= wireframe mode ground
        glColor3f(GroundHue[0], GroundHue[1], GroundHue[2]);
        glBegin(GL_LINES);
        glVertex3f(-float(GRID_SIZE / 2), 0.0f, float(GRID_SIZE / 2));
        glVertex3f(float(GRID_SIZE/2), 0.0f, float(GRID_SIZE/2));

        glVertex3f(float(GRID_SIZE/2), 0.0f, float(GRID_SIZE/2));
        glVertex3f(float(GRID_SIZE/2), 0.0f, -float(GRID_SIZE/2));

        glVertex3f(float(GRID_SIZE/2), 0.0f, -float(GRID_SIZE/2));
        glVertex3f(-float(GRID_SIZE/2), 0.0f, -float(GRID_SIZE/2));

        glVertex3f(-float(GRID_SIZE/2), 0.0f, -float(GRID_SIZE/2));
        glVertex3f(-float(GRID_SIZE/2), 0.0f, float(GRID_SIZE/2));
        glEnd();
    }
    else if (shapeMode == VERTICES) { //= vertex mode ground
        glBegin(GL_POINTS);
        glColor3f(GroundHue[0], GroundHue[1], GroundHue[2]);
        glPointSize(6.0f);
        glVertex3f(-float(GRID_SIZE / 2), 0.0f, float(GRID_SIZE / 2));
        glVertex3f(float(GRID_SIZE / 2), 0.0f, float(GRID_SIZE / 2));
        glVertex3f(float(GRID_SIZE / 2), 0.0f, -float(GRID_SIZE / 2));
        glVertex3f(-float(GRID_SIZE / 2), 0.0f, -float(GRID_SIZE / 2));
        glEnd();
    }
    else
    { //= solid mode ground
        glEnable(GL_TEXTURE_2D);
        glColor3f(WHITE[0], WHITE[1], WHITE[2]);
        glBindTexture(GL_TEXTURE_2D, groundColor);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);    glVertex3f(-float(GRID_SIZE / 2), 0.0f, -float(GRID_SIZE / 2));
        glTexCoord2f(7.0f, 0.0f);    glVertex3f(float(GRID_SIZE / 2), 0.0f, -float(GRID_SIZE / 2));
        glTexCoord2f(7.0f, 7.0f);    glVertex3f(float(GRID_SIZE / 2), 0.0f, float(GRID_SIZE / 2));
        glTexCoord2f(0.0f, 7.0f);    glVertex3f(-float(GRID_SIZE/2), 0.0f, float(GRID_SIZE/2));
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawCameraBarrel(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
   
    //= Draw cylinder
    glColor4d(0.4, 0.4, 0.4, 1); //= set camera color
    gluCylinder(quad, radius, radius, height, 16, 32);

    //= Draw face
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // flip to face downward
    gluDisk(quad, 0.0, radius, 16, 1);
    glPopMatrix();

    //= Draw lens
    glPushMatrix();
    glColor4d(0.0, 0.0, 0.0, 0.0);
    glTranslatef(0.0f, 0.0f, -0.001f);
    gluDisk(quad, 0.0, radius / 2, 32, 1);
    glPopMatrix();

    //= Outline the cylinder
    gluQuadricDrawStyle(quad, GLU_LINE);
    glColor4d(0.2, 0.2, 0.2, 1); //= set camera edge color
    gluCylinder(quad, radius, radius, height, 24, 1);

    gluDeleteQuadric(quad);
}

void drawCamera() { //= draw the camera as a gray box
    glPushMatrix();

    glTranslatef(CAMERA_X, CAMERA_Y - 2, CAMERA_Z); //= translate to camera position
    glRotatef(
        (-firstPersonAngle * 180.0f / PI), 0.0f, 1.0f, 0.0f); //= rotate based on first-person view angle
    
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(3.0f, 0.5f, -4.0f);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(GRAY[0], GRAY[1], GRAY[2]);
    glBindTexture(GL_TEXTURE_2D, gunMetal);
    renderNode(pistol->mRootNode, pistol);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    if (showColliders) {
        glPushMatrix();
        glColor3f(playerCollider.getValues()[0], playerCollider.getValues()[1], playerCollider.getValues()[2]);
        glutWireSphere(playerRadius, 6, 6);
        glPopMatrix();
    }

    //= draw the camera barrel
    glPushMatrix(); 
    glTranslatef(0.0f, 0.0f, -1.51f);
    drawCameraBarrel(0.5f, 0.5f);
    glPopMatrix();

    //= draw the camera body
    glColor4d(0.4, 0.4, 0.4, 1); //= set camera color
    glutSolidCube(2); //= draw the cube
    glColor4d(0.2, 0.2, 0.2, 1); //= set camera edge color
    glutWireCube(2); //= draw the cube's edges

    glPopMatrix();
}

//= draw the first-person view
void drawFirstPerson() {
    glLoadIdentity();

    //= set the view using the camera position and rotation variables
    gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, CAMERA_X + lx, CAMERA_Y, CAMERA_Z + lz, 0.0f, 5.0f, 0.0f);
    
    //= draw sky background
    renderSkyTexture();
    //= re-enable depth test
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslated(CAMERA_X + lx+3.0, CAMERA_Y-0.5, CAMERA_Z + lz-4.0);
    glRotatef(
        (-firstPersonAngle * 180.0f / PI), 0.0f, 1.0f, 0.0f); //= rotate based on first-person view angle
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(GRAY[0], GRAY[1], GRAY[2]);
    glBindTexture(GL_TEXTURE_2D, gunMetal);
    renderNode(pistol->mRootNode, pistol);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();

    drawGround(); //= draw the ground

    //= draw aiming reticle
    glPushMatrix();
    glColor3f(WHITE[0], WHITE[1], WHITE[2]);
    glTranslated(CAMERA_X + lx, CAMERA_Y, CAMERA_Z + lz);
    glutSolidSphere(0.01, 12, 12);
    glPopMatrix();
    

    if (showAxes) {//= if axes are displayed, draw them
        drawAxes();
    }

    //= initialize local vectors of the body color and head color constant vectors
    std::vector<Color> bodyColors = BodyHues;
    std::vector<Color> headColors = HeadHues;

    //= if the vector of bots is not full
    if (bots.size() < MAX_ROBOTS) {
        //= in the rare case that the points were unable to be placed, place new ones
        while (!success) success = gameField.placeEnemies(MAX_ROBOTS, robotRadius * 2, 500);

        //= iterate over the vector of points
        for (auto i = 0; i < gameField.getPosSize(); i++) {
            if (bodyColors.empty()) refillVec(bodyColors, BodyHues);
            if (headColors.empty()) refillVec(headColors, HeadHues);

            int colorIndex = rand() % bodyColors.size(); //= randomize the body color
            Color newBodyColor = bodyColors[colorIndex]; //= initialize a color object using the color index
            std::vector<Color>::const_iterator bodyIter = bodyColors.begin(); //= initialize an iterator
            for (int i = 0; i < colorIndex; i++) {
                bodyIter++; //= move the iterator to the position of the color index
            }
            colorIndex = rand() % headColors.size(); //= randomize the body color (no need to init a new variable)
            Color newHeadColor = headColors[colorIndex]; //= initialize a color object using the color index
            std::vector<Color>::const_iterator headIter = headColors.begin(); //= initialize an iterator
            for (int i = 0; i < colorIndex; i++) {
                headIter++; //= move the iterator to the position of the color index
            }
            //= initialize a new robot with the randomized traits and add it to the vector
            bots.push_back(new Robot(gameField[i], newBodyColor, newHeadColor, AQUA));
            //= erase the traits from the local vectors to ensure uniqueness
            bodyColors.erase(bodyIter);
            headColors.erase(headIter);
        }
    }

    //= draw each robot
    for (const auto& b : bots) {
        glPushMatrix();
        b->drawRobot();
        glPopMatrix();
    }
    for (const auto& b : bullets) b.draw();
}

void drawBirdsEye() {
    static bool first = true;
    if (first) {
        recomputeOrientation();
        first = false;
    }

    glLoadIdentity();
    applyLighting();
    //= set view from above
    gluLookAt(ESV_X, ESV_Y, ESV_Z, 0, 5.0f, 0, 0, 1, 0);
    
    renderSkyTexture();
    glEnable(GL_DEPTH_TEST);


    drawGround(); //= draw the ground

    glPushMatrix();
    glTranslated(CAMERA_X + 1, CAMERA_Y - 2, CAMERA_Z + 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    drawCamera(); //= draw the camera

    if (showAxes) { //= if axes are displayed, draw them
        drawAxes();
    }


    //= draw each robot
    for (const auto& b : bots) b->drawRobot();
    //= draw bullets
    for (const auto& b : bullets) b.draw();
}

void drawGameInfoView() {
    //= set the viewport of the rear view
    GLint newY = WINDOW_H - WINDOW_H * INFO_RATIO;
    GLint newH = WINDOW_H * INFO_RATIO;
    glViewport(0, newY, WINDOW_W, newH);
    glMatrixMode(GL_PROJECTION); //= projection mode
    glLoadIdentity();
    //= set the perspective
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW); //= back to model mode
    glLoadIdentity();
    if (!gameOver) {
        displayControls();

        snprintf(displayText, sizeof(displayText), MISSION_TEXT);
        glColor3f(BLACK[0], BLACK[1], BLACK[2]);
        drawString(0.7f, 1.0f, GLUT_BITMAP_HELVETICA_12, displayText);

        snprintf(displayText, sizeof(displayText), SCORE_TEXT, robotsKilled, MAX_ROBOTS);
        glColor3f(NAVY[0], NAVY[1], NAVY[2]);
        drawString(0.8f, 0.2f, GLUT_BITMAP_HELVETICA_12, displayText);

        snprintf(displayText, sizeof(displayText), TIME_LEFT_TEXT, timeLeft, TIME_LIMIT);
        glColor3f(MAROON[0], MAROON[1], MAROON[2]);
        drawString(0.8f, -0.6f, GLUT_BITMAP_HELVETICA_12, displayText);

        snprintf(displayText, sizeof(displayText), BULLET_SPEED_TEXT, TEXT_VEC[bulletSpeed]);
        glColor3f(OLIVE[0], OLIVE[1], OLIVE[2]);
        drawString(0.8f, -1.4f, GLUT_BITMAP_HELVETICA_12, displayText);
    }
    else if (robotsKilled == MAX_ROBOTS){
        snprintf(displayText, sizeof(displayText), GAME_OVER_TEXT);
        glColor3f(BLACK[0], BLACK[1], BLACK[2]);
        drawString(-0.15f, 1.0f, GLUT_BITMAP_HELVETICA_12, displayText);

        snprintf(displayText, sizeof(displayText), SUCCESS_TEXT);
        glColor3f(GREEN[0], GREEN[1], GREEN[2]);
        drawString(-0.3f, -1.0f, GLUT_BITMAP_HELVETICA_12, displayText);
    }
    else {
        snprintf(displayText, sizeof(displayText), GAME_OVER_TEXT);
        glColor3f(BLACK[0], BLACK[1], BLACK[2]);
        drawString(-0.15f, 1.0f, GLUT_BITMAP_HELVETICA_12, displayText);

        snprintf(displayText, sizeof(displayText), FAIL_TEXT);
        glColor3f(RED[0], RED[1], RED[2]);
        drawString(-0.3f, -1.0f, GLUT_BITMAP_HELVETICA_12, displayText);
    }
}

//= function to draw the borders of the mini-viewports
void drawViewportBorder(int x, int y, int width, int height, float r, float g, float b) {
    //= Set projection for 2D drawing
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);

    //= Switch to model view
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //= Disable depth test so lines draw over everything
    glDisable(GL_DEPTH_TEST);

    //= Set border color
    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP); //= line loop mode
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();

    //= Re-enable depth test
    glEnable(GL_DEPTH_TEST);

    //= Restore previous projection and model matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void bulletTimer(int value) {
    for (auto& b : bullets)
        b.update();

    for (auto& b : bullets) {
        if (!b.isActive()) continue;

        for (auto& r : bots) {
            if (!r->getBeenShot()) {
                if (collision({ b.getX(), b.getZ() }, r->getPosition(), 0.5f, robotRadius)) {
                    b.deactivate();
                    r->setBulletCollision(true);
                    r->kill();
                    gameScore += 10;
                    robotsKilled++;
                    if (robotsKilled == MAX_ROBOTS) gameOver = true;
                    break;
                }
            }
        }
    }
    for (auto& r : bots) r->updateDeath();

    // remove inactive or out-of-bounds bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](Bullet& b) {
            return !b.isActive() ||
                fabs(b.getX()) > 200 ||  // failsafe
                fabs(b.getZ()) > 200;
        }),
        bullets.end());

    glutPostRedisplay();
    glutTimerFunc(16, bulletTimer, 0);
}

void moveEnemiesTimer(int value) {
    if (!movementToggle) {
        isMoveTimerActive = false;
        return;
    }
    //= progress movement of each robot
    for (auto& r : bots)
        r->updateMovement();

    //= periodically decide new directions
    static int stepCounter = 0;
    if (++stepCounter % 120 == 0) { // every ~20 frames
        gameField.progressGrid();
    }

    glutPostRedisplay();
    glutTimerFunc(16, moveEnemiesTimer, 0);
}

void gameTimer(int value) {
    if (gameOver) {
        isGameTimerActive = false;
        return;
    }

    if (timeLeft > 0) {
        if (!paused) timeLeft--;
        glutPostRedisplay();
        glutTimerFunc(1000, gameTimer, 0); //= call again in 1 second
    }
    else {
        gameOver = true;
    }
}

void renderSkyTexture() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(1, 0);
    glTexCoord2f(1, 1); glVertex2f(1, 1);
    glTexCoord2f(0, 1); glVertex2f(0, 1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}



void renderNode(aiNode* node, const aiScene* scene) {
    //std::cout << "inside rendernode\n";
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        glBegin(GL_TRIANGLES);
        for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
            const aiFace& face = mesh->mFaces[t];

            for (unsigned int j = 0; j < 3; j++) {
                unsigned int idx = face.mIndices[j];
                aiVector3D pos = mesh->mVertices[idx];
                aiVector3D normal = mesh->mNormals[idx];

                if (mesh->mTextureCoords[0]) {
                    aiVector3D uv = mesh->mTextureCoords[0][idx];
                    glTexCoord2f(uv.x, uv.y);
                }

                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(pos.x, pos.y, pos.z);
            }
        }
        glEnd();
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        renderNode(node->mChildren[i], scene);
    }
}

void applyLighting() {
    if (directionalLight) { //= sunlight
        glLightfv(GL_LIGHT0, GL_POSITION, sunDirection);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);
        //= no distance attenuation w/ sun
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    }
    else { //= point light
        glLightfv(GL_LIGHT0, GL_POSITION, bulbPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, bulbAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, bulbDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, bulbSpecular);

        //= Enable distance attenuation
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);
    }
}
