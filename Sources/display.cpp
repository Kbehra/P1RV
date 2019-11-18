//
// Created by kiki on 17/10/2019.
//
#include <Windows.h>
#include <iostream>
#include <math.h>


#include "display.h"
#include "createmap.h"
#include "camera.h"
#include "Material.h"


extern Camera cam;
extern CreateMap map;
extern Display goDisplay;
#define VITESSE_DEPLACEMENT 0.1
#define VITESSE_ROTATION 0.1

Display :: Display() {
    windowW = 1080;
    windowH = 960;

    focale = 10.0f;
    Near = 0.0f;
    Far = 0.0f;

    //
    choiceMat = 4;


}

void Display :: initWindow(int argc, char *argv[]){
    // initialisation de GLUT
    glutInit(&argc, argv);
    // choix du mode d'affichage (ici RGB)
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    // position initiale de la fenetre GLUT
    glutInitWindowPosition(0,0);
    // taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // création de la fenetre GLUT
    glutCreateWindow("Heightmap");

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialement on desactive le Z-buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);


    // Lumiere
    GLfloat lightpos[] = { 0.0f, 0.0f, 15.0f };
    GLfloat lightcolor[] = { 1.0f, 1.0f, 0.0f };
    GLfloat ambcolor[] = { 0.0f, 0.0f, 1.0f };

    glEnable(GL_LIGHTING);                               // enable lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);     // ambient light

    glEnable(GL_LIGHT0);                                 // enable light source
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);           // config light source
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightcolor);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

    // Shading model
    glShadeModel(GL_SMOOTH);

}

GLvoid Display :: clavier (unsigned char touche, int x, int y){
    // Suivant les touches pressees, nous aurons un comportement different de l'application
    // ESCAPE ou 'q' : fermera l'application
    // 'p' : affichage du carre plein
    // 'f' : affichage du carre en fil de fer
    // 's' : affichage des sommets du carre
    switch(touche)
    {
        case 'z':
            std::cout<<"Z"<<std::endl;
            break;
        case 'q':
            std::cout<<"Q"<<std::endl;
            break;
        case 's':
            std::cout<<"S"<<std::endl;
            break;
        case 'd':
            glEnable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'w':
            std::cout<<"w"<<std::endl;
            glDisable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;

        case 'e':
            break;
        case 'm':
            // change de the default material
            choiceMat = (choiceMat + 1) % 5;
            Material((int)choiceMat);
            break;
        default:
            break;
    }
    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();
}

GLvoid Display :: redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;

    // eviter une division par 0
    if(windowH==0)
        windowH = 1;

    float ratio = (float)windowW / (float)windowH;
    std::cout << "Ratio : " << ratio << std::endl;

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, windowW, windowH);

    // Mise en place de la perspective
    gluPerspective(focale, ratio, Near, Far);


    // Placement de la caméra
    //gluLookAt(-1, 1, 2, 0, 0, 0, 1, 1, 0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}


int Display :: getWindowW() {
    return windowW;
}
int Display ::getWindowH() {
    return windowH;
}

/*
 *
 */
GLvoid affichage(){

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Shader mapShader("shader.vert", "shader.frag");

    glMatrixMode(GL_MODELVIEW);

    // give a map a material
	//map.init(&mapShader);
    map.afficher();
    //Material(4);

    glLoadIdentity();
    glRotatef(-cam.getAngleY(),1.0f,0.0f,0.0f);
    glRotatef(-cam.getAngleX(),0.0f,1.0f,0.0f);

    //glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

GLvoid redimensionner(int w, int h){
    goDisplay.redimensionner(w, h);
}

