//
// Created by KIlian on 12/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H

#define _CRT_SECURE_NO_WARNINGS
#define GL_GLEXT_PROTOTYPES
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
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
    GLbyte* texData;                // the data of the image
    GLuint ID;                      // the id OpenGl gives it
    unsigned long size;             // length of the file
    GLuint type;
    int channels;                   // the channels of the image 3 = RGA 4 = RGBA
    vector<vector<Pixel>> Pixels;     //matrice de pixels


public:
    ImageJPEG();
    unsigned long getX() const;
    unsigned long getY() const;
    GLbyte* getData() const;
    bool LoadJPEG(char* FileName, bool Fast = true);    //chargement de l'image
    Pixel getPixel(int x, int y) const;                 //acceder a un pixel
    vector<vector<Pixel>>* getMatPixel();               //pointeur sur la matrice de pixels
    int seekMax() const;                                //permet de chercher le niveau max
    int seekMin() const;                                //permet de chercher le niveau min


};







#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_LOADJPEG_H
