/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * main.cpp
 */
#include <Windows.h>
#include <iostream>

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

char* LINK_IMAGE = _strdup("C:/dev/P1RV/examples/Heightmap.jpeg");
char* LINK_SHADERVERT = _strdup("C:/Users/kilia/source/repos/P1RV/Sources/shader/shader.vert");
char* LINK_SHADERFRAG = _strdup("C:/Users/kilia/source/repos/P1RV/Sources/shader/shader.frag");

int main(int argc, char *argv[]) {

    // initialisation glut
    goDisplay.initWindow(argc, argv);


    ImageJPEG monimage;

    bool loaderimage = monimage.LoadJPEG(LINK_IMAGE);

    // création de la map
    map = CreateMap(monimage);
    map.generateMap();

  



  
    glutMainLoop();

    return 0;
}

