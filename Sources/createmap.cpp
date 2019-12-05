/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * createmap.cpp
 */

#include "createmap.h"
#include "vertex.h"

extern Camera cam;
extern char* LINK_TEX;

CreateMap :: CreateMap(){ }

CreateMap ::CreateMap(ImageJPEG uneimage)
{
    x = uneimage.getX();                                          // dimension de l'image
    y = uneimage.getY();
    image = uneimage;                                             // image originale
    pas_pixel = 5;                                                //

    scale = 5 ;                                                   // default scale
	loader_tex= ma_texture.loadTexture(LINK_TEX, true);     // texture de la my_map
	if (loader_tex)
	{
        texture_id = 0;
		std::cout << "texture chargee" << std::endl;
		applyTexture();
	}
	else { std::cout << "Impossible de charger une texture"<< std::endl;}

    id_display_list = glGenLists(1);
	glNewList(id_display_list, GL_COMPILE);
	
}


/*
 * Permet de créer la Map
 */
void CreateMap :: generateMap()
{
    // QUADS AVEC TEXTURE
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    std::cout << "x = "<<x<<" y =" <<y<<std::endl;          // -- debug
    if ((x > 0) && (y>0)) {
        id_display_list = glGenLists(1);
        glNewList(id_display_list, GL_COMPILE);

        glBegin(GL_QUADS);

        for (int j = 0; j < x - pas_pixel; j += pas_pixel) {
            for (int i = 0; i < y - pas_pixel; i += pas_pixel) {
                Pixel p1 = image.getPixel(i, j);
                Pixel p2 = image.getPixel(i + pas_pixel, j);
                Pixel p3 = image.getPixel(i, j + pas_pixel);
                Pixel p4 = image.getPixel(i + pas_pixel, j + pas_pixel);

                //std::cout << scale << std::endl;        //debug

                Vertex v1 = Vertex((float) p1.getPosx() / x, (float) p1.getR() / (255 * scale),
                                   (float) p1.getPosy() / y);
                Vertex v2 = Vertex((float) p2.getPosx() / x, (float) p2.getR() / (255 * scale),
                                   (float) p2.getPosy() / y);
                Vertex v3 = Vertex((float) p3.getPosx() / x, (float) p3.getR() / (255 * scale),
                                   (float) p3.getPosy() / y);
                Vertex v4 = Vertex((float) p4.getPosx() / x, (float) p4.getR() / (255 * scale),
                                   (float) p4.getPosy() / y);

                Vertex normal;

                normal.computeCross(v2 - v1, v3 - v1);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glTexCoord2f(0.0, 0.0);
                glVertex3f(v1.getX(), v1.getY(), v1.getZ());


                normal.computeCross(v4 - v2, v1 - v2);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glTexCoord2f(0.0, 1.0);
                glVertex3f(v2.getX(), v2.getY(), v2.getZ());

                normal.computeCross(v3 - v4, v2 - v4);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glTexCoord2f(1.0, 1.0);
                glVertex3f(v4.getX(), v4.getY(), v4.getZ());


                normal.computeCross(v1 - v3, v4 - v3);
                glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                glTexCoord2f(1.0, 0.0);
                glVertex3f(v3.getX(), v3.getY(), v3.getZ());

                // enregistrement des résultats (pour export)
                vertex.push_back(v1);
                vertex.push_back(v2);
                vertex.push_back(v3);
                vertex.push_back(v4);
            }
        }
        glEndList();
        glEnd();
    }

}

void CreateMap ::applyTexture()
{
	glGenTextures(1, &texture_id);

	//Vérouillage
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, ma_texture.getType(), ma_texture.getX(), ma_texture.getY(), 0, ma_texture.getType(), GL_UNSIGNED_BYTE, ma_texture.getData() );

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
	//glBindTexture(GL_TEXTURE_2D, texture_id);

}



/*
 * Permet d'afficher
 */

GLvoid CreateMap :: afficher()
{
    glCallList(id_display_list);
}

int CreateMap :: getPas()
{
    return pas_pixel;
}

void CreateMap ::changeScale(float newscale) {
    scale = newscale ;
    // il faut reinit le vecteur de vertex
    vertex.clear();
}
float CreateMap :: getScale(){
    return scale;
}

/*
 * Permet de sauvegarder le contexte OpenGL en STL
 */

void CreateMap::exportToSTL(string link)
{
    // Mots clés format STL
    string facetnormal = "facet normal";
    string outerloop = "outer loop";
    string namevertex = "vertex";
    string endloop = "endloop";
    string endfacet = "endfacet";
    string endsolid = "ensolid name";

    ofstream file(link+".stl");
    if (file)
    {
        file << "solid name" << std::endl;
        for (int i=0; i<vertex.size()-4; i+=4)
        {
            Vertex A = vertex.at(i);
            Vertex B = vertex.at(i+1);
            Vertex C = vertex.at(i+2);
            Vertex D = vertex.at(i+3);

            // calcul de la normal du 1er triangle
            Vertex normal1;
            normal1 = normal1.computeCross(B-A,C-A);
            //
            file << facetnormal << " "<<normal1.getX()<<" "<<normal1.getY()<<" "<<normal1.getZ()<< std::endl;
            file << "    " << outerloop << std::endl;
            file << "        " << namevertex<< " " << A.getX() << " " << A.getY() << " " << A.getZ() << std::endl;       // A
            file << "        " << namevertex<< " " << C.getX() << " " << C.getY() << " " << C.getZ() << std::endl;       // C
            file << "        " << namevertex<< " " << D.getX() << " " << D.getY() << " " << D.getZ() << std::endl;       // D
            file << "    " << endloop << std::endl;
            file << endfacet << std::endl;

            // calcul de la normal du 2nd triangle
            Vertex normal2;
            normal2 = normal2.computeCross(D-A, C-B);
            file << facetnormal << " "<<normal2.getX()<<" "<<normal2.getY()<<" "<<normal2.getZ()<< std::endl;
            file << "    " << outerloop << std::endl;
            file << "        " << namevertex<< " " << A.getX() << " " << A.getY() << " " << A.getZ() << std::endl;       // A
            file << "        " << namevertex<< " " << B.getX() << " " << B.getY() << " " << B.getZ() << std::endl;       // B
            file << "        " << namevertex<< " " << D.getX() << " " << D.getY() << " " << D.getZ() << std::endl;       // D
            file << "    " << endloop << std::endl;
            file << endfacet << std::endl;
        }
        file << endsolid << std::endl;
    }
    else
        {
        std::cout << "Impossible d'ouvrir le fichier :"<<link+".stl" <<std::endl;
        }

}
