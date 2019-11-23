//
// Created by alicia on 14/11/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_SHADER_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_SHADER_H
#define GLUT_DISABLE_ATEXIT_HACK
#pragma once 
#define GLEW_STATIC
#include<GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include <string>
#include <iostream>


using namespace std;

class Shader {

private:    //Attributs
    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    string m_vertexSource;
    string m_fragmentSource;

public:
    //Constructeurs & destructeur
    Shader();
    Shader(char* vertexSource, char* fragmentSource);
	Shader(Shader const& shaderACopier); //de recopie
    ~Shader();

	//surcharge de l'operateur =, application aux shaders
	Shader& operator=(Shader const& shaderACopier);

    //méthodes
	void bind();
	void unbind();
    GLuint getProgramID() const;
	bool charger();
	bool compilerShader(GLuint& shader, GLenum type, std::string const& fichierSource);

};


#endif //P1RV_HEIGHTMAPS_BEHRA_MARAVAT_SHADER_H
