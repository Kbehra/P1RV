//
// Created by eleve on 14/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
#define GLEW_STATIC 1
#pragma once
#include <Windows.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include<GL/glext.h>
#include<GL/wglext.h>
#include "loadjpeg.h"
#include "camera.h"


class CreateMap {
    public:
    CreateMap(ImageJPEG uneimage);
    CreateMap();
   
	//void init(Shader* shadertest);
    void generateMap();
    GLvoid afficher();
    int  getPas();
    void setMode(int mode);


private:
	unsigned long x;
	unsigned long y;
	int idDisplayList;
	ImageJPEG image;
	int pas_pixel;              // permet de selectionner qu'une partie des pixels -- decimation
    int mode;                   // permet de selectionner le mode d'affichage

	int tailleVerticesBytes = 12 * sizeof(float);

	//chargement de la texture
	ImageJPEG matexture;
	bool loadertex; 

};

GLvoid createTexture(ImageJPEG tex);

#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
