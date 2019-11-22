# P1RV -heightmaps
Kilian BEHRA & Alicia MARAVAT 

Dépendances : 
  - libjpeg 
  - freeglut 
  - glext
  - glew 
  
 Projet VS2019 : 
  -> C/C++
      -> Général 
          -> C:\dev\libjpeg\include;C:\dev\freeglut\include\GL;C:\dev\glext\include\GL;C:\dev\glew\include\GL;%(AdditionalIncludeDirectories)
          
          -> vérification SDL : non 
   -> éditeur de liens 
      -> Général 
        -> répertoires de bibliothèques supplémentaires : C:\dev\freeglut\lib;C:\dev\glew\lib;C:\dev\glext\lib;C:\dev\libjpeg\lib
        
      -> entrée 
        -> dépendances supplémentaires : opengl32.lib;jpeg.lib;jpegD.lib;glu32.lib;glew32.lib;legacy_stdio_definitions.lib;%(AdditionalDependencies)
    
