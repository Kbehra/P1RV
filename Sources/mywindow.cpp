//
// Created by alicia on 04/12/2019.
//
#include "interface.h"
#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : Interface (60, parent, (char *)"Premier poly" )
{
    // Construction du bouton
    m_bouton_quit = new QPushButton("Close", this);
    m_bouton_quit->setFont(QFont("Comic Sans MS", 14));

    // Bouton pour charger soit une 'map' soit une texture
    m_bouton_load = new QPushButton("File", this);
    m_bouton_load->setFont(QFont("Comic Sans MS", 14));

    // Bouton pour modifier les parametre (echelle, pas, scale, perspective...)
    m_bouton_param = new QPushButton("Settings", this);
    m_bouton_param->setFont(QFont("Comic Sans MS", 14));

    // Bouton pour sauvegarder au format stl le rendu obtenu
    m_bouton_save = new QPushButton("Save", this);
    m_bouton_save->setFont(QFont("Comic Sans MS", 14));

    //placement des boutons
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_bouton_load, 0, 0);
    layout->addWidget(m_bouton_save, 0, 1);
    layout->addWidget(m_bouton_param, 0, 2);
    layout->addWidget(m_bouton_quit, 20, 20);

    setLayout(layout);

    QObject::connect(m_bouton_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_bouton_load, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject::connect(m_bouton_save, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(m_bouton_param, SIGNAL(clicked()), this, SLOT(chooseParam()));
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

void MyWindow::openFile()
{

    //QMessageBox::information(this, "Titre de la fenêtre", "Bienvenu dans l'application HeightMap !");
    //QMessageBox::warning(this, "Titre de la fenêtre", "Attention, vous avez selectionner....!");
    //QMessageBox::critical(this, "Titre de la fenêtre", "Erreur: Vous blabla!");
    QMessageBox::question(this, "File", "Would you like to open a new file?", QMessageBox::Open | QMessageBox::Cancel);

    if(QMessageBox :: Open){
        QString dossier = QFileDialog::getExistingDirectory(this);
        QString file = QFileDialog::getOpenFileName(this, "Choose your file", QString(), "Images (*.jpg *.jpeg)");
        QMessageBox::information(this, "File", "This file had been selected :\n" + file);
        //TODO : relier le chemin avec la fonction pour lire heightmap
    }

}

void MyWindow::saveFile()
{
    QMessageBox::question(this, "Save the file", "Do you want to save as a .stl file ?", QMessageBox::Save | QMessageBox::Cancel);

    if(QMessageBox::Save){
        QString fichier = QFileDialog::getSaveFileName(this, "Save Heightmap", QString(), "Images (*.stl)");
        //TODO : relier avec l'enregistrement en stl
    } else {
        //NOTHING TO DO
    }
}

void MyWindow::chooseParam()
{
    QMessageBox::question(this, "Save the file", "Do you want to save as a .stl file ?", QMessageBox::Yes | QMessageBox::No);

    if(QMessageBox::Yes){
        QString fichier = QFileDialog::getSaveFileName(this, "Save Heightmap", QString(), "Images (*.stl)");
        //TODO : relier avec l'enregistrement en stl
    } else {
        //NOTHING TO DO
    }
}