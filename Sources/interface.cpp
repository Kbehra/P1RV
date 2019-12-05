/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * interface.cpp
 */
#include <iostream>
#include "interface.h"

Interface::Interface(int framesPerSecond, QWidget *parent, char *name) : QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name)); //permet de définir le nom de la fenêtre :param name
    b_Fullscreen = false ;
    shade_model = false ;
    if(framesPerSecond == 0)
    {
        t_Timer = NULL;
    }
    else
    {   //Controle du temps entre deux images rendus par OpenGL
        int seconde = 100000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
}

void Interface::toggleFullWindow()
{
    if(b_Fullscreen)
    {
        showNormal();
        b_Fullscreen = false;
    }
    else
    {
        showFullScreen();
        b_Fullscreen = true;
    }
}

/* Evenement clavier*/
void Interface::keyPressEvent(QKeyEvent *keyEvent)
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
    }
}

//SLOT
void Interface::timeOutSlot()
{
    updateGL();
}