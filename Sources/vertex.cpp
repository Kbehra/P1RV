/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * vertex.cpp
 */

#include "vertex.h"


vertex ::vertex() {}

vertex ::vertex(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

vertex vertex:: computeCross(vertex u, vertex v)
{
    vertex w;
    w.x = u.y*v.z - u.z*v.y ;
    w.y = u.z*v.x - u.x*v.z ;
    w.z = u.x*v.y - u.y*v.x ;
    return w;

}

float vertex ::getX() {
    return x;
}
float vertex ::getY() {
    return y;
}
float vertex ::getZ() {
    return z;
}


