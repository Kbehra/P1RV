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

}

void MyWindow::initializeGL()
{

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.95f, 0.95f, 0.95f, 0.95f);

    // Intialement on active le Z-buffer
    glEnable(GL_DEPTH_TEST);

    // on active les textures
    glEnable(GL_TEXTURE_2D);

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

/*
 * Ouverture d'un fichier "images"
 */
void MyWindow::openFile()
{

    QString file = QFileDialog::getOpenFileName(this, "Choose your file", QString(), "Images (*.jpg *.jpeg)");
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

void MyWindow::openTex()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose your file", QString(), "Images (*.jpg *.jpeg)");
    QMessageBox::information(this, "File", "This file had been selected :\n" + file);
    //TODO : relier le chemin avec la fonction pour mettre texture

}

void MyWindow::saveFile()
{

    QString file_saved = QFileDialog::getSaveFileName(this, "Save Heightmap", QString(), "Images (*.stl)");
    my_map.exportToSTL(file_saved.toStdString());

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