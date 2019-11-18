//
// Created by kiki on 31/10/2019.
//

#include "callback.h"

extern CreateMap map;
extern Display goDisplay;
extern Camera cam;

void KeyBoard(unsigned char c, int x, int y){
    goDisplay.clavier(c, x, y);
}

void souris(int bouton, int etat, int x, int y){
    cam.mouseState(bouton, etat, x, y);
}

void deplacementSouris(int x, int y){
    cam.mouseMove(x, y);
}
