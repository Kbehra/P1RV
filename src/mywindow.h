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
    CreateMap *my_map;

    int choice_mat;
    bool shade_model;
    bool projection;
    int pas_pixel;  //taille maillage

    QString scale_selected; //convertie en string la hauteur max choisie
    float converted_scale;  //convertir l'entier du slider en float
    GLfloat pas; //pas pour utiliser les touches '+' et '-' pour modifier la hauteur

    bool press;

    //liens
    QString default_directory;
    QString default_texture;
    QString filename;

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

    //image
    QImage image;

    //fenetre de parametre
    QWidget fenetre;
    QTabWidget *onglets; //onglets de la fenetre
    QWidget *page1;

    QPushButton *apply_change;
    QPushButton *not_apply;
    QLabel *nameproj;
    QComboBox *chooseprojection;
    QLabel *nameshade;
    QComboBox *chooseshader;
    QLabel *namepas;
    QLCDNumber *m_lcd_pas_pixel;
    QLabel *nameheight;
    QLCDNumber *m_lcd_map_height;
    QLabel *namemat;
    QComboBox *choosematerial;

    //pour sauvegarder avant de quitter
    int maybeSave();

public slots :
    virtual void closeEvent(QCloseEvent *);
    void openFile();
    void openTex();
    void saveFile();
    void changeParam();
    void chooseParam();
    void convertScale(int num);
    void setHelpText(int index);
    void setHelpText2(int useless);
    QString getFileName();
    void setImage(QImage image);

    signals:
        void youCanGetFileName();
        void setFullWindow(bool);
        void IWantImage();
};


#endif //P1RV_MYWINDOW_H
