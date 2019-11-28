/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * createmap.cpp
 */

#include "createmap.h"
#include "vertex.h"

extern Camera cam;
extern GLbyte* texData;
extern char* LINK_TEX;


CreateMap ::CreateMap(ImageJPEG uneimage)
{
    x = uneimage.getX();                // dimension de l'image
    y = uneimage.getY();

    image = uneimage;
    pas_pixel = 5;

    scale = 1 ;                         // default scale

	loadertex= matexture.LoadTexture(LINK_TEX, true);
	if (loadertex)
	{
		textureID =0;
		std::cout << "texture chargee" << std::endl;
		applyTexture();
	}
	else { std::cout << "Impossible de charger une texture"<< std::endl;}

	idDisplayList = glGenLists(1); 
	glNewList(idDisplayList, GL_COMPILE);
	
}
CreateMap :: CreateMap(){ }

/*
 * Permet de créer la Map
 */
void CreateMap :: generateMap()
{
    // QUADS AVEC TEXTURE
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    glDrawBuffer(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glFrontFace(GL_CW);

    for (int j = 0; j < x - pas_pixel; j += pas_pixel)
    {
        for (int i = 0; i < y - pas_pixel; i += pas_pixel)

        {
            Pixel p1 = image.getPixel(i, j);
            Pixel p2 = image.getPixel(i + pas_pixel, j);
            Pixel p3 = image.getPixel(i, j + pas_pixel);
            Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

            std::cout << scale << std::endl;        //debug
            vertex v1 = vertex((float)p1.getPosx() / x, (float)p1.getR() / (255*scale), (float)p1.getPosy() / y);
            vertex v2 = vertex((float)p2.getPosx() / x, (float)p2.getR() / (255*scale), (float)p2.getPosy() / y);
            vertex v3 = vertex((float)p4.getPosx() / x, (float)p4.getR() / (255*scale), (float)p4.getPosy() / y);
            vertex v4 = vertex((float)p3.getPosx() / x, (float)p3.getR() / (255*scale), (float)p3.getPosy() / y);

            vertex normal;

            normal.computeCross(v1,v2);
            glNormal3f(normal.getX(), normal.getY(), normal.getZ());
            glTexCoord2f(0.0, 0.0);
            glVertex3f(v1.getX(), v1.getY(), v1.getZ());


            normal.computeCross(v2,v3);
            glNormal3f(normal.getX(), normal.getY(), normal.getZ());
            glTexCoord2f(0.0, 1.0);
            glVertex3f(v2.getX(), v2.getY(), v2.getZ());

            normal.computeCross(v3,v4);
            glNormal3f(normal.getX(), normal.getY(), normal.getZ());
            glTexCoord2f(1.0, 1.0);
            glVertex3f(v3.getX(), v3.getY(), v3.getZ());


            normal.computeCross(v4,v1);
            glNormal3f(normal.getX(), normal.getY(), normal.getZ());
            glTexCoord2f(1.0, 0.0);
            glVertex3f(v4.getX(), v4.getY(), v4.getZ());

        }
    }

    glEnd();
	glEndList();
}
void CreateMap ::applyTexture()
{
	glGenTextures(1, &textureID);

	//Vérouillage
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, matexture.getType(), matexture.getX(), matexture.getY(), 0, matexture.getType(), GL_UNSIGNED_BYTE, texData );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	// Correction de la perspective
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Déverrouillage
	//glBindTexture(GL_TEXTURE_2D, textureID);

}



/*
 * Permet d'afficher
 */

GLvoid CreateMap :: afficher()
{
    glCallList(idDisplayList);
}

int CreateMap :: getPas()
{
    return pas_pixel;
}

void CreateMap ::changeScale(float newscale) {
    scale = newscale ;
}
float CreateMap :: getScale(){
    return scale;
}

