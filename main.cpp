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

#include "Sources/loadjpeg.h"
#include "Sources/createmap.h"
#include "Sources/display.h"
#include "Sources/camera.h"


// Variables globales
CreateMap map;
Display goDisplay;
Camera cam;

// Liens vers le fichier à charger
char* LINK_IMAGE = strdup("../examples/Heightmap4.jpeg");
char* LINK_TEX = strdup("../examples/texture1.jpeg");

int main(int argc, char *argv[]) {

    // initialisation glut
    goDisplay.initWindow(argc, argv);


    ImageJPEG monimage;

    bool loaderimage = monimage.loadJPEG(LINK_IMAGE);

    // création de la map
    map = CreateMap(monimage);
    map.generateMap();

  

    glutMainLoop();

    return 0;
}

