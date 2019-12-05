//
// Created by kiki on 01/11/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_MATERIAL_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_MATERIAL_H

#ifdef __linux__
#elif _WIN32
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#endif
#include <GL/freeglut.h>

class Material {

public:
    Material(int choice);
};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_MATERIAL_H
