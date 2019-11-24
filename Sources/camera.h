//
// Created by kiki on 20/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H
#define GLUT_DISABLE_ATEXIT_HACK
#pragma once
#include <Windows.h>
#include <GL/freeglut.h>



class Camera{
public :
    // constructeur
    Camera();
    // destructeur
    ~Camera();
    //
    GLvoid mouseState(int bouton, int etat, int x, int y);
    //
    GLvoid mouseMove(int x, int y);

    GLfloat getAngleX();
    GLfloat getAngleY();
	GLfloat getZoom();

private:
    GLfloat pointSize;
    // Rotations autour de X et Y
    GLfloat angleX;
    GLfloat angleY;
	GLfloat zoom;
    GLint oldX;
    GLint oldY;
    GLboolean boutonClickLeft;
	GLboolean boutonClickRight;

};

#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H
