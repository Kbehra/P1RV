/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * loadjpeg.cpp
 */
#define _CRT_SECURE_NO_WARNINGS
#define GL_GLEXT_PROTOTYPES

#include "loadjpeg.h"
#include "jpeglib.h"
#include "jerror.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

ImageJPEG :: ImageJPEG (){}


bool ImageJPEG :: loadJPEG(char* FileName, bool Fast)
{
    FILE* file = fopen(FileName, "rb");         //open the file
    struct jpeg_decompress_struct info;                //the jpeg decompress info
    struct jpeg_error_mgr err;                         //the error handler

    info.err = jpeg_std_error(&err);                    //tell the jpeg decompression handler to send the errors to err
    jpeg_create_decompress(&info);                //sets info to all the default stuff

    //if the jpeg file didnt load exit
    if(!file)
    {
        fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
        return false;
    }

    jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

    jpeg_read_header(&info, TRUE);   //tell it to start reading it

    //if it wants to be read fast or not
    if(Fast)
    {
        info.do_fancy_upsampling = FALSE;
    }

    jpeg_start_decompress(&info);    //decompress the file

    //set the x and y
    x = info.output_width;
    y = info.output_height;
    channels = info.num_components;


    //TODO : ajouter un algo pour détecter si on rentre une image en niveau de gris en entrée i.e. R=G=B dans cette
    // configuration on peut imaginer de garder qu'une composante pour décharger un peu la RAM.

    type = GL_RGB;

    if(channels == 4)
    {
        type = GL_RGBA;
    }

    bpp = channels * 8;

    size = x * y * 3;

    //read turn the uncompressed data into something ogl can read
    texData = new GLbyte[size];      //setup data for the data its going to be handling

    GLbyte* p1 = texData;
    GLbyte** p2 = &p1;
    int numlines = 0;
    id = 0;

    JSAMPARRAY buffer;
    buffer = (*info.mem->alloc_sarray)((j_common_ptr)&info, JPOOL_IMAGE, info.output_width*info.output_components,1);

    while(info.output_scanline < info.output_height)
    {
        (void) jpeg_read_scanlines(&info, buffer, 1);
        // get the pointer to the row
        unsigned char* pixel_row = (unsigned char*)(buffer[0]);
        pixels.push_back(std::vector<Pixel>(info.output_width));

        // iterate over the pixels
        for (int i=0; i<info.output_width; i++)
        {
            //create a Pixel from Pixel
            Pixel Pixel ;
            //get RGB values
            Pixel.setR((*pixel_row++));
            Pixel.setG((*pixel_row++));
            Pixel.setB((*pixel_row++));

            Pixel.setPosx(i);
            Pixel.setPosy(numlines);

            // ligne / colonne ? ou colonne / ligne ?
            pixels[numlines][i] = Pixel;

        }

		//*p2 += numlines * 3 * info.output_width; // pour utiliser texData (texture)
        numlines++; //parcourir les lignes
    }

    while(info.output_scanline < info.output_height)
    {
        numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
        *p2 += numlines * 3 * info.output_width;
    }

//    std::cout << "taille :" <<info.output_width<<" " << info.output_height <<" "<< numlines <<std::endl;       // -- DEBUG

    jpeg_finish_decompress(&info);   //finish decompressing this file

    fclose(file);                    //close the file

    return true;
}

bool ImageJPEG :: loadTexture(char * FileName, bool Fast){

        FILE* file = fopen(FileName, "rb");  //open the file
        struct jpeg_decompress_struct info;  //the jpeg decompress info
        struct jpeg_error_mgr err;           //the error handler

        info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
        jpeg_create_decompress(&info);       //sets info to all the default stuff

        //if the jpeg file didnt load exit
        if(!file)
        {
            fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
            return false;
        }

        jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

        jpeg_read_header(&info, TRUE);   //tell it to start reading it

        //if it wants to be read fast or not
        if(Fast)
        {
            info.do_fancy_upsampling = FALSE;
        }

        jpeg_start_decompress(&info);    //decompress the file

        //set the x and y
        x = info.output_width;
        y = info.output_height;
        channels = info.num_components;

        type = GL_RGB;

        if(channels == 4)
        {
            type = GL_RGBA;
        }

        bpp = channels * 8;

        size = x * y * 3;

        //read turn the uncompressed data into something ogl can read
        texData = new GLbyte[size];      //setup data for the data its going to be handling

        GLbyte* p1 = texData;
        GLbyte** p2 = &p1;
        int numlines = 0;

        while(info.output_scanline < info.output_height)
        {
            numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
            *p2 += numlines * 3 * info.output_width;
        }

        jpeg_finish_decompress(&info);   //finish decompressing this file

        fclose(file);                    //close the file

        return true;
}

GLuint ImageJPEG::getType() const {
	return type;
}

unsigned long ImageJPEG :: getX() const{
    return x;
}
unsigned long ImageJPEG :: getY() const{
    return y;
}

GLuint ImageJPEG::getID() const {
	return id;
}
GLuint* ImageJPEG::getPtrID() {
	return &id;
}
GLbyte* ImageJPEG::getData() const {
    return texData;
}

Pixel ImageJPEG :: getPixel(int h, int l) const{
    if ((h>x || l>y))
    {
        Pixel Error;
//        Error.R, Error.G, Error.B =0,0,0;
        std::cout << "Veuillez renseigner un pixel présent dans l'image" << std::endl;
        return Error;
    }
    else{ return pixels[h][l];}

}

vector<vector<Pixel>> * ImageJPEG :: getMatPixel(){
        return &pixels ;
}
