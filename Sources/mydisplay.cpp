/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * display.cpp
 */
#include "mydisplay.h"

extern Camera cam;
extern CreateMap my_map;
extern MyDisplay go_display;



MyDisplay :: MyDisplay() {
    window_width = 1080;
    window_high = 960;

    focale = 11.0f; //10
    near = 0.0f;
    far = 0.0f;

    choice_mat = 4;			// permet de sélectionner un matériau par défaut
    change_shade_model = false;
    projection = false;
    pas = 0.10;

}

void MyDisplay :: initWindow(int argc, char *argv[]){

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
    glClearColor(0.95f, 0.95f, 0.95f, 0.95f);

    // Initialement on active le Z-buffer
	//glEnable(GL_DEPTH_TEST);

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

GLvoid MyDisplay :: clavier (unsigned char touche, int x, int y)
{
    switch(touche)
    {
        case 'p':
        {
            // change projection mode
            std::cout << "Projection : Orthogonale <-> Perspective " << std::endl;
            projection = !projection;
        }

            break;
        case 's':
		{
            std::cout << "Shade Model : " << std::endl;
            if(change_shade_model)
            {
                glShadeModel(GL_SMOOTH);
                std::cout << "GL_SMOOTH - rendu de Phong, 1 normale par sommets" << std::endl;
            }
            else
            {
                glShadeModel(GL_FLAT);
                std::cout << "GL_FLAT - eclairage constant, 1 normale par faces" << std::endl;
            }
            change_shade_model = !change_shade_model;
            glutSwapBuffers();
            glFlush();
            glutPostRedisplay();
		}
            break;
        case 'd':
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
            glutSwapBuffers();
            glFlush();
			glutPostRedisplay();
		}
            break;
        case 'w':
		{
			glDisable(GL_DEPTH_TEST);
            glutSwapBuffers();
            glFlush();
			glutPostRedisplay();
		}
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
                float scale = my_map.getScale();
                my_map.changeScale(scale+=pas);
                std::cout << my_map.getScale() << std::endl;
                glutSwapBuffers();
                my_map.generateMap();
                glutPostRedisplay();
            }
            break;
        case '-':
            {
                float scale = my_map.getScale();
                my_map.changeScale(scale-=pas);
                std::cout << my_map.getScale() << std::endl;
                glutSwapBuffers();
                my_map.generateMap();
                glutPostRedisplay();
            }
            break;
        case 'o':
        {
            my_map.exportToSTL();

        }
        default:
		{}
            break;
    }
    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();
}

GLvoid MyDisplay :: redimensionner(int w, int h) {

    // Garde les valeurs
    window_width = w;
    window_high = h;

    // eviter une division par 0
    if(window_high == 0)
    {
        window_high = 1;
    }
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
    if(projection)
    {
        gluOrtho2D(left,right,bottom,top);
    }
    else
    {
        gluPerspective(focale, ratio, near, far);
    }

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}

GLvoid MyDisplay :: applyLights()
{
    // Lumiere
    GLfloat lightpos[] = { 20.5f, 20.0f, 20.5f,20.5f };
    GLfloat lightcolor[] = { 1.0f, 1.0f, 1.0f,0.5f };
    GLfloat ambcolor[] = { 0.9f, 0.9f, 1.0f,0.9f};
    GLfloat lightambient[] = {10.0f, 10.0f,10.0f, 0.0f};

    glEnable(GL_LIGHTING);                               // enable lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);     // ambient light


    glEnable(GL_LIGHT0);                                 // enable light source
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);           // config light source
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

}

int MyDisplay :: getWindowW() {
    return window_width;
}
int MyDisplay ::getWindowH() {
    return window_high;
}





