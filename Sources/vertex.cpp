/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * Vertex.cpp
 */

#include "vertex.h"


Vertex ::Vertex() {}

Vertex ::Vertex(float x1, float y1, float z1, float x2, float y2, float z2)
{
    this->x=x2-x1;
    this->y=y2-y1;
    this->z=z2-z1;
}

Vertex Vertex:: computeCross(Vertex u, Vertex v)
{
    Vertex w;
    w.x = u.y*v.z - u.z*v.y ;
    w.y = u.z*v.x - u.x*v.z ;
    w.z = u.x*v.y - u.y*v.x ;
    return w;

}

Vertex Vertex:: inverseVertex()
{
    Vertex w;
    w.x = -x;
    w.y = -y ;
    w.z = -z;
    return w;

}

float Vertex ::getX() {
    return x;
}
float Vertex ::getY() {
    return y;
}
float Vertex ::getZ() {
    return z;
}


