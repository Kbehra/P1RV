cmake_minimum_required(VERSION 3.00)
project(P1RV)

set (CMAKE_CXX_STANDARD 14)

link_directories( /usr/lib/x86_64-linux-gnu )

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu ")

add_executable(P1RV
        main.cpp
        Sources/loadjpeg.cpp
        Sources/loadjpeg.h
        Sources/pixel.cpp
        Sources/pixel.h
        Sources/createmap.cpp
        Sources/createmap.h
        Sources/mydisplay.cpp
        Sources/mydisplay.h
        Sources/camera.cpp
        Sources/camera.h
        Sources/callback.cpp
        Sources/callback.h
        Sources/material.cpp
        Sources/material.h Sources/vertex.cpp Sources/vertex.h Sources/interface.cpp Sources/interface.h)


# required packages
find_package ( OpenGL REQUIRED )
find_package ( GLUT REQUIRED )
find_package(Qt4 REQUIRED)

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )

include_directories( ${OPENGL_DIRS} ${GLUT_DIRS} )
target_link_libraries( P1RV ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${QT_LIBRARIES} libjpeg.so)
