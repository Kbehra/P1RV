//
// Created by eleve on 14/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H

#pragma once
#include <Windows.h>
#include "loadjpeg.h"
#include "GL/gl.h"
#include "camera.h"
#include "shader.h"

class CreateMap {
    public:
    CreateMap(ImageJPEG uneimage);
    CreateMap();
   
	//void init(Shader* shadertest);
    void generateMap();
    GLvoid afficher();
    int  getPas();
    void setMode(int mode);


protected:


private:
	unsigned long x;
	unsigned long y;
	int idDisplayList;
	ImageJPEG image;
	int pas_pixel;              // permet de selectionner qu'une partie des pixels -- decimation
    int mode;                   // permet de selectionner le mode d'affichage

	/*unsigned int vaoID[1]; // Our Vertex Array Object
	unsigned int vboID[1]; // Our Vertex Buffer Object*/

	//taille du tableau de sommets = 3 vertices * 3 coord * nb triangles
	// nb triangles = x*y*2/pas_pixel*pas_pixel
	int tailleVerticesBytes = ((3 * x * y * 4) / (pas_pixel * pas_pixel)) * sizeof(float);

	/*GLfloat* projectionMatrix; // Store the projection matrix
	GLfloat* viewMatrix; // Store the view matrix
	GLfloat* modelMatrix; // Store the model matrix*/
};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
