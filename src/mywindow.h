/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mywindow.h
 */
#ifndef P1RV_MYWINDOW_H
#define P1RV_MYWINDOW_H

#include "interface.h"
#include "loadjpeg.h"
#include "createmap.h"
#include "material.h"
#include <GL/glu.h>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QSlider>
#include <QComboBox>
#include <QLCDNumber>

class MyWindow : public Interface {
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);

    GLvoid applyLights();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);

private:
    ImageJPEG monimage;
    CreateMap my_map;

    int choice_mat;
    bool shade_model;
    bool projection;
    QString pas_selected;
    float convert;
    GLfloat pas;

    bool press;

    //liens
    QString default_directory;
    QString default_texture;

    // ratio de l'image
    float ratio;

    //Ortho
    float left;
    float right;
    float top;
    float bottom;

    //Perspective
    float focale;
    float near;
    float far;

    //camera
    Camera cam;

    //fenetre de parametre
    QWidget fenetre;
    QTabWidget *onglets; //onglets de la fenetre
    QWidget *page1;
    QWidget *page2;

    QPushButton *apply_change;
    QPushButton *not_apply;
    QLabel *nameproj;
    QComboBox *chooseprojection;
    QLabel *nameshade;
    QComboBox *chooseshader;
    QLabel *namepas;
    QLCDNumber *m_lcd;

    //pour sauvegarder avant de quitter
    int maybeSave();

public slots :
    virtual void closeEvent(QCloseEvent *);
    void openFile();
    void openTex();
    void saveFile();
    void convertPas(int num);
    void changeParam();
    void chooseParam();
    void setHelpText(int index);
    void setHelpText2(int useless);
};


#endif //P1RV_MYWINDOW_H
