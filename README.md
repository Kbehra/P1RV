# P1RV - heightmaps
Kilian BEHRA & Alicia MARAVAT <br>
Projet d'option réalité virtuelle 

## Procédure d'installation : 

Dépendances : 
  - libjpeg 
  - freeglut 
  - glext
  - glew <br>
  
Assurez vous de disposer du client git. 
  
  ### Visual Studio 2019 
 
 Créez un projet vide C++ vide. Ajoutez les sources du projet dans votre nouveau projet.  
 Dans les propriétés du projet, vous devez renseigner les liens vers les bibliothèques. 
 
 les includes (*C/C++ -> Général -> Autres répertoires Include*) 
  >>Exemple: 
  
       C:\dev\libjpeg\include;C:\dev\freeglut\include\GL;C:\dev\glext\include\GL;C:\dev\glew\include\GL;%(AdditionalIncludeDirectories)
       
 Désactivez également la vérification SDL : 
   
          vérification SDL : non 
  
  Renseignez les liens vers les bibliothèques supplémentaires (*éditeur de liens -> Général -> répertoires de bibliothèques supplémentaires*) 
  
   >> Exemple: 
    
      C:\dev\freeglut\lib;C:\dev\glew\lib;C:\dev\glext\lib;C:\dev\libjpeg\lib
      
 puis les dépendances supplémentaires (*éditeur de liens -> entrée -> dépendances supplémentaires*) 
 
   >> Exemple: 
    
    opengl32.lib;jpeg.lib;jpegD.lib;glew32.lib;glew32s.lib;glu32.lib;glut32.lib;freeglut.lib;legacy_stdio_definitions.lib;%(AdditionalDependencies)
    
    
 Une fois les dépendances renseignées vous devriez pouvoir compiler. Assurez vous également que les liens pointent bien vers les images. 
 
 ### Version Linux 
 
 Dans le dépôt vous devriez trouver une branche pour compiler le projet depuis linux avec Cmake (version sans les shaders) 
 
 
 Source Materiau : http://devernay.free.fr/cours/opengl/materials.html
 
   
