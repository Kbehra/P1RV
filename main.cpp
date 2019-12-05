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

#include <QApplication>
#include "Sources/loadjpeg.h"
#include "Sources/createmap.h"
#include "Sources/mydisplay.h"
#include "Sources/camera.h"
#include "Sources/mymainwindow.h"


// Variables globales
Camera cam;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MyMainWindow fenetre;

    fenetre.show();

    // initialisation glut
    //go_display.initWindow(argc, argv);



    // création de la my_map
    //my_map = CreateMap(monimage);
    //my_map.generateMap();

  

    //glutMainLoop();

    //return 1;
    return app.exec();
}

