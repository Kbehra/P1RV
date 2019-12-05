/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * camera.cpp
 */

#include "camera.h"
#include <iostream>     // --debug

Camera::Camera() {
    point_size = 1.0f;

    angle_x = 0.0f;                  // Rotations autour de X et Y
    angle_y = 0.0f;
	zoom = 1.0;
    old_x = 0;
    old_y = 0;
    bouton_click_left = false;
    bouton_click_right = false;
}
Camera::~Camera() {
}

// Fonction de rappel de la souris
GLvoid Camera :: mouseState(int bouton, int etat, int x, int y) {
    // Test pour voir si le bouton gauche de la souris est appuyé
    std::cout << " etat souris "<<bouton<<" "<<etat<<"  "<<x<<" "<<y<< std::endl;

    if (bouton == Qt::LeftButton && etat == QEvent::MouseButtonPress) {
        bouton_click_left = true;
        old_x = x;
        old_y = y;
    }
    // si on relache le bouton gauche
    if (bouton == Qt::LeftButton && etat == QEvent::MouseButtonRelease) {
        bouton_click_left = false;
    }
	if (bouton == Qt::RightButton && etat == Qt::Key_Down) {
        bouton_click_right = true;
        old_x = x;
        old_y = y;
	}
	// si on relache le bouton gauche
	if (bouton == Qt::RightButton && etat == Qt::Key_Up) {
        bouton_click_right = false;
	}
}
GLvoid Camera:: mouseMove(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace
    // alors on doit modifier les angles de rotations du cube
    // en fonction de la derniere position de la souris
    // et de sa position actuelle
    if(bouton_click_left) {
        angle_x += (x - old_x);
        angle_y += (y - old_y);
        // Appeler le re-affichage de la scene OpenGL
    }
	if (bouton_click_right) {
		zoom += (x - old_x) + (y - old_y);
		// Appeler le re-affichage de la scene OpenGL

	}
    // Mise a jour des anciennes positions de la souris en X et Y
    old_x = x;
    old_y = y;
}

GLfloat Camera :: getAngleX(){
    return angle_x;
}
GLfloat Camera :: getAngleY(){
    return angle_y;
}
GLfloat Camera::getZoom() {
	return zoom;
}
