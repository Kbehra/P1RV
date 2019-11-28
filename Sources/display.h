/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * display.h
 */

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H

#ifdef __linux__
#elif _WIN32
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#endif
#include <iostream>
#include <math.h>
#include "createmap.h"
#include "callback.h"
#include <GL/freeglut.h>
#include "camera.h"
#include "material.h"


/*
 * Permet d'afficher sur l'écran le résultat de heightmapping grâce à OpenGL
 */

class Display{
private :
    int choice_mat;
    bool change_shade_model;
    bool projection;
    float pas;

    int window_width;
    int window_high;

    float left;
    float right;
    float top;
    float bottom;

    float focale;
    float near;
    float far;

public :
    //Methods
    Display();

    GLvoid applyLights();
    GLvoid clavier(unsigned char touche, int x, int y);
    GLvoid redimensionner(int w, int h);
    void initWindow(int argc, char *argv[]);
    int getWindowW();
    int getWindowH();

};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H
