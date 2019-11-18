//
// Created by kiki on 20/10/2019.
//

#include "camera.h"
#include "display.h"

extern Display goDisplay;

Camera::Camera() {
    pointSize = 1.0f;
    // Rotations autour de X et Y
    angleX = 0.0f;
    angleY = 0.0f;
    oldX = 0;
    oldY = 0;
    boutonClick = false;

}
Camera::~Camera() {
}

// Fonction de rappel de la souris
GLvoid Camera :: mouseState(int bouton, int etat, int x, int y) {
    // Test pour voir si le bouton gauche de la souris est appuyé
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
        boutonClick = true;
        oldX = x;
        oldY = y;
    }
    // si on relache le bouton gauche
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
        boutonClick = false;
    }
}
GLvoid Camera:: mouseMove(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace
    // alors on doit modifier les angles de rotations du cube
    // en fonction de la derniere position de la souris
    // et de sa position actuelle
    if(boutonClick) {
        angleX += (x-oldX);
        angleY += (y-oldY);
        // Appeler le re-affichage de la scene OpenGL
        glutPostRedisplay();
    }
    // Mise a jour des anciennes positions de la souris en X et Y
    oldX = x;
    oldY = y;
}

GLfloat Camera :: getAngleX(){
    return angleX;
}
GLfloat Camera :: getAngleY(){
    return angleY;
}

