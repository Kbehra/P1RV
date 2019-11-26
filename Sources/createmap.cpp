//
// Created by eleve on 14/10/2019.
//

#include "createmap.h"
extern Camera cam;
extern GLbyte* texData;

char* LINK_TEX = strdup("../examples/texture1.jpeg");

CreateMap ::CreateMap(ImageJPEG uneimage)
{
    x = uneimage.getX();
    y = uneimage.getY();
    image = uneimage;
	idDisplayList = 0;
    pas_pixel = 10;
    mode = 1;								// permet de sélectionner le mode d'affichage
    //TODO reflechir à une alternative

	loadertex= matexture.LoadJPEG(LINK_TEX);
	if (loadertex) {
		textureID =0;
		std::cout << "texture chargee" << std::endl;
		applyTexture();
	}
	//createTexture(matexture);

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

    for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
        for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
            Pixel p1 = image.getPixel(i, j);
            Pixel p2 = image.getPixel(i + pas_pixel, j);
            Pixel p3 = image.getPixel(i, j + pas_pixel);
            Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

            glTexCoord2f(0.0, 0.0);
            glVertex3f((float)p1.getPosx() / x, (float)p1.getR() / 255, (float)p1.getPosy() / y);

            glTexCoord2f(0.0, 1.0);
            glVertex3f((float)p2.getPosx() / x, (float)p2.getR() / 255, (float)p2.getPosy() / y);

            glTexCoord2f(1.0, 1.0);
            glVertex3f((float)p4.getPosx() / x, (float)p4.getR() / 255, (float)p4.getPosy() / y);

            glTexCoord2f(1.0, 0.0);
            glVertex3f((float)p3.getPosx() / x, (float)p3.getR() / 255, (float)p3.getPosy() / y);


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

	std::cout <<matexture.getX()<< " " <<matexture.getY()<< " " << matexture.getType() << std::endl;

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

void CreateMap :: setMode(int mode)
{
    this->mode=mode;
}

GLvoid createTexture(ImageJPEG tex)
{

}
