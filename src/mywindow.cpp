/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mywindow.cpp
 */
#include "interface.h"
#include "mywindow.h"
#include "createmap.h"

MyWindow::MyWindow(QWidget *parent) : Interface (60, parent, (char *)"P1RV - Heightmap - BEHRA & MARAVAT" )
{

    setFocusPolicy(Qt::StrongFocus);     // permet d'activer les key evt dans la fenetre

    window_width = 1080;                        //USELESS
    window_high = 960;                          //USELESS

    focale = 10.0f; //10
    near = 0.0f;
    far = 0.0f;

    choice_mat = 4;			// permet de sélectionner un matériau par défaut
    shade_model = false;
    projection = false;
    pas = 0.10;

    default_directory ="../examples/";
    default_texture = "../examples/texture2.jpeg";

    // initialisation camera
    cam = Camera();

    //Pour les parametres
    fenetre.setWindowTitle("Edit");
    apply_change = new QPushButton("&Apply",&fenetre);
    apply_change->setGeometry(0, 0, 50, 25);
    not_apply = new QPushButton("&Cancel",&fenetre);
    not_apply->setGeometry(60, 0, 50, 25);

    // Création du QTabWidget pour parametre
    onglets = new QTabWidget(&fenetre);
    onglets->setGeometry(0, 30, 340, 260);
    // Créer 2 pages, en utilisant un widget parent pour contenir chacune des pages
    page1 = new QWidget;
    page2 = new QWidget;
    //Créer le contenu des pages de widgets
    // Page 1
    chooseprojection = new QComboBox(); //add fenetre en question
    chooseprojection->addItem("Perspective");
    chooseprojection->addItem("Ortho");
    chooseshader = new QComboBox(); //add fenetre en question
    chooseshader->addItem("Rendu de Phong");
    chooseshader->addItem("Eclairage constant");
    m_lcd = new QLCDNumber();
    m_lcd->setSegmentStyle(QLCDNumber::Flat);
    QSlider *slider_pas = new QSlider(Qt::Horizontal);
    slider_pas->setMaximum(10);
    slider_pas->setMinimum(1);
    slider_pas->setTickPosition(QSlider::TicksAbove);

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(chooseprojection);
    vbox1->addWidget(chooseshader);
    vbox1->addWidget(slider_pas);
    vbox1->addWidget(m_lcd);

    page1->setLayout(vbox1);

    //ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(page1, "Parameters");

    connect(apply_change, SIGNAL(clicked()), this, SLOT(changeParam()));
    connect(slider_pas, SIGNAL(valueChanged(int)), m_lcd, SLOT(display(int)));
    connect(not_apply, SIGNAL(clicked()), &fenetre, SLOT(close()));
}

void MyWindow::initializeGL()
{

    // définition de la couleur d'effacement du framebuffer
    glClearColor(0.95f, 0.95f, 0.95f, 0.95f);

    // Intialement on active le Z-buffer
    glEnable(GL_DEPTH_TEST);

    // on active les textures
    glEnable(GL_TEXTURE_2D);

    // Initialisation lumière
    this->applyLights();

    // création d'une map vide
    my_map = CreateMap();

    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyWindow::resizeGL(int width, int height)
{
    if(height == 0) {
        height = 1;
    }

    glViewport(0, 0, width, height);
    ratio = (GLfloat)width/(GLfloat)height;

    top = 1.0f;
    bottom = -1.0f;
    left = -ratio;
    right = ratio;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Mise en place de la perspective
    if(projection)
    {
        gluOrtho2D(left,right,bottom,top);
    }
    else
    {
        gluPerspective(focale, ratio, near, far);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Tracer dans le contexte OpenGL
 */
void MyWindow::paintGL()
{

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    my_map.generateMap();
    my_map.afficher();

    glLoadIdentity();
    glRotatef(-cam.getAngleY(), 1.0f, 0.0f, 0.0f);
    glRotatef(-cam.getAngleX(), 0.0f, 1.0f, 0.0f);
    glScalef(1.0f+(cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100), 1.0f + (cam.getZoom() / 100));

    glFlush();
}

int MyWindow::maybeSave(){
    QMessageBox closeornot;
    closeornot.setText("Do you want to save your changes?");
    closeornot.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    closeornot.setDefaultButton(QMessageBox::Save);
    return closeornot.exec();
}

void MyWindow::keyPressEvent(QKeyEvent *keyEvent)
{

    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            //TODO trouver autre chose que Close qui ferme le contexte OpenGL mais pas la fenetre
            close();
            break;
        case Qt::Key_F1:
            //TODO ne marche pas
            toggleFullWindow();
            break;
        case Qt::Key_P:
        {
            // change projection mode
            std::cout << "Projection" << std::endl;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if(projection)
            {
                gluOrtho2D(left,right,bottom,top);
                std::cout << "Orthogonale 2D" << std::endl;
            }
            else
            {
                gluPerspective(focale, ratio, near, far);
                std::cout << "Perspective 3D" << std::endl;
            }
            projection = !projection;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            updateGL();
        }
            break;
        case Qt::Key_S:
        {
            std::cout << "Shade Model : " << std::endl;
            if(shade_model)
            {
                glShadeModel(GL_SMOOTH);
                std::cout << "GL_SMOOTH - rendu de Phong, 1 normale par sommets" << std::endl;
            }
            else
            {
                glShadeModel(GL_FLAT);
                std::cout << "GL_FLAT - eclairage constant, 1 normale par faces" << std::endl;
            }
            shade_model = !shade_model;
            updateGL();

        }
            break;
        case Qt::Key_D:
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glFlush();
            updateGL();
        }
            break;
        case Qt::Key_W:
        {
            glDisable(GL_DEPTH_TEST);
            glFlush();
            updateGL();


        }
            break;

        case Qt::Key_M:
        {
            // change de the default material
            choice_mat = (choice_mat + 1) % 5;
            Material((int)choice_mat);
            updateGL();
        }
            break;
        case Qt::Key_Plus:
        {
            float scale = my_map.getScale();
            my_map.changeScale(scale+=pas);
            std::cout << my_map.getScale() << std::endl;

            my_map.generateMap();
            updateGL();
        }
            break;
        case Qt::Key_Minus:
        {
            float scale = my_map.getScale();
            my_map.changeScale(scale-=pas);
            std::cout << my_map.getScale() << std::endl;
            my_map.generateMap();
            updateGL();

        }
            break;
    }
}

void MyWindow::mousePressEvent (QMouseEvent *event) {
    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    if (press)
        setCursor (Qt::ClosedHandCursor);
    // selection de l'action à effectuer
    cam.mouseState(event->button(), Qt::Key_Down, X, Y);
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event){

    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    // selection de l'action à effectuer
    cam.mouseState(event->button(), Qt::Key_Up, X, Y);

    // maj du contexte OpenGL
    updateGL();
}

void MyWindow::mouseMoveEvent (QMouseEvent *event) {
    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();

    // calcul de la transformation
    cam.mouseMove(X, Y);

    // maj du contexte OpenGL
    updateGL();

}

GLvoid MyWindow :: applyLights()
{
    // Lumiere
    GLfloat lightpos[] = { 20.5f, 20.0f, 20.5f,20.5f };
    GLfloat lightcolor[] = { 1.0f, 1.0f, 1.0f,0.5f };
    GLfloat ambcolor[] = { 0.9f, 0.9f, 1.0f,0.9f};
    GLfloat lightambient[] = {10.0f, 10.0f,10.0f, 0.0f};

    glEnable(GL_LIGHTING);                               // enable lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);     // ambient light


    glEnable(GL_LIGHT0);                                 // enable light source
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);           // config light source
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

}

