/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * main.cpp
 */

#ifdef __linux__
#include <string>
#include <memory.h>
#elif _WIN32
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#endif

#include <iostream>
#include "Sources/loadjpeg.h"
#include "Sources/createmap.h"
#include "Sources/display.h"
#include "Sources/camera.h"
#include "Sources/callback.h"

// Variables globales
CreateMap map;
Display goDisplay;
Camera cam;

// Liens vers le fichier à charger

char* LINK_IMAGE = strdup("../examples/Heightmap.jpeg");
char* LINK_SHADERVERT = strdup("C:/Users/kilia/P1RV/Sources/shader/shader.vert");
char* LINK_SHADERFRAG = strdup("C:/Users/kilia/P1RV/Sources/shader/shader.frag");


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

