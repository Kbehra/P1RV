/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mywindow.cpp
 */
#include "interface.h"
#include "mywindow.h"
#include "createmap.h"

MyWindow::MyWindow(QWidget *parent) : Interface (60, parent, (char *)"P1RV - Heightmap - BEHRA & MARAVAT" )
{

    window_width = 1080;
    window_high = 960;

    focale = 11.0f; //10
    near = 0.0f;
    far = 0.0f;

    choice_mat = 4;			// permet de sélectionner un matériau par défaut
    shade_model = false;
    projection = false;
    pas = 0.10;

    default_directory ="../examples/";

    // initialisation camera
    cam = Camera();
}

void MyWindow::initializeGL()
{

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.95f, 0.95f, 0.95f, 0.95f);

    // Intialement on active le Z-buffer
    glEnable(GL_DEPTH_TEST);

    // on active les textures
    glEnable(GL_TEXTURE_2D);

    // Initialisation lumière
    this->applyLights();

    // création d'une map vide
    my_map = CreateMap();

//    glShadeModel(GL_SMOOTH);
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0f);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    ratio = width/(GLfloat)height;

    top = 1.0f;
    bottom = -1.0f;
    left = -ratio;
    right = ratio;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Mise en place de la perspective
    if(projection)
    {
        gluOrtho2D(left,right,bottom,top);
    }
    else
    {
        gluPerspective(focale, ratio, near, far);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Tracer dans le contexte OpenGL
 */
void MyWindow::paintGL()
{

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // give a my_map a material
    my_map.generateMap();
    my_map.afficher();

    std::cout << "paintGL" << std::endl;            // --debug

    glLoadIdentity();
    std::cout << -cam.getAngleY() << " " << -cam.getAngleX()<< " "  << cam.getZoom()<< std::endl;

    glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
    glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);
    glScalef(1.0f+(cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100));

    glFlush();

    //updateGL();
}

void MyWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F1:
            toggleFullWindow();
            break;
        case Qt::Key_P:
        {
            // change projection mode
            std::cout << "Projection" << std::endl;
            if(projection){
                gluOrtho2D(left,right,bottom,top);
                std::cout << "Projection orthogonale 2D" << std::endl;
            } else {
                gluPerspective(focale, ratio, near, far);
                std::cout << "Projection perspective 3D" << std::endl;
            }
            projection = !projection;
        }
        case Qt::Key_S:
        {
            std::cout << "Shade Model : " << std::endl;
            if(shade_model){
                glShadeModel(GL_SMOOTH);
                std::cout << "GL_SMOOTH - rendu de Phong, 1 normale par sommets" << std::endl;
            } else {
                glShadeModel(GL_FLAT);
                std::cout << "GL_FLAT - eclairage constant, 1 normale par faces" << std::endl;
            }
            shade_model = !shade_model;
        }
        case Qt::Key_D:
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            //glutSwapBuffers();
            glFlush();
            //glutPostRedisplay();
        }
            break;
        case Qt::Key_W:
        {
            glDisable(GL_DEPTH_TEST);
            //glutSwapBuffers();
            glFlush();
            //glutPostRedisplay();
        }
            break;

        case Qt::Key_M:
        {
            // change de the default material
            choice_mat = (choice_mat + 1) % 5;
            Material((int)choice_mat);
            //glutPostRedisplay();
        }
            break;
        case Qt::Key_Plus:
        {
            float scale = my_map.getScale();
            my_map.changeScale(scale+=pas);
            std::cout << my_map.getScale() << std::endl;
            //glutSwapBuffers();
            my_map.generateMap();
            //glutPostRedisplay();
        }
            break;
        case Qt::Key_Minus:
        {
            float scale = my_map.getScale();
            my_map.changeScale(scale-=pas);
            std::cout << my_map.getScale() << std::endl;
            my_map.generateMap();

        }
            break;
    }
}

void MyWindow::mousePressEvent (QMouseEvent *event) {
    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    if (press)
        setCursor (Qt::ClosedHandCursor);
    // selection de l'action à effectuer
    cam.mouseState(event->button(), Qt::Key_Down, X, Y);
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event){

    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    // selection de l'action à effectuer
    cam.mouseState(event->button(), Qt::Key_Up, X, Y);

    // maj du contexte OpenGL
    updateGL();
}

void MyWindow::mouseMoveEvent (QMouseEvent *event) {
    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    // calcul de la transformation
    cam.mouseMove(X, Y);

    // maj du contexte OpenGL
    updateGL();

}

GLvoid MyWindow :: applyLights()
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

/*
 * Ouverture d'un fichier "images"
 */
void MyWindow::openFile()
{

    QFileDialog open_map(this);
    open_map.setViewMode(QFileDialog::Detail); //permet d'afficher en mode detail (modifiable)
    QString file = open_map.getOpenFileName(this, "Choose your file", default_directory, "Images (*.jpg *.jpeg)");

    if(file.isEmpty()){
        QMessageBox::warning(this,"Warning","No file selected.");
    } else {
        QMessageBox::information(this, "File", "This file had been selected :\n" + file);

        bool loaderimage = monimage.loadJPEG(file.toStdString().c_str());

        if (!loaderimage)
        {
            std::cout << "Impossible de charger l'image :" << file.toStdString() << " veuillez réessayer" << std::endl;
        }
        // création de la map à partir de l'image
        my_map = CreateMap(monimage);
        //my_map.generateMap();
    }

}

/*
 * Ouverture d'un fichier "images" pour la texture
 */
void MyWindow::openTex()
{
    QFileDialog open_tex(this);
    open_tex.setViewMode(QFileDialog::Detail); //permet d'afficher en mode detail (modifiable)
    QString texture = open_tex.getOpenFileName(this, "Choose your texture", default_directory, "Images (*.jpg *.jpeg)");

    if(texture.isEmpty()){
        QMessageBox::warning(this,"Warning","No texture selected.");
    } else {
        QMessageBox::information(this, "Texture", "This texture had been selected :\n" + texture);
        //TODO : relier le chemin avec la fonction pour mettre texture
    }

}

void MyWindow::saveFile()
{
    QFileDialog saveNewFile(this);
    QString file_saved = saveNewFile.getSaveFileName(this, "Save Heightmap", default_directory, "Images (*.stl)");
    my_map.exportToSTL(file_saved.toStdString());
    //TODO probleme si on selectionne rien
}

void MyWindow::chooseParam()
{
    QMessageBox::information(this, "Edit", "Parameters");
//    QSlider param1 = QSlider();
    QComboBox * projection = new QComboBox(); //add fenetre en question
    projection->addItem("Ortho");
    projection->addItem("Perspective");
    //TODO : relier avec les differents trucs a parametrer

}