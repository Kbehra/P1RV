/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * callback.cpp
 */

#include "callback.h"


extern CreateMap my_map;
extern MyDisplay go_display;
extern Camera cam;

void keyBoard(unsigned char c, int x, int y){
    go_display.clavier(c, x, y);
}

void souris(int bouton, int etat, int x, int y){
    cam.mouseState(bouton, etat, x, y);
}

void deplacementSouris(int x, int y){
    cam.mouseMove(x, y);
}

GLvoid rezise(int w, int h) {
	go_display.redimensionner(w, h);
}


GLvoid affichage() {

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// give a my_map a material
	my_map.afficher();

	glLoadIdentity();
	glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
	glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);
	glScalef(1.0f+(cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100));

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void BitmapOutput(float x, float y, std::string string, void* font)
{
	int len, i; // len donne la longueur de la cha�ne de caract�res
	glRasterPos2f(x, y); // Positionne le premier caract�re de la cha�ne
	//len = (int) strlen(string); // Calcule la longueur de la cha�ne
	len = string.length();
	for (i = 0; i < len; i++) glutBitmapCharacter(font, string[i]); // Affiche chaque caract�re de la cha�ne
}