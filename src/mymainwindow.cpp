/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mymainwindow.cpp
 */

#include "mymainwindow.h"



MyMainWindow::MyMainWindow() {

    //Titre de l'appli
    setWindowTitle("HeightMap Creator Tool    -  BEHRA & MARAVAT");

    //Permet d'avoir plusieurs fenetre dans notre fenetre principale
    zoneCentrale = new QMdiArea;

    //On creer 2 fenetres
    fenetre_opengl = new MyWindow(this);
    fenetre_canvas = new MyCanvas(this);
    //QTextEdit *zoneTexte2 = new QTextEdit("Drawing Heightmap");

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

    //sous-menu Edit
    params = new QAction("&Parameters",fenetre_opengl); //parametre modifiable
    //ajout a l'onglet Edit
    menuEdition->addAction(params);

    //Onglet View
    menuAffichage = menuBar()->addMenu("&View");

    //sous-menu Edit
    openHeightMap = new QAction("&Heightmap",rendu_3d);
    openHeightMap->setCheckable(true);
    openHeightMap->setChecked(true);
    openDraw = new QAction("&Draw",dessin);
    openDraw->setCheckable(true);
    openDraw->setChecked(true);

    //ajout a l'onglet Edit
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
    //connect(config, SIGNAL(triggered()), this, SLOT());
    connect(params, SIGNAL(triggered()), fenetre_opengl,SLOT(chooseParam()));
    connect(openHeightMap, SIGNAL(triggered()), this,SLOT(viewWindow()));
    connect(openDraw, SIGNAL(triggered()), this,SLOT(viewWindow()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutApp()));
}
//TODO dans le menu Edit, ajouter la possibilite à l'utilisateur de réouvrir une fenetre fermée (ex: visualisation de l'image)
// ou Fenetre OpenGL


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

void MyMainWindow::setConfig(){
    //TODO mettre le changement de langue ou autre

}

void MyMainWindow::viewWindow(){

   if(openHeightMap->isChecked()){
       rendu_3d->show();
   } else {
       rendu_3d->hide();
   }
    if(openDraw->isChecked()){
        dessin->show();
    } else {
        dessin->hide();
    }
}
