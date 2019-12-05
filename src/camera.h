/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * camera.h
 */

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H

#ifdef __linux__
#elif __WIN32
#define GLUT_DISABLE_ATEXIT_HACK
#include <Windows.h>
#endif
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
    GLfloat point_size;
    // Rotations autour de X et Y
    GLfloat angle_x;
    GLfloat angle_y;
	GLfloat zoom;
    GLint old_x;
    GLint old_y;
    GLboolean bouton_click_left;
	GLboolean bouton_click_right;

};

#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CAMERA_H
