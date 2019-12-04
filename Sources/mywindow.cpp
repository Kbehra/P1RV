//
// Created by alicia on 04/12/2019.
//
#include "interface.h"
#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : Interface (60, parent, (char *)"Premier poly" )
{

}

void MyWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glTranslatef(3.0f, 0.0f, -6.0f);

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3d(1.0f, 1.0f, 0.0f);
    glEnd();
}

//SLOTS
void MyWindow::openFile()
{

    //QMessageBox::information(this, "Titre de la fenêtre", "Bienvenu dans l'application HeightMap !");
    //QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous avez selectionner....!");
    //QMessageBox::critical(this, "Titre de la fenêtre", "Erreur: Vous blabla!");
    QString dossier = QFileDialog::getExistingDirectory(this);
    QString file = QFileDialog::getOpenFileName(this, "Choose your file", QString(), "Images (*.jpg *.jpeg)");
    QMessageBox::information(this, "File", "This file had been selected :\n" + file);
    //TODO : relier le chemin avec la fonction pour lire heightmap

}

void MyWindow::openTex()
{

    //QMessageBox::information(this, "Titre de la fenêtre", "Bienvenu dans l'application HeightMap !");
    //QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous avez selectionner....!");
    //QMessageBox::critical(this, "Titre de la fenêtre", "Erreur: Vous blabla!");
    QString dossier = QFileDialog::getExistingDirectory(this);
    QString file = QFileDialog::getOpenFileName(this, "Choose your file", QString(), "Images (*.jpg *.jpeg)");
    QMessageBox::information(this, "File", "This file had been selected :\n" + file);
    //TODO : relier le chemin avec la fonction pour mettre texture

}

void MyWindow::saveFile()
{
    QMessageBox::information(this, "Save as (.stl)", "Enter the name of your file :");


    QString file_saved = QFileDialog::getSaveFileName(this, "Save Heightmap", QString(), "Images (*.stl)");
    //TODO : relier avec l'enregistrement en stl


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