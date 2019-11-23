//
// Created by alicia on 14/11/2019.
//


#include "shader.h"


//Constructeurs
Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{

}

Shader::Shader(char* vertexSource, char* fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                             m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{

}

Shader::Shader(Shader const& shaderACopier)
{
	// Copie des fichiers sources
	m_vertexSource = shaderACopier.m_vertexSource;
	m_fragmentSource = shaderACopier.m_fragmentSource;

	// Chargement du nouveau shader
	charger();
}

// Destructeur
Shader::~Shader()
{
	/*
	// Destruction du shader
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
	*/
}

//surcharge operateur =
Shader& Shader::operator=(Shader const& shaderACopier)
{
	// Copie des fichiers sources
	m_vertexSource = shaderACopier.m_vertexSource;
	m_fragmentSource = shaderACopier.m_fragmentSource;

	// Chargement du nouveau shader
	charger();

	// Retour du pointeur this
	return *this;
}

//méthodes
GLuint Shader::getProgramID() const
{
    return m_programID;
}

void Shader::bind() {
	glUseProgram(m_programID);
}

void Shader::unbind() {
	glUseProgram(0);
}

bool Shader::charger()
{
	// Destruction d'un éventuel ancien Shader
	if (glIsShader(m_vertexID) == GL_TRUE)
	{
		glDeleteShader(m_vertexID);
	}

	if (glIsShader(m_fragmentID) == GL_TRUE)
	{
		glDeleteShader(m_fragmentID);
	}

	if (glIsProgram(m_programID) == GL_TRUE) 
	{
		glDeleteProgram(m_programID);
	}

	// Compilation des shaders
	if (!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
		return false;

	if (!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
		return false;

	// Création du programme
	m_programID = glCreateProgram();

	// Association des shaders
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);

	// Verrouillage des entrées shader
	glBindAttribLocation(m_programID, 0, "in_Vertex");
	glBindAttribLocation(m_programID, 1, "in_Color");
	glBindAttribLocation(m_programID, 2, "in_TexCoord0");

	// Linkage du programme
	glLinkProgram(m_programID);

	// Linkage du programme
	glLinkProgram(m_programID);

	// Vérification du linkage
	GLint erreurLink(0);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

	// S'il y a eu une erreur
	if (erreurLink != GL_TRUE)
	{
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char* erreur = new char[tailleErreur + 1];

		// Récupération de l'erreur
		glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		cout << erreur << endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteProgram(m_programID);

		return false;
	}
	else   // Sinon c'est que tout s'est bien passé
	{
		return true;
	}
}

/*
 * shader = le shader à compiler
 * type = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}
 * filename = code source associé au shader
*/
bool Shader::compilerShader(GLuint& shader, GLenum type, std::string const& fichierSource)
{
	// Création du shader
	shader = glCreateShader(type);

	// Vérification du shader
	if (shader == 0)
	{
		cout << "Erreur, le type de shader (" << type << ") n'existe pas" << endl;
		return false;
	}

	// Flux de lecture
	ifstream fichier(fichierSource.c_str());

	// Test d'ouverture
	if (!fichier)
	{
		cout << "Erreur le fichier " << fichierSource << " est introuvable" << endl;
		glDeleteShader(shader);

		return false;
	}

	// Strings permettant de lire le code source
	string ligne;
	string codeSource;

	// Lecture
	while (getline(fichier, ligne)) 
	{
		codeSource += ligne + '\n';
	}

	// Fermeture du fichier
	fichier.close();

	// Récupération de la chaine C du code source
	const GLchar* chaineCodeSource = codeSource.c_str();

	// Envoi du code source au shader
	/*2eme param = nombre de chaine de caractere a envoyer -> ici string donc 1
	 *3eme param = sorte de double pointeur*/
	glShaderSource(shader, 1, &chaineCodeSource, 0);

	// Compilation du shader
	glCompileShader(shader);

	// Vérification de la compilation
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

	// S'il y a eu une erreur
	if (erreurCompilation != GL_TRUE)
	{
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char* erreur = new char[tailleErreur + 1];

		// Récupération de l'erreur
		/*shader : Le shader sur lequel on travaille
		 *taille erreur : Taille de chaine de caractère qui va accueillir l'erreur.
		*length : Adresse de la variable qui contiendra la taille précédente.
		*erreur : La chaine de caractère qui contiendra le message final.
		*/
		glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		cout << erreur << endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteShader(shader);

		return false;
	}
	else // Sinon c'est que tout s'est bien passé
	{
		return true;
	}
}

