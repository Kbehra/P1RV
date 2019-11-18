//
// Created by kiki on 13/10/2019.
//

#include "pixel.h"
#include <iostream>
Pixel :: Pixel(){

}
int Pixel :: getR() const{
    return this->R;
}
int Pixel :: getG() const{
    return this->G;
}
int Pixel :: getB() const{
    return this->B;
}
int  Pixel :: getA() const{
    return A;
}
void Pixel :: setR(uint8_t red){
    R = red;
}
void Pixel :: setG(uint8_t green){
    G = green;
}
void Pixel :: setB(uint8_t blue ){
    B = blue;
}
void Pixel :: setPosx(unsigned long x ){
    posx = x;
}
void Pixel :: setPosy(unsigned long y ){
    posy = y;
}
unsigned long Pixel ::getPosx() const {
    return posx;
}
unsigned long Pixel ::getPosy() const {
    return posy;
}
void Pixel ::printPixel() {
    std::cout <<"x = "<< getPosx() <<" y =" << getPosy()<< " ; R = "<< getR()<< ", G = "<< getG() <<" , B = "<<getB()<<std::endl;
}
