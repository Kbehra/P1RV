/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * Material.cpp
 *
 */

#include "material.h"

Material ::Material(int choice)
{
    GLfloat ambientR;
    GLfloat ambientG;
    GLfloat ambientB;
    GLfloat diffuseR;
    GLfloat diffuseG;
    GLfloat diffuseB;
    GLfloat specularR;
    GLfloat specularG;
    GLfloat specularB;
    GLfloat shininess;
    switch (choice)
    {
        case 0:
            {
            ambientR = 0.0f;
            ambientG = 0.5f;
            ambientB = 1.0f;
            diffuseR = 0.0f;
            diffuseG = 0.5f;
            diffuseB = 1.0f;
            specularR = 1.0f;
            specularG = 1.0f;
            specularB = 1.0f;
            shininess = 1.0f;
            }
            break;

        case 1:
            {
            ambientR=0.0f;
            ambientG=0.5f;
            ambientB=1.0f;
            diffuseR=0.0f;
            diffuseG=0.5f;
            diffuseB=1.0f;
            specularR=1.0f;
            specularG=1.0f;
            specularB=1.0f;
            shininess=50.0f;
            }
            break;
        case 2:
            {
            ambientR=1.0f;
            ambientG=0.0f;
            ambientB=0.0f;
            diffuseR=1.0f;
            diffuseG=0.0f;
            diffuseB=0.0f;
            specularR=0.0f;
            specularG=0.0f;
            specularB=0.0f;
            shininess=1.0f;
            }
            break;
        case 3:
            {
            ambientR=1.0f;
            ambientG=1.0f;
            ambientB=0.0f;
            diffuseR=1.0f;
            diffuseG=0.0f;
            diffuseB=0.0f;
            specularR=1.0f;
            specularG=0.0f;
            specularB=1.0f;
            shininess=100.0f;
            }
            break;
        case 4:
            {
            ambientR=1.0f;
            ambientG=0.5f;
            ambientB=0.25f;
            diffuseR=1.0f;
            diffuseG=0.5f;
            diffuseB=1.0f;
            specularR=1.0f;
            specularG=1.0f;
            specularB=1.0f;
            shininess=120.0f;
            }
            break;
        default:
            break;
    }
    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}
