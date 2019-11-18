//
// Created by alicia on 14/11/2019.
//

#ifndef P1RV_HEIGHTMAPS_BEHRA_MARAVAT_SHADER_H
#define P1RV_HEIGHTMAPS_BEHRA_MARAVAT_SHADER_H
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include "loadjpeg.h"

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
    Shader(string vertexSource, string fragmentSource);
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
