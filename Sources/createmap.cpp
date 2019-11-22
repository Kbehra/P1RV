//
// Created by eleve on 14/10/2019.
//

#include "createmap.h"
extern Camera cam;

char* LINK_TEX = _strdup("C:/dev/P1RV_1611/P1RV_1611/examples/texture1.jpeg");

CreateMap ::CreateMap(ImageJPEG uneimage) {
    x = uneimage.getX();
    y = uneimage.getY();
    image = uneimage;
	idDisplayList = 0;
    pas_pixel = 10;
    mode = 6;						// permet de sélectionner le mode d'affichage
    //TODO reflechir à une alternative

}
CreateMap :: CreateMap(){ }

/*
 * Permet de créer la Map
 */
void CreateMap :: generateMap() {

	GLuint tex;
	int tailleVerticesBytes = 12 * sizeof(float);

	//chargement de la texture
	ImageJPEG matexture;
	bool loadertex = matexture.LoadJPEG(LINK_TEX);

	glLoadIdentity();
	glRotatef(-cam.getAngleX(), 1.0f, 0.0f, 0.0f);
	glRotatef(-cam.getAngleY(), 0.0f, 1.0f, 0.0f);

	//Génération de l'ID
	glGenTextures(1, &tex);

	//Verrouillage
	glBindTexture(GL_TEXTURE_2D, tex);

	//Copie des pixels
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, matexture.getX(), matexture.getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, matexture.getMatPixel());
	
	//Application de filtres
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Déverrouillage
	glBindTexture(GL_TEXTURE_2D, 0);

	//on choisi notre couleur de la carte
	glColor3f(1.0f, 1.0f, 1.0f);

    switch (mode)
    {
        case 1:
            // TRIANGLE STRIPS SANS TEXTURE
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j<x-pas_pixel; j+=pas_pixel){
                for (int i =0; i<y-pas_pixel; i+=pas_pixel){
                    Pixel p1 = image.getPixel(i, j);
                    Pixel p2 = image.getPixel(i+pas_pixel, j);
                    Pixel p3 = image.getPixel(i,j+ pas_pixel);
                    Pixel p4 = image.getPixel(i+ pas_pixel,j+ pas_pixel);

                    glVertex3f((float)p1.getPosx()/x,(float)p1.getR()/255, (float)p1.getPosy()/y);

                    glVertex3f((float)p2.getPosx()/x,(float)p2.getR()/255, (float)p2.getPosy()/y);

                    glVertex3f((float)p3.getPosx()/x,(float)p3.getR()/255, (float)p3.getPosy()/y);

                    glVertex3f((float)p4.getPosx()/x,(float)p4.getR()/255, (float)p4.getPosy()/y);

                    // -- DEBUG
                    std::cout<<(float)p1.getPosx()/x<<" "<<(float)p1.getR()/255<<" "<< (float)p1.getPosy()/y <<std::endl;
                }
            }
            break;
        case 2:
			// TRIANGLE STRIPS AVEC TEXTURE
			glBegin(GL_TRIANGLE_STRIP);
			glFrontFace(GL_CW);
			for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
				for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
					Pixel p1 = image.getPixel(i, j);
					Pixel p2 = image.getPixel(i + pas_pixel, j);
					Pixel p3 = image.getPixel(i, j + pas_pixel);
					Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

					glTexCoord2d(0, 0);
					//glTexCoord3f(0, (float)p1.getR()/255,0);
					glVertex3f((float)p1.getPosx() / x, (float)p1.getR() / 255, (float)p1.getPosy() / y);

					glTexCoord2d(p2.getPosx() / x, 0);
					//glTexCoord2d(1/matexture.getX(),0);
					// glTexCoord3f((float) 1/matexture.getX(),(float)p2.getR()/255, 0);
					glVertex3f((float)p2.getPosx() / x, (float)p2.getR() / 255, (float)p2.getPosy() / y);

					glTexCoord2d(0.5 * p3.getPosx() / x, p3.getPosy() / y);
					//glTexCoord2d(0.5/matexture.getX(),1/matexture.getY());
					//glTexCoord3f((float)0.5/matexture.getX(),(float)p3.getR()/255, (float)1/matexture.getY());
					glVertex3f((float)p3.getPosx() / x, (float)p3.getR() / 255, (float)p3.getPosy() / y);

					glVertex3f((float)p4.getPosx() / x, (float)p4.getR() / 255, (float)p4.getPosy() / y);

					// -- DEBUG
					std::cout << (float)p1.getPosx() / x << " " << (float)p1.getR() / 255 << " " << (float)p1.getPosy() / y << std::endl;
				}
			}
            break;
        case 3:
            // QUADS SANS TEXTURE
            glBegin(GL_QUADS);
            for (int j = 0; j<x-pas_pixel; j+=pas_pixel){
                for (int i =0; i<y-pas_pixel; i+=pas_pixel) {
                    Pixel p1 = image.getPixel(i, j);
                    Pixel p2 = image.getPixel(i + pas_pixel, j);
                    Pixel p3 = image.getPixel(i, j + pas_pixel);
                    Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

                    glVertex3f((float) p1.getPosx() / x, (float) p1.getR() / 255, (float) p1.getPosy() / y);

                    glVertex3f((float) p2.getPosx() / x, (float) p2.getR() / 255, (float) p2.getPosy() / y);

                    glVertex3f((float) p3.getPosx() / x, (float) p3.getR() / 255, (float) p3.getPosy() / y);

                    glVertex3f((float) p4.getPosx() / x, (float) p4.getR() / 255, (float) p4.getPosy() / y);
                }
            }
            break;
        case 4:
            // QUADS AVEC TEXTURE
			glBegin(GL_QUADS);
			glFrontFace(GL_CW);
			for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
				for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
					Pixel p1 = image.getPixel(i, j);
					Pixel p2 = image.getPixel(i + pas_pixel, j);
					Pixel p3 = image.getPixel(i, j + pas_pixel);
					Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

					glTexCoord2d(0, 0);
					glVertex3f((float)p1.getPosx() / x, (float)p1.getR() / 255, (float)p1.getPosy() / y);

					glTexCoord2d(0, 1);
					glVertex3f((float)p2.getPosx() / x, (float)p2.getR() / 255, (float)p2.getPosy() / y);

					glTexCoord2d(0, 1);
					glVertex3f((float)p4.getPosx() / x, (float)p4.getR() / 255, (float)p4.getPosy() / y);

					glTexCoord2d(1, 1);
					glVertex3f((float)p3.getPosx() / x, (float)p3.getR() / 255, (float)p3.getPosy() / y);

				}
			}
            break;
		case 5:
			//SHADER AVEC TRIANGLES
			/*glFrontFace(GL_CW);
			//taille du tableau de sommets = 3 vertices * 3 coord * nb triangles
			// nb triangles = x*y*2/pas_pixel*pas_pixel
			int tailleVerticesBytes = ((3 * 3 * x * y * 2 )/ (pas_pixel * pas_pixel) )* sizeof(float);
			
			float* vertices = new float[tailleVerticesBytes];

			int k = 0;

			for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
				for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
					Pixel p1 = image.getPixel(i, j);
					Pixel p2 = image.getPixel(i + pas_pixel, j);
					Pixel p3 = image.getPixel(i, j + pas_pixel);
					Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

					// Coin en bas à gauche
					vertices[k] = (float)p1.getPosx() / x; 
					vertices[k+1] = (float)p1.getR() / 255;
					vertices[k+2] = (float)p1.getPosy() / y;

					// Coin en haut à gauche
					vertices[k+3] = (float)p3.getPosx() / x;
					vertices[k+4] = (float)p3.getR() / 255;
					vertices[k+5] = (float)p3.getPosy() / y;
					
					// Coin en haut à droite
					vertices[k+6] = (float)p4.getPosx() / x;
					vertices[k+7] = (float)p4.getR() / 255;
					vertices[k+8] = (float)p4.getPosy() / y;

					// Coin en bas à droite
					vertices[k+9] = (float)p2.getPosx() / x;
					vertices[k+10] = (float)p2.getR() / 255;
					vertices[k+11] = (float)p2.getPosy() / y;
					
					// Coin en bas à gauche
					vertices[k+12] = (float)p1.getPosx() / x;
					vertices[k+13] = (float)p1.getR() / 255;
					vertices[k+14] = (float)p1.getPosy() / y;;
					
					// Coin en haut à droite
					vertices[k+15] = (float)p4.getPosx() / x;
					vertices[k+16] = (float)p4.getR() / 255;
					vertices[k+17] = (float)p4.getPosy() / y;

					//il faut 3 sommet de 3 coord par triangles et 2 triangles pour 1 carré de pas_pixel de côté
					k+= 18; //3*3*2=18

				}
			} */
			break;
		case 6:
		{
			//SHADER AVEC TRIANGLE_STRIP
			float* vertices = new float[tailleVerticesBytes];

			int k = 0;

			for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
				for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
					Pixel p1 = image.getPixel(i, j);
					Pixel p2 = image.getPixel(i + pas_pixel, j);
					Pixel p3 = image.getPixel(i, j + pas_pixel);
					Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

					// Coin en bas à gauche
					vertices[k] = (float)p1.getPosx() / x;
					vertices[k + 1] = (float)p1.getR() / 255;
					vertices[k + 2] = (float)p1.getPosy() / y;

					// Coin en bas à droite
					vertices[k + 3] = (float)p2.getPosx() / x;
					vertices[k + 4] = (float)p2.getR() / 255;
					vertices[k + 5] = (float)p2.getPosy() / y;

					// Coin en haut à gauche
					vertices[k + 6] = (float)p3.getPosx() / x;
					vertices[k + 7] = (float)p3.getR() / 255;
					vertices[k + 8] = (float)p3.getPosy() / y;

					// Coin en haut à droite
					vertices[k + 9] = (float)p4.getPosx() / x;
					vertices[k + 10] = (float)p4.getR() / 255;
					vertices[k + 11] = (float)p4.getPosy() / y;

					//il faut 4 sommet de 3 coord pour 1 carré de pas_pixel de côté
					k += 12; //3*4=12

				}
			}

			/* ***** Gestion du VBO ***** */

			//GLuint vbo;

			//// Génération du VBO
			//glGenBuffers(1, &vbo);

			//// Verrouillage
			//glBindBuffer(GL_ARRAY_BUFFER, vbo);

			//// Remplissage
			//glBufferData(GL_ARRAY_BUFFER, tailleVerticesBytes, 0, GL_STATIC_DRAW);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVerticesBytes, vertices);

			//// Déverrouillage du VBO
			//glBindBuffer(GL_ARRAY_BUFFER, 0);

			///* ***** Gestion du VAO ***** */
			//GLuint vao;
			//glGenVertexArrays(1, &vao);

			//// Verrouillage du VAO
			//glBindVertexArray(vao);

			//// Verrouillage du VBO
			//glBindBuffer(GL_ARRAY_BUFFER, vbo);

			//// Vertex Attrib 0 (Vertices)
			////glVertexAttribPointer(0, tailleVerticesBytes, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			//glEnableVertexAttribArray(0);

			//// Déverrouillage du VBO
			//glBindBuffer(GL_ARRAY_BUFFER, 0);

			//// Déverrouillage du VAO
			//glBindVertexArray(0);

		}
			break;
        default:

            break;
    }
    glEnd();
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

/*void CreateMap::init(Shader* shadertest) {
	
	shadertest->bind(); // Bind our shader

	int projectionMatrixLocation = glGetUniformLocation(shadertest->getProgramID(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shadertest->getProgramID(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shadertest->getProgramID(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
	
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object

	glDrawArrays(GL_TRIANGLE_STRIP, 0, tailleVerticesBytes); // Draw our square

	glBindVertexArray(0); // Unbind our Vertex Array Object

	shadertest->unbind(); // Unbind our shader
}*/
