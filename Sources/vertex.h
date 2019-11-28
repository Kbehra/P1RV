/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * vertex.h
 */

#ifndef P1RV_VERTEX_H
#define P1RV_VERTEX_H


class vertex {
private :
    float x;
    float y;
    float z;
public:
    vertex();
    vertex(float x, float y, float z);
    vertex computeCross(vertex u, vertex v);

    float getX();
    float getY();
    float getZ();

};


#endif //P1RV_VERTEX_H
