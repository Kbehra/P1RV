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
#include <QToolBar>

class MyMainWindow : public QMainWindow {
    Q_OBJECT
public:
    MyMainWindow();
    void setFileName(QString filename);


private:

    //zone centrale
    QMdiArea *zoneCentrale;

    //sous-fenetres
    QMdiSubWindow *dessin;
    QMdiSubWindow *rendu_3d;

    bool b_Fullscreen_opengl; //full window opengl
    bool b_Fullscreen_draw; //full window canvas

    //widget de la fenetre opengl qui affiche notre map
    MyWindow* fenetre_opengl;               //consideree comme un QGLWidget
    MyCanvas* fenetre_canvas;               //la toile

    //menus
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QMenu *menuAide;

    //dans file
    QAction *chargerMap;
    QAction *chargerTex;
    QAction *exportFile;
    QAction *config;
    QAction *actionQuitter;

    //Changer les parametres d'affichage
    QAction *params;
    QAction *drawtool;

    //action pour ouvrir/fermer les deux fenetres a l'interieur
    QAction *openHeightMap;
    QAction *openDraw;

    //help
    QAction *about;
    QAction *shortcutHelp;

    //toolbar
    QToolBar *toolBarDraw;
    QAction *changeColor;
    QLabel *namepenwidth;
    QDoubleSpinBox *setPenWidth;
    QAction *setRound;
    QAction *setSquare;

    QString filename;


public slots:
    void aboutApp();
    void shortcut();
    void setConfig();
    void viewWindow();
    void viewToolBar();
    void changeIcon();
    void sendFileName();
    void toggleFullWindow(bool window);
    void getImage();

    signals:
        void FileNameChanged();
        void changeCapStyle(bool cap_style);
};


#endif //P1RV_MYMAINWINDOW_H
