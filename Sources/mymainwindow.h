/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mymainwindow.h
 */
#ifndef P1RV_MYMAINWINDOW_H
#define P1RV_MYMAINWINDOW_H
#include "mywindow.h"
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

public:
    MyMainWindow();

private:
    MyWindow* fenetre_opengl; //consideree comme un QGLWidget

public slots:
    void setConfig();
};


#endif //P1RV_MYMAINWINDOW_H
