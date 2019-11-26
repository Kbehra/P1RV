//
// Created by kiki on 20/10/2019.
//

#include "camera.h"
#include "display.h"

extern Display goDisplay;

Camera::Camera() {
    pointSize = 1.0f;

    angleX = 0.0f;                  // Rotations autour de X et Y
    angleY = 0.0f;
	zoom = 1.0;
    oldX = 0;
    oldY = 0;
    boutonClickLeft = false;
	boutonClickRight = false;
}
Camera::~Camera() {
}

// Fonction de rappel de la souris
GLvoid Camera :: mouseState(int bouton, int etat, int x, int y) {
    // Test pour voir si le bouton gauche de la souris est appuyé
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
        boutonClickLeft = true;
        oldX = x;
        oldY = y;
    }
    // si on relache le bouton gauche
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
        boutonClickLeft = false;
    }
	if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_DOWN) {
		boutonClickRight = true;
		oldX = x;
		oldY = y;
	}
	// si on relache le bouton gauche
	if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_UP) {
		boutonClickRight = false;
	}
}
GLvoid Camera:: mouseMove(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace
    // alors on doit modifier les angles de rotations du cube
    // en fonction de la derniere position de la souris
    // et de sa position actuelle
    if(boutonClickLeft) {
        angleX += (x-oldX);
        angleY += (y-oldY);
        // Appeler le re-affichage de la scene OpenGL
        glutPostRedisplay();
    }
	if (boutonClickRight) {
		zoom += (x - oldX)+(y - oldY);
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
GLfloat Camera::getZoom() {
	return zoom;
}
