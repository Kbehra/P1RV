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
    Vertex(float x, float y, float z);
    Vertex computeCross(Vertex u, Vertex v);

    float getX();
    float getY();
    float getZ();

};


#endif //P1RV_VERTEX_H