/*
 * Ouverture d'un fichier "images"
 */
void MyWindow::openFile()
{

    QFileDialog open_map(this);
    open_map.setViewMode(QFileDialog::Detail); //permet d'afficher en mode detail (modifiable)
    QString file = open_map.getOpenFileName(this, "Choose your file", default_directory, "Images (*.jpg *.jpeg)");

    if(file.isEmpty())
    {
        QMessageBox::warning(this,"Warning","No file selected.");
    }
    else
    {
        QMessageBox::information(this, "File", "This file had been selected :\n" + file);

        bool loaderimage = monimage.loadJPEG(file.toStdString().c_str());

        if (!loaderimage)
        {
            std::cout << "Impossible de charger l'image :" << file.toStdString() << " veuillez réessayer" << std::endl;
        }

        // création de la map à partir de l'image
        char* new_link;
        if(!my_map.getLoaderTex())
        {
            std::size_t found = file.toStdString().find_last_of("/\\");
            std::string path = file.toStdString().substr(0, found);
            QString newdefaultlink = QString::fromStdString(path) + QString::fromStdString("/texture1.jpeg");

            new_link = newdefaultlink.toAscii().data();
        }
        my_map = CreateMap(monimage, new_link);
    }

}

/*
 * Ouverture d'un fichier "images" pour la texture
 */
void MyWindow::openTex()
{
    QFileDialog open_tex(this);
    open_tex.setViewMode(QFileDialog::Detail); //permet d'afficher en mode detail (modifiable)
    QString texture = open_tex.getOpenFileName(this, "Choose your texture", default_directory, "Images (*.jpg *.jpeg)");

    if(texture.isEmpty())
    {
        QMessageBox::warning(this,"Warning","No texture selected.");
    }
    else
    {
        QMessageBox::information(this, "Texture", "This texture had been selected :\n" + texture);
    }
    char* new_link = texture.toAscii().data();

    if (monimage.getX()>4 && monimage.getY()>0)
    {
        std::cout<<"Veuillez sélectionner une carte"<<std::endl;
        my_map = CreateMap(monimage, new_link);
    }

}

void MyWindow::saveFile()
{
    QFileDialog saveNewFile(this);
    QString file_saved = saveNewFile.getSaveFileName(this, "Save Heightmap", default_directory, "Images (*.stl)");
    my_map.exportToSTL(file_saved.toStdString());

}

void MyWindow::chooseParam()
{
    fenetre.show();
}
void MyWindow::changeParam()
{
    int proj = chooseprojection->currentIndex();
    int shade = chooseshader->currentIndex();
    if(proj == 0){
        projection = false;
    } else {
        projection = true;
    }
    if(shade == 0){
        shade_model = true;
    } else {
        shade_model = false;
    }
    pas = pas * m_lcd->intValue();

    //TODO : relier avec les differents trucs a parametrer
    resizeGL(window_width,window_high);
}

void MyWindow::closeEvent(QCloseEvent *event)
{
    switch (maybeSave()) {
        case QMessageBox::Save:
            // Save was clicked
            saveFile();
            event->accept();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            event->accept();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            event->ignore();
            break;
        default:
            // should never be reached
            break;
    }
}