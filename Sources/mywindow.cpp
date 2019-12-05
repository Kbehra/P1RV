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
}

void MyWindow::initializeGL()
{

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.95f, 0.95f, 0.95f, 0.95f);

    // Intialement on active le Z-buffer
    glEnable(GL_DEPTH_TEST);

    // on active les textures
    glEnable(GL_TEXTURE_2D);

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
//    if(height == 0)
//        height = 1;
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
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

    std::cout << "Je suis la" << std::endl;


    glLoadIdentity();
   // glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
    //glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);
    //glScalef(1.0f+(cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100));

    //glFlush();


    //glutSwapBuffers();
    //glutPostRedisplay();
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
            glutPostRedisplay();
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
            //glutSwapBuffers();
            my_map.generateMap();
            //glutPostRedisplay();
        }
            break;
    }
}

/*
 * Ouverture d'un fichier "images"
 */
void MyWindow::openFile()
{

    QFileDialog open_map(this);
    open_map.setViewMode(QFileDialog::Detail); //permet d'afficher en mode detail (modifiable)
    QString file = open_map.getOpenFileName(this, "Choose your file", "/home/alicia/CLion/Projets/P1RV/examples", "Images (*.jpg *.jpeg)");

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
    QString texture = open_tex.getOpenFileName(this, "Choose your texture", "/home/alicia/CLion/Projets/P1RV/examples", "Images (*.jpg *.jpeg)");

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
    QString file_saved = saveNewFile.getSaveFileName(this, "Save Heightmap", "/home/alicia/CLion/Projets/P1RV/examples", "Images (*.stl)");
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