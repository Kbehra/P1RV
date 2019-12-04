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

//#include <QApplication>
#include "qapplication.h"
#include <QDebug>
#include "Sources/loadjpeg.h"
#include "Sources/createmap.h"
#include "Sources/mydisplay.h"
#include "Sources/camera.h"
#include "Sources/interface.h"


// Variables globales
CreateMap my_map;
MyDisplay go_display;
Camera cam;

// Liens vers le fichier à charger
char* LINK_IMAGE = strdup("../examples/Heightmap.jpeg");
char* LINK_TEX = strdup("../examples/texture1.jpeg");

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    // initialisation glut
    go_display.initWindow(argc, argv);


    ImageJPEG monimage;

    bool loaderimage = monimage.loadJPEG(LINK_IMAGE);

    // création de la my_map
    my_map = CreateMap(monimage);
    my_map.generateMap();

  

    glutMainLoop();

    return app.exec();
}

