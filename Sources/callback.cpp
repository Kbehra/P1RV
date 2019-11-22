//
// Created by kiki on 31/10/2019.
//

#include "callback.h"
#include "shader.h"

extern CreateMap map;
extern Display goDisplay;
extern Camera cam;
extern char* LINK_SHADERVERT;
extern char* LINK_SHADERFRAG;

void KeyBoard(unsigned char c, int x, int y){
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

	Shader mapShader(LINK_SHADERVERT, LINK_SHADERFRAG);

	glMatrixMode(GL_MODELVIEW);

	// give a map a material
	//map.init(&mapShader);
	map.afficher();
	//Material(4);

	glLoadIdentity();
	glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
	glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);

	//glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}