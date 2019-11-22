//
// Created by kiki on 31/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CALLBACK_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CALLBACK_H

#pragma once
#include <Windows.h>

#include "createmap.h"
#include "display.h"
#include "camera.h"


void KeyBoard(unsigned char c, int x, int y);

void souris(int bouton, int etat, int x, int y);

void deplacementSouris(int x, int y);

GLvoid rezise(int w, int h);

GLvoid affichage();




#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CALLBACK_H
