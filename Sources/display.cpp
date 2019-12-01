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
    window_width = 1080;
    window_high = 960;

    focale = 11.0f; //10
    near = 0.0f;
    far = 0.0f;

    choice_mat = 4;			// permet de sélectionner un matériau par défaut
    change_shade_model = false;
    projection = false;
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
    glutInitWindowSize(window_width, window_high);

    // création de la fenetre GLUT
    glutCreateWindow("Heightmap"); //remplacer "..." par argv[0] pour appel avec terminal

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
        case 'p':
        {
            std::cout << "Projection : Orthogonale <-> Perspective " << std::endl;
            projection = !projection;
        }
            break;
        case 's':
		{
            std::cout << "Shade Model : " << std::endl;
            if(change_shade_model){
                glShadeModel(GL_SMOOTH);
                std::cout << "GL_SMOOTH - rendu de Phong, 1 normale par sommets" << std::endl;
            } else {
                glShadeModel(GL_FLAT);
                std::cout << "GL_FLAT - eclairage constant, 1 normale par faces" << std::endl;
            }
            change_shade_model = !change_shade_model;
            glutPostRedisplay();
		}
            break;
        case 'd':
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
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
			choice_mat = (choice_mat + 1) % 5;
			Material((int)choice_mat);
            glutPostRedisplay();
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
    window_width = w;
    window_high = h;

    // eviter une division par 0
    if(window_high == 0)
        window_high = 1;

    GLdouble ratio = (GLfloat)window_width / (GLfloat)window_high;
    std::cout << "Ratio : " << ratio << std::endl;

    top = 1.0f;
    bottom = -1.0f;
    left = -ratio;
    right = ratio;

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, window_width, window_high);

    // Mise en place de la perspective
    if(projection){
        gluOrtho2D(left,right,bottom,top);
    } else {
        gluPerspective(focale, ratio, near, far);
    }

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}

GLvoid Display :: applyLights()
{
    GLfloat lightpos[] = { 0.0f, 0.0f, 15.0f };
    GLfloat lightcolor[] = { 1.0f, 1.0f, 0.0f };
    GLfloat ambcolor[] = { 0.0f, 0.0f, 1.0f };
    GLfloat surf_diffuse[]={0.8,0.8,0.0,1.0};

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);                               // enable lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);     // ambient light
    glMaterialfv(GL_FRONT,GL_DIFFUSE,surf_diffuse );

    glEnable(GL_LIGHT0);                                 // enable light source
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);           // config light source
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightcolor);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

}

int Display :: getWindowW() {
    return window_width;
}
int Display ::getWindowH() {
    return window_high;
}





