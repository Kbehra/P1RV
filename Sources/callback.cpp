//
// Created by kiki on 31/10/2019.
//

#include "callback.h"


extern CreateMap map;
extern Display goDisplay;
extern Camera cam;

void keyBoard(unsigned char c, int x, int y){
    goDisplay.clavier(c, x, y);
}

void souris(int bouton, int etat, int x, int y){
    cam.mouseState(bouton, etat, x, y);
}

void deplacementSouris(int x, int y){
    cam.mouseMove(x, y);
}

GLvoid rezise(int w, int h) {
	goDisplay.redimensionner(w, h);
}


GLvoid affichage() {

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	// give a map a material
	map.afficher();
	Material(4);

	glLoadIdentity();
	glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
	glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);
	glScalef(1.0f+(cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100));

	// affichage des informations sur l'écran
	//std::string Zoom = std::to_string(cam.getZoom());


	//BitmapOutput(1.0, 1.0, Zoom, GLUT_BITMAP_TIMES_ROMAN_24); //debug

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