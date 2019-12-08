/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mymainwindow.cpp
 */

#include "mymainwindow.h"
#include <QTime>




MyMainWindow::MyMainWindow() {

    //Titre de l'appli
    setWindowTitle("HeightMap Creator Tool    -  BEHRA & MARAVAT");

    //Permet d'avoir plusieurs fenetre dans notre fenetre principale
    zoneCentrale = new QMdiArea;

    b_Fullscreen_opengl = true;
    b_Fullscreen_draw = true;
    //On creer 2 fenetres
    fenetre_opengl = new MyWindow(this);
    fenetre_canvas = new MyCanvas(this);
    fenetre_canvas->setWindowTitle("Canvas");

    //idealement on creer une fenetre a part qui viens se mettre dans la subwindow pour dessin
    dessin   = zoneCentrale->addSubWindow(fenetre_canvas);                        //second window
    rendu_3d = zoneCentrale->addSubWindow(fenetre_opengl);                        //first window

    zoneCentrale->tileSubWindows();
    setCentralWidget(zoneCentrale);

    //Onglet File
    menuFichier = menuBar()->addMenu("&File");
    //sous-menu File
    chargerMap = new QAction("&Load Map...", fenetre_opengl);
    chargerMap->setShortcut(QKeySequence("Ctrl+M"));
    chargerTex = new QAction("&Load Texture...", fenetre_opengl);
    chargerTex->setShortcut(QKeySequence("Ctrl+T"));
    exportFile = new QAction("&Export (.stl)", fenetre_opengl);
    exportFile->setShortcut(QKeySequence("Ctrl+S"));
    config = new QAction("&Settings", this); //options de langues, couleur fenetre...
    actionQuitter = new QAction("&Quit", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    //ajout a l'onglet File
    menuFichier->addAction(chargerMap);
    menuFichier->addAction(chargerTex);
    menuFichier->addAction(exportFile);
    menuFichier->addAction(config);
    menuFichier->addAction(actionQuitter);

    //Onglet Edit
    menuEdition = menuBar()->addMenu("&Edit");
    toolBarDraw = addToolBar("&Drawing Tool");
    changeColor = new QAction(toolBarDraw);
    changeColor->setIcon(QIcon("../icons/icon_seau_couleur.png"));
    namepenwidth = new QLabel("Pen Width:");
    setPenWidth = new QDoubleSpinBox(toolBarDraw);
    setPenWidth->setMinimum(1.0);
    setPenWidth->setMaximum(60.0);
    setPenWidth->setDecimals(1);
    setRound = new QAction(toolBarDraw);
    setRound->setIcon(QIcon("../icons/icon_pinceau.png"));
    setRound->setEnabled(false);
    setSquare = new QAction(toolBarDraw);
    setSquare->setIcon(QIcon("../icons/icon_rouleau_peinture.png"));
    setSquare->setEnabled(true);
    toolBarDraw->addAction(changeColor);
    toolBarDraw->addSeparator();
    toolBarDraw->addWidget(namepenwidth);
    toolBarDraw->addWidget(setPenWidth);
    toolBarDraw->addSeparator();
    toolBarDraw->addAction(setRound);
    toolBarDraw->addAction(setSquare);
    toolBarDraw->addSeparator();
    toolBarDraw->hide();

    //sous-menu Edit
    params = new QAction("&Parameters",fenetre_opengl); //parametre modifiable
    drawtool = new QAction("&Drawing Tool",fenetre_canvas);
    drawtool->setCheckable(true);
    drawtool->setChecked(false);

    //ajout a l'onglet Edit
    menuEdition->addAction(params);
    menuEdition->addAction(drawtool);

    //Onglet View
    menuAffichage = menuBar()->addMenu("&View");

    //sous-menu View
    openHeightMap = new QAction("&Heightmap",rendu_3d);
    openHeightMap->setCheckable(true);
    openHeightMap->setChecked(true);
    openDraw = new QAction("&Draw",dessin);
    openDraw->setCheckable(true);
    openDraw->setChecked(true);

    //ajout a l'onglet View
    menuAffichage->addAction(openHeightMap);
    menuAffichage->addAction(openDraw);

    //Onglet Help
    menuAide = menuBar()->addMenu("&Help");

    //sous-menu Help
    about = new QAction(tr("&About.."), this);

    //ajout a l'onglet Help
    menuAide->addAction(about);

    //Connects
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(chargerMap, SIGNAL(triggered()), fenetre_opengl, SLOT(openFile()));
    connect(chargerTex, SIGNAL(triggered()), fenetre_opengl, SLOT(openTex()));
    connect(exportFile, SIGNAL(triggered()), fenetre_opengl, SLOT(saveFile()));
    connect(params, SIGNAL(triggered()), fenetre_opengl,SLOT(chooseParam()));
    connect(drawtool, SIGNAL(triggered()), this,SLOT(viewToolBar()));
    connect(openHeightMap, SIGNAL(triggered()), this,SLOT(viewWindow()));
    connect(openDraw, SIGNAL(triggered()), this,SLOT(viewWindow()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutApp()));
    connect(this, SIGNAL(FileNameChanged()), fenetre_canvas, SLOT(openImageGo()));
    connect(changeColor, SIGNAL(triggered()), fenetre_canvas, SLOT(changeBrushColor()));
    connect(setPenWidth,SIGNAL(valueChanged(double)),fenetre_canvas,SLOT(changePenWidth(double)));
    connect(setRound, SIGNAL(triggered()), this, SLOT(changeIcon()));
    connect(setSquare, SIGNAL(triggered()), this, SLOT(changeIcon()));
}

//SLOT
void MyMainWindow::aboutApp()
{
    QMessageBox::about(this, "A propos de Application",
                       "<b>Application</b> permet de creer des Heightmaps "
                          "personnalisee avec differents parametre. Il est possible "
                          "de sauvegarder le rendu 3D au format (.stl)."
                          "Explication des raccourcis:");
    //TODO mettre tout les raccourci clavier utiles
}

void MyMainWindow::setConfig()
{
    //TODO mettre le changement de langue ou autre

}

void MyMainWindow::viewWindow(){

   if(openHeightMap->isChecked())
   {
       rendu_3d->show();
   }
   else
   {
       rendu_3d->hide();
   }
   if(openDraw->isChecked())
   {
        dessin->show();
   }
   else
   {
        dessin->hide();
   }
}

void MyMainWindow::viewToolBar()
{
    if(drawtool->isChecked())
    {
        toolBarDraw->show();
    }
    else
    {
        toolBarDraw->hide();
    }
}


void MyMainWindow::changeIcon() {
    if(setRound->isEnabled())
    {
        setRound->setEnabled(false);
        setSquare->setEnabled(true);
        emit changeCapStyle(true); //round =false
    }
    else
    {
        setSquare->setEnabled(false);
        setRound->setEnabled(true);
        emit changeCapStyle(false); //square = true
    }
}

void MyMainWindow::sendFileName()
{
    fenetre_canvas->setFileName(fenetre_opengl->getFileName());
}

void MyMainWindow::setFileName(QString filename)
{
    this->filename=filename;
    emit FileNameChanged();
}

void MyMainWindow::toggleFullWindow(bool window)
{
    if(window)
    {
        if(b_Fullscreen_opengl)
        {
            rendu_3d->showMaximized();
            b_Fullscreen_opengl = false;
        }
        else
        {
            rendu_3d->showNormal();
            b_Fullscreen_opengl = true;
        }
    }
    else {
        if (b_Fullscreen_draw) {
            dessin->showMaximized();
            b_Fullscreen_draw = false;
        } else {
            dessin->showNormal();
            b_Fullscreen_draw = true;
        }
    }
}

void MyMainWindow::getImage() {
    QImage image = fenetre_canvas->getImage();
    fenetre_opengl->setImage(image);

}