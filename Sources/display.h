//
// Created by kiki on 17/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H
#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "createmap.h"
#include "callback.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "camera.h"
#include "Material.h"


/*
 * Permet d'afficher sur l'écran le résultat de heightmapping grâce à OpenGL
 */
class Display{
private :
    int choiceMat;
public :
    int windowW;
    int windowH;

    float focale;
    float Near;
    float Far;
    Display();
    GLvoid clavier(unsigned char touche, int x, int y);
    GLvoid redimensionner(int w, int h);
    void initWindow(int argc, char *argv[]);
    int getWindowW();
    int getWindowH();

};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_DISPLAY_H
