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


class CreateMap {
    public:
		unsigned long x;		// hauteur de l'image
		unsigned long y;		// largeur de l'image
		ImageJPEG image;
		int pas_pixel;		    // permet de selectionner qu'une partie des pixels -- decimation
		int idDisplayList;

		CreateMap();
		CreateMap(ImageJPEG uneimage);
    
		void generateMap();
		GLvoid afficher();
		int  getPas();

		int getIdDisplayList();
		void setMode(int mode);
		void changeMode();

protected:


private:
    int mode;                   // permet de selectionner le mode d'affichage




};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
