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
#include "src/mymainwindow.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MyMainWindow fenetre;

    fenetre.show();

    return app.exec();
}

