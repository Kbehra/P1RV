/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * createmap.h
 */

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
#define GLEW_STATIC 1

#ifdef __linux__
#include <memory.h>
#elif _WIN32
#include <Windows.h>
#include<GL/wglext.h>
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include<GL/glext.h>
#include <fstream>

#include "loadjpeg.h"
#include "camera.h"
#include "vertex.h"


class CreateMap {
    public:

    CreateMap();
    CreateMap(ImageJPEG uneimage);
    void generateMap();                                 // génération de la map
    GLvoid afficher();                                  // afficher la map
    int  getPas();
    float scale;                                        // facteur de hauteur de la map
    void changeScale(float newscale);
    float getScale();
    void exportToSTL();

private:
	unsigned long x;
	unsigned long y;
	int id_display_list;
	ImageJPEG image;
	int pas_pixel;                                      // permet de selectionner qu'une partie des pixels -- decimation
	vector<Vertex> vertex;                              // vertex affichés à l'écran
	vector<Vertex> normals;                             // normales des vertex affichés à l'écran

	ImageJPEG ma_texture;                               //  chargement de la texture
	bool loader_tex;
	GLuint texture_id;
	void applyTexture();


};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
