//
// Created by kiki on 13/10/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_PIXEL_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_PIXEL_H
#include <iostream>

class Pixel{
public:
    Pixel();
    int getR() const;
    int getG() const;
    int getB() const;
    int getA() const;
    unsigned long getPosx() const;
    unsigned long getPosy() const;

    void setR(uint8_t red);
    void setG(uint8_t green);
    void setB(uint8_t blue);
    void setPosx(unsigned long x);
    void setPosy(unsigned long y);
    void printPixel();


protected:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
    unsigned long posx;
    unsigned long posy;
private:

//    uint8_t getR();
//    uint8_t getG();
//    uint8_t getB();
//    uint8_t getA();
//    void setR(uint8_t red);
//    void setG(uint8_t green);
//    void setB(uint8_t blue);
};



#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_PIXEL_H
