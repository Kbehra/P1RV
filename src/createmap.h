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
    CreateMap(ImageJPEG uneimage, char* link_tex, int paspixel);
    void generateMap();                                 // génération de la my_map
    GLvoid afficher();                                  // afficher la my_map
    int  getPas();
    void changeScale(float newscale);
    void changePas(int newpas);
    float getScale();
    void exportToSTL(string link);
    bool getLoaderTex();

    void setLinkTexture(const char* link);

private:
	unsigned long x;
	unsigned long y;
	int id_display_list;
	ImageJPEG image;
    float scale;                                        // facteur de hauteur de la my_map
	int pas_pixel;                                      // permet de selectionner qu'une partie des pixels -- decimation
	vector<Vertex> vertex;                              // vertex affichés à l'écran

	ImageJPEG ma_texture;                               //  chargement de la texture
	bool loader_tex;
	GLuint texture_id;
	const char* link_texture;                                 // lien de la texture à charger
	void applyTexture();


};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_CREATEMAP_H
