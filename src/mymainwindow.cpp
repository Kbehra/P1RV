/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mymainwindow.cpp
 */

#include "mymainwindow.h"



MyMainWindow::MyMainWindow() {

    //Titre de l'appli
    setWindowTitle("HeightMap Creator Tool");

    //Permet d'avoir plusieurs fenetre dans notre fenetre principale
    QMdiArea *zoneCentrale = new QMdiArea;

    //On creer 2 fenetres
    fenetre_opengl = new MyWindow(this);
    QTextEdit *zoneTexte2 = new QTextEdit("Drawing Heightmap");

    QMdiSubWindow *dessin = zoneCentrale->addSubWindow(zoneTexte2); //second window
    QMdiSubWindow *rendu_3d = zoneCentrale->addSubWindow(fenetre_opengl); //first window

    zoneCentrale->tileSubWindows();
    setCentralWidget(zoneCentrale);

    //Onglet File
    QMenu *menuFichier = menuBar()->addMenu("&File");

    //sous-menu File
    QAction *chargerMap = new QAction("&Load Map...", fenetre_opengl);
    chargerMap->setShortcut(QKeySequence("Ctrl+M"));
    QAction *chargerTex = new QAction("&Load Texture...", fenetre_opengl);
    chargerTex->setShortcut(QKeySequence("Ctrl+T"));
    QAction *exportFile = new QAction("&Export (.stl)", fenetre_opengl);
    exportFile->setShortcut(QKeySequence("Ctrl+S"));
    QAction *config = new QAction("&Settings", this); //options de langues, couleur fenetre...
    QAction *actionQuitter = new QAction("&Quit", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    //ajout a l'onglet File
    menuFichier->addAction(chargerMap);
    menuFichier->addAction(chargerTex);
    menuFichier->addAction(exportFile);
    menuFichier->addAction(config);
    menuFichier->addAction(actionQuitter);

    //Onglet Edit
    QMenu *menuEdition = menuBar()->addMenu("&Edit");
    //sous-menu Edit
    QAction *params = new QAction("&Parameters",fenetre_opengl); //parametre modifiable
    //ajout a l'onglet Edit
    menuEdition->addAction(params);


    //Connects
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(chargerMap, SIGNAL(triggered()), fenetre_opengl, SLOT(openFile()));
    connect(chargerTex, SIGNAL(triggered()), fenetre_opengl, SLOT(openTex()));
    connect(exportFile, SIGNAL(triggered()), fenetre_opengl, SLOT(saveFile()));
    //connect(config, SIGNAL(triggered()), this, SLOT());
    connect(params, SIGNAL(triggered()), fenetre_opengl,SLOT(chooseParam()));

}
//TODO dans le menu Edit, ajouter la possibilite à l'utilisateur de réouvrir une fenetre fermée (ex: visualisation de l'image)
// ou Fenetre OpenGL


//SLOT
void MyMainWindow::setConfig(){
    //TODO mettre le changement de langue ou autre

}
