/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * interface.h
 */

#ifndef P1RV_INTERFACE_H
#define P1RV_INTERFACE_H
#include <Qt>
#include <QtOpenGL>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QGLWidget>
#include <QGL>

class QWidget;

class Interface : public QGLWidget {
    Q_OBJECT
public:
    explicit Interface(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);

    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0; //afficher la scène OpenGL
    void toggleFullWindow();
    virtual void keyPressEvent( QKeyEvent *keyEvent );

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;
    bool b_Fullscreen;
};

#endif //P1RV_INTERFACE_H
