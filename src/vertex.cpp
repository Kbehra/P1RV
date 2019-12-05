/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * Vertex.cpp
 */

#include "vertex.h"


Vertex ::Vertex() {}

Vertex ::Vertex(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
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

float Vertex ::getX() const
{
    return x;
}

float Vertex ::getY() const
{
    return y;
}

float Vertex ::getZ() const
{
    return z;
}

Vertex operator+(const Vertex & u, const Vertex & v)
{
    return Vertex(u.getX()+v.getX(),u.getY()+v.getY(),u.getZ()+v.getZ());

}

Vertex operator-(const Vertex & u, const Vertex & v)
{
    return Vertex(u.getX()-v.getX(),u.getY()-v.getY(),u.getZ()-v.getZ());

}

