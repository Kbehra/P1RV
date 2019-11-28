/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * loadjpeg.h
 */

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H

#ifdef __linux__

#elif _WIN32
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#define _CRT_SECURE_NO_WARNINGS
#define GL_GLEXT_PROTOTYPES
#endif
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "pixel.h"

using namespace std;

class ImageJPEG {

protected:
    unsigned long x;
    unsigned long y;
    unsigned short int bpp;         // bits per pixels   unsigned short int

    GLuint id;                      // the id OpenGl gives it
    unsigned long size;             // length of the file
    GLuint type;
    int channels;                   // the channels of the image 3 = RGA 4 = RGBA
    vector<vector<Pixel>> pixels;     //matrice de pixels
    GLbyte* texData;                //donnees de textures

public:
    ImageJPEG();
    unsigned long getX() const;
    unsigned long getY() const;
    GLbyte* getData() const;
	GLuint getID() const;
	GLuint* getPtrID();
	GLuint getType() const;
    bool loadJPEG(char* FileName, bool Fast = true);    //chargement de l'image
    bool loadTexture(char * FileName, bool Fast);
    Pixel getPixel(int x, int y) const;                 //acceder a un pixel
    vector<vector<Pixel>>* getMatPixel();               //pointeur sur la matrice de pixels
    int seekMax() const;                                //permet de chercher le niveau max
    int seekMin() const;                                //permet de chercher le niveau min

};

#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H
