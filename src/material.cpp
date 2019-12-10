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

        case 1:
            {
                ambientR=0.0f;
                ambientG=0.0f;
                ambientB=0.0f;
                diffuseR=0.5f;
                diffuseG=0.0f;
                diffuseB=0.0f;
                specularR=0.7f;
                specularG=0.6f;
                specularB=0.6f;
                shininess=20.0f;
            }
            break;
        case 2:
            {
                ambientR=0.2473f;
                ambientG=0.1995f;
                ambientB=0.0745f;
                diffuseR=0.7516f;
                diffuseG=0.6065f;
                diffuseB=0.2265f;
                specularR=0.6282f;
                specularG=0.5558f;
                specularB=0.3661f;
                shininess=20.0f;
            }
            break;
        case 3:
            {
                ambientR=0.0f;
                ambientG=0.15f;
                ambientB=0.0f;
                diffuseR=0.4f;
                diffuseG=0.6f;
                diffuseB=0.4f;
                specularR=0.04f;
                specularG=0.5f;
                specularB=0.04f;
                shininess=0.70f;
            }
            break;
        case 4:
            {
                ambientR=0.135f;
                ambientG=0.2225f;
                ambientB=0.1575f;
                diffuseR=0.54f;
                diffuseG=0.89f;
                diffuseB=0.63f;
                specularR=0.3162f;
                specularG=0.3162f;
                specularB=0.3162f;
                shininess=0.1f;
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
