//
// Created by eleve on 14/10/2019.
//

#include "createmap.h"
extern Camera cam;


CreateMap ::CreateMap(ImageJPEG uneimage) {
    x = uneimage.getX();
    y = uneimage.getY();
    image = uneimage;
    pas_pixel = 10;
    mode = 3;

    //TODO reflechir à une alternative

}
CreateMap :: CreateMap(){}

/*
 * Permet de créer la Map
 */
void CreateMap :: generateMap() {

    GLuint tex;

    //chargement de la texture
    ImageJPEG matexture;
//    bool loadertex = matexture.LoadJPEG("/home/alicia/Documents/Clion/Projets/P1RV_Heightmaps_BEHRA_MARAVAT_2010_2/examples/texture3.jpeg");

    glLoadIdentity();
    glRotatef(-cam.getAngleX(),1.0f,0.0f,0.0f);
    glRotatef(-cam.getAngleY(),0.0f,1.0f,0.0f);

    idDisplayList = glGenLists(1);

    glNewList(idDisplayList, GL_COMPILE);

    //glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_3D, tex);

    //on choisi notre couleur de la carte
    glColor3f(1.0f, 1.0f, 1.0f);

    switch (mode)
    {
        case 1:
            // TRIANGLE STRIPS SANS TEXTURE
            glBegin(GL_TRIANGLE_STRIP);
            glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
            for (int j = 0; j<x-pas_pixel; j+=pas_pixel){
                for (int i =0; i<y-pas_pixel; i+=pas_pixel){
                    Pixel p1 = image.getPixel(i, j);
                    Pixel p2 = image.getPixel(i+pas_pixel, j);
                    Pixel p3 = image.getPixel(i,j+ pas_pixel);
                    Pixel p4 = image.getPixel(i+ pas_pixel,j+ pas_pixel);

                    //glTexCoord2d(0,0);
                    //glTexCoord3f(0, (float)p1.getR()/255,0);
                    glVertex3f((float)p1.getPosx()/x,(float)p1.getR()/255, (float)p1.getPosy()/y);

                    //glTexCoord2d(1/matexture.getX(),0);
                    // glTexCoord3f((float) 1/matexture.getX(),(float)p2.getR()/255, 0);
                    glVertex3f((float)p2.getPosx()/x,(float)p2.getR()/255, (float)p2.getPosy()/y);

                    //glTexCoord2d(0.5/matexture.getX(),1/matexture.getY());
                    //glTexCoord3f((float)0.5/matexture.getX(),(float)p3.getR()/255, (float)1/matexture.getY());
                    glVertex3f((float)p3.getPosx()/x,(float)p3.getR()/255, (float)p3.getPosy()/y);

                    glVertex3f((float)p4.getPosx()/x,(float)p4.getR()/255, (float)p4.getPosy()/y);

                    // -- DEBUG
                    std::cout<<(float)p1.getPosx()/x<<" "<<(float)p1.getR()/255<<" "<< (float)p1.getPosy()/y <<std::endl;
                }
            }
            break;
        case 2:
            // TRIANGLE STRIPS AVEC TEXTURE
			glBegin(GL_TRIANGLES); 
			glFrontFace(GL_CW); 
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_BACK); 
			for (int i = 0; i < x - pas_pixel; i += pas_pixel) {
				for (int j = 0; j < y - pas_pixel; j += pas_pixel) {
					Pixel p1 = image.getPixel(i, j);
					Pixel p2 = image.getPixel(i + pas_pixel, j);
					Pixel p3 = image.getPixel(i, j + pas_pixel);
					Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

					//glTexCoord2d(0,0);
					//glTexCoord3f(0, (float)p1.getR()/255,0);
					glVertex3f((float)p1.getPosx(), (float)p1.getR() / 255, (float)p1.getPosy());

					//glTexCoord2d(1/matexture.getX(),0);
					// glTexCoord3f((float) 1/matexture.getX(),(float)p2.getR()/255, 0);
					glVertex3f((float)p2.getPosx(), (float)p2.getR() / 255, (float)p2.getPosy());

					//glTexCoord2d(0.5/matexture.getX(),1/matexture.getY());
					//glTexCoord3f((float)0.5/matexture.getX(),(float)p3.getR()/255, (float)1/matexture.getY());
					glVertex3f((float)p3.getPosx(), (float)p3.getR() / 255, (float)p3.getPosy());

					glVertex3f((float)p4.getPosx(), (float)p4.getR() / 255, (float)p4.getPosy());

					// -- DEBUG
					std::cout << (float)p1.getPosx() / x << " " << (float)p1.getR() / 255 << " " << (float)p1.getPosy() / y << std::endl;

				}
			}


            break;
        case 3:
            // QUADS SANS TEXTURE
            glBegin(GL_QUADS);
            //glFrontFace(GL_CW);
            for (int j = 0; j<x-pas_pixel; j+=pas_pixel){
                for (int i =0; i<y-pas_pixel; i+=pas_pixel) {
                    Pixel p1 = image.getPixel(i, j);
                    Pixel p2 = image.getPixel(i + pas_pixel, j);
                    Pixel p3 = image.getPixel(i, j + pas_pixel);
                    Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

                    glTexCoord2d(0, 0);

                    glVertex3f((float) p1.getPosx() / x, (float) p1.getR() / 255, (float) p1.getPosy() / y);

                    glTexCoord2d(0, 1);
                    glVertex3f((float) p2.getPosx() / x, (float) p2.getR() / 255, (float) p2.getPosy() / y);

                    glTexCoord2d(0, 1);

                    glVertex3f((float) p3.getPosx() / x, (float) p3.getR() / 255, (float) p3.getPosy() / y);

                    glTexCoord2d(1, 1);
                    glVertex3f((float) p4.getPosx() / x, (float) p4.getR() / 255, (float) p4.getPosy() / y);

                }
            }
            break;

        case 4:
            // QUADS AVEC TEXTURE
			
		


            break;
        default:
            break;



    }

    //info texture
//    glTexImage2D(GL_TEXTURE_3D, 0, GL_RGB, matexture.getX(), matexture.getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, matexture.getMatPixel());
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);




    glEnd();
    glEndList();
}
/*
 * Permet d'afficher
 */

GLvoid CreateMap :: afficher() {

    glCallList(idDisplayList);

}

int CreateMap :: getPas(){
    return pas_pixel;
}

void CreateMap :: setMode(int mode){
    this->mode=mode;
}
void CreateMap::changeMode() {
	if (mode > 4) { mode = 0; }
	else { mode++; }
	generateMap();
}
