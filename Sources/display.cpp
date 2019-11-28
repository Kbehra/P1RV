/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * display.cpp
 */
#include "display.h"

extern Camera cam;
extern CreateMap map;
extern Display goDisplay;



Display :: Display() {
    windowW = 1080;
    windowH = 960;

    focale = 11.1f;
    Near = 0.00f;
    Far = 0.0f;

    choiceMat = 4;			// permet de sélectionner un matériau par défaut 

    pas = 0.1;

}

void Display :: initWindow(int argc, char *argv[]){

    // initialisation de GLUT
    glutInit(&argc, argv);

    // choix du mode d'affichage (ici RGB)
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    // position initiale de la fenetre GLUT
    glutInitWindowPosition(0,0);

    // taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);

    // création de la fenetre GLUT
    glutCreateWindow("Heightmap");

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialement on active le Z-buffer
	glEnable(GL_DEPTH_TEST);

	//active texture
	glEnable(GL_TEXTURE_2D);

    // Lumiere
   applyLights();

	// fonctions de callback
	glutDisplayFunc(affichage);
	glutReshapeFunc(rezise);
	glutKeyboardFunc(keyBoard);
	glutMouseFunc(souris);
	glutMotionFunc(deplacementSouris);

}

GLvoid Display :: clavier (unsigned char touche, int x, int y){
    // Suivant les touches pressees, nous aurons un comportement different de l'application
    // ESCAPE ou 'q' : fermera l'application
    // 'p' : affichage du carre plein
    // 'f' : affichage du carre en fil de fer
    // 's' : affichage des sommets du carre
    switch(touche)
    {
        case 'z':
		{
			std::cout << "Z" << std::endl;
		}
            break;
        case 'q':
		{
			std::cout << "Q" << std::endl;
		}
            break;
        case 's':
		{
			std::cout << "S" << std::endl;
		}
            break;
        case 'd':
		{
			glEnable(GL_DEPTH_TEST);
			glutPostRedisplay();
		}
            break;
        case 'w':
		{
			std::cout << "w" << std::endl;
			glDisable(GL_DEPTH_TEST);
			glutPostRedisplay();
		}
            break;
        case 'e':
            break;
        case 'm':
		{
			// change de the default material
			choiceMat = (choiceMat + 1) % 5;
			Material((int)choiceMat);
		}
            break;
        case '+':
            {
                float scale = map.getScale();
                map.changeScale(scale+=pas);
                std::cout << map.getScale() << std::endl;
                glutSwapBuffers();
                map.generateMap();
                glutPostRedisplay();
            }
            break;
        case '-':
            {
                float scale = map.getScale();
                map.changeScale(scale-=pas);
                std::cout << map.getScale() << std::endl;
                glutSwapBuffers();
                map.generateMap();
                glutPostRedisplay();
            }
            break;
        default:
		{}
            break;
    }
    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();
}

GLvoid Display :: redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;

    // eviter une division par 0
    if(windowH==0)
        windowH = 1;

    float ratio = (float)windowW / (float)windowH;
    std::cout << "Ratio : " << ratio << std::endl;

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, windowW, windowH);

    // Mise en place de la perspective
    gluPerspective(focale, ratio, Near, Far);


    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}

GLvoid Display :: applyLights()
{
    GLfloat lightpos[] = { 0.0f, 0.0f, 15.0f };
    GLfloat lightcolor[] = { 1.0f, 1.0f, 0.0f };
    GLfloat ambcolor[] = { 0.0f, 0.0f, 1.0f };

    glEnable(GL_LIGHTING);                               // enable lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);     // ambient light

    glEnable(GL_LIGHT0);                                 // enable light source
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);           // config light source
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightcolor);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

}

int Display :: getWindowW() {
    return windowW;
}
int Display ::getWindowH() {
    return windowH;
}





