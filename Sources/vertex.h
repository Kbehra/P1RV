/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * Vertex.h
 */

#ifndef P1RV_VERTEX_H
#define P1RV_VERTEX_H


class Vertex {
private :
    float x;
    float y;
    float z;
public:
    Vertex();
    Vertex(float x1, float y1, float z1, float x2, float y2, float z2);
    Vertex computeCross(Vertex u, Vertex v);
    Vertex inverseVertex();

    float getX();
    float getY();
    float getZ();

};


#endif //P1RV_VERTEX_H
