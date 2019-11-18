/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * main.cpp
 */
#include <Windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "sources/loadjpeg.h"
#include "sources/createmap.h"
#include "sources/display.h"
#include "sources/camera.h"
#include "sources/callback.h"

// Variables globales
CreateMap map;
Display goDisplay;
Camera cam;

// Liens vers le fichier à charger
//char* LINK_IMAGE = "/home/kiki/CLionProjects/P1RV_Heightmaps_BEHRA_MARAVAT/examples/Heightmap3.jpeg";
char* LINK_IMAGE = _strdup("C:/dev/P1RV/examples/Heightmap.jpeg");

int DEPUISLEWEB;

int main(int argc, char *argv[]) {

    // initialisation glut
    goDisplay.initWindow(argc, argv);

    ImageJPEG monimage;

    bool loaderimage = monimage.LoadJPEG(LINK_IMAGE);
    std :: cout << monimage.getX() << "  " << monimage.getY() << std :: endl;

    // création de la map
    map = CreateMap(monimage);
    map.generateMap();

    float ambientStrenght =0.1;



    // fonctions de callback
    glutDisplayFunc(affichage);
    glutReshapeFunc(redimensionner);

    glutKeyboardFunc(KeyBoard);
    glutMouseFunc(souris);
    glutMotionFunc(deplacementSouris);


    // Correction de la perspective
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    return 0;
}

