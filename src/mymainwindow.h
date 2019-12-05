/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mymainwindow.h
 */
#ifndef P1RV_MYMAINWINDOW_H
#define P1RV_MYMAINWINDOW_H
#include "mywindow.h"
#include "mycanvas.h"

#include <QtGui/QMainWindow>
#include <QApplication>
#include <QtGui/QMdiArea>
#include <QtGui/QTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QAction>
#include <QSlider>
#include <QComboBox>

class MyMainWindow : public QMainWindow {
    Q_OBJECT
public:
    MyMainWindow();

private:

    //zone centrale
    QMdiArea *zoneCentrale;

    //sous-fenetres
    QMdiSubWindow *dessin;
    QMdiSubWindow *rendu_3d;

    //widget de la fenetre opengl qui affiche notre map
    MyWindow* fenetre_opengl;                           //consideree comme un QGLWidget
    MyCanvas* fenetre_canvas;

    //menus
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QMenu *menuAide;

    QAction *chargerMap;
    QAction *chargerTex;
    QAction *exportFile;
    QAction *config;
    QAction *actionQuitter;

    //Changer les parametres d'affichage
    QAction *params;

    //action pour ouvrir/fermer les deux fenetres a l'interieur
    QAction *openHeightMap;
    QAction *openDraw;

    //help
    QAction *about;


public slots:
    void aboutApp();
    void setConfig();
    void viewWindow();
};


#endif //P1RV_MYMAINWINDOW_H
