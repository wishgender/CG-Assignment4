#pragma once
//= Lazuli Rogers | aroger52
//= due 11-25-2025
//= Computer Graphics - Assignment 4
//= utils.cpp

//= utility functions used primarily by the main function

//= Dependencies =//
#include <iostream>
#include <GL/glut.h>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <miniaudio.h>
#include "globalVars.hpp"

GLuint skyTexture;
GLuint gunMetal;
GLuint headTexture;
GLuint bodyTexture;
GLuint groundColor;


void setSkyTexture(void) {
    unsigned char* image_data;
    int w, h, channels;

    //= load image data from file
    image_data = stbi_load("./resources/textures/sky.jpg", &w, &h, &channels, STBI_rgb);

    if (!image_data) {
        std::cerr << "Failed to load image: sky.jpg\n";
        return;
    }

    //= gen & bind texture
    glGenTextures(1, &skyTexture);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //= set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //= set texture format
    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;

    //= set texture from image
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image_data);
    //= unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //= free image data
    stbi_image_free(image_data);
}


void setGroundTexture(void) {
    unsigned char* image_data;
    int w, h, channels;

    //= load image data from file
    image_data = stbi_load("./resources/textures/rock_final.png", &w, &h, &channels, STBI_rgb);

    if (!image_data) {
        std::cerr << "Failed to load image: rock_final.jpg\n";
        return;
    }

    //= gen & bind texture
    glGenTextures(1, &groundColor);
    glBindTexture(GL_TEXTURE_2D, groundColor);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //= set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //= set texture format
    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;

    //= set texture from image
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image_data);
    //= unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //= free image data
    stbi_image_free(image_data);
}


void setPistolTexture(void) {
    unsigned char* image_data;
    int w, h, channels;

    //= load image data from file
    image_data = stbi_load("./resources/textures/gun-metal.png", &w, &h, &channels, 1);

    if (!image_data) {
        std::cerr << "Failed to load image: gun-metal.png\n";
        return;
    }

    //= gen & bind texture
    glGenTextures(1, &gunMetal);
    glBindTexture(GL_TEXTURE_2D, gunMetal);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //= set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //= set texture format
        //GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
    GLenum format = GL_LUMINANCE;

    //= set texture from image
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image_data);
    //= unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //= free image data
    stbi_image_free(image_data);
}

void setHeadTexture(void) {
    unsigned char* image_data;
    int w, h, channels;

    //= load image data from file
    image_data = stbi_load("./resources/textures/crystal1.png", &w, &h, &channels, 1);

    if (!image_data) {
        std::cerr << "Failed to load image: crystal1.png\n";
        return;
    }

    //= gen & bind texture
    glGenTextures(1, &headTexture);
    glBindTexture(GL_TEXTURE_2D, headTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //= set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //= set texture format
    GLenum format = GL_LUMINANCE;

    //= set texture from image
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image_data);
    //= unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //= free image data
    stbi_image_free(image_data);
}

void setBodyTexture(void) {
    unsigned char* image_data;
    int w, h, channels;
    image_data = stbi_load("./resources/textures/crystal3.jpg", &w, &h, &channels, 1);

    if (!image_data) {
        std::cerr << "Failed to load image: crystal3.jpg\n";
        return;
    }

    //= gen & bind texture
    glGenTextures(1, &bodyTexture);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //= set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //= set texture format
    GLenum format = GL_LUMINANCE;

    //= set texture from image
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image_data);
    //= unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //= free image data
    stbi_image_free(image_data);
}

void loadBulletModel() {
    //= load bullet OBJ
    bullet = bulletImporter.ReadFile("./resources/models/Bullet.obj",
        aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!bullet) {
        std::cerr << "Assimp error: " << bulletImporter.GetErrorString() << std::endl;
    }
}

void initTextures(void) {
    setSkyTexture();
    setGroundTexture();
    setPistolTexture();
    setHeadTexture();
    setBodyTexture();
}

void initLightShade(void) {

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    //= Make specular color come from glMaterial
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64.0f);

}


