cmake_minimum_required(VERSION 3.00)
project(P1RV)

set(CMAKE_CXX_STANDARD 14)

add_executable(P1RV
        main.cpp
        Sources/loadjpeg.cpp
        Sources/loadjpeg.h
        Sources/pixel.cpp
        Sources/pixel.h
        Sources/createmap.cpp
        Sources/createmap.h
        Sources/display.cpp
        Sources/display.h
        Sources/camera.cpp
        Sources/camera.h
        Sources/callback.cpp
        Sources/callback.h
        Sources/Material.cpp
        Sources/Material.h)


# required packages
find_package ( OpenGL REQUIRED )
find_package ( GLUT REQUIRED )

include_directories( ${OPENGL_DIRS} ${GLUT_DIRS} )
link_directories( /usr/lib/x86_64-linux-gnu )
target_link_libraries( P1RV ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES}  libjpeg.so)