//
// Created by alicia on 04/12/2019.
//

#ifndef P1RV_MYWINDOW_H
#define P1RV_MYWINDOW_H

#include "interface.h"
#include <GL/glu.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QGridLayout>

class MyWindow : public Interface {
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    QPushButton *m_bouton_quit;
    QPushButton *m_bouton_load; //choix de charger map ou texture
    QPushButton *m_bouton_param; //pour changement d'échelle (a voir)
    QPushButton *m_bouton_save; //sauvegarder en stl

    signals:

public slots:
    void openFile();
    void saveFile();
    void chooseParam();
};


#endif //P1RV_MYWINDOW_H
